from pathlib import Path
from difflib import *
import argparse
import subprocess

import lief

parser = argparse.ArgumentParser()
subparsers = parser.add_subparsers(dest="command")

# these should just parse the binary and calculate RVA stuff on it's own
# could probably also add a way to write the overlays to the files, might lead to weird diffs?
bindiff_parser = subparsers.add_parser("funcdiff")
bindiff_parser.register('type', 'hexadecimal integer', lambda s: int(s, 16))
bindiff_parser.add_argument("built", type=str)
bindiff_parser.add_argument("target", type=str)
bindiff_parser.add_argument("start", type="hexadecimal integer")
bindiff_parser.add_argument("length", type="hexadecimal integer")
bindiff_parser.add_argument("-i", "--ignores-file", type=str)

bytediff_parser = subparsers.add_parser("bytediff")
bytediff_parser.register('type', 'hexadecimal integer', lambda s: int(s, 16))
bytediff_parser.add_argument("built", type=str)
bytediff_parser.add_argument("target", type=str)
bytediff_parser.add_argument("start", type="hexadecimal integer")
bytediff_parser.add_argument("length", type="hexadecimal integer")
bytediff_parser.add_argument("-i", "--ignores-file", type=str)

pos_parser = subparsers.add_parser("positions")
pos_parser.add_argument("built", type=str)
pos_parser.add_argument("target", type=str)
pos_parser.add_argument("-p", "--print_all", action="store_true")

xmap_parser = subparsers.add_parser("xmap")
xmap_parser.add_argument("file", type=str)
xmap_parser.add_argument("-p", "--print_all", action="store_true")
args = parser.parse_args()

RED = '\033[91m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
RESET = '\033[0m'


def disassemble(file: str, function_name: str):
    disas = subprocess.run(
            ["./bin/mips-ps2-decompals-objdump", "-d", f"--disassemble={function_name}", file],
            capture_output=True,
            text=True,
            check=True
        )
    output = b""
    lines = disas.stdout.splitlines()
    for i, line in enumerate(lines):
        if line.startswith("Disassembly"):
            output = "\n".join(lines[i+2:])
    return output

def check_xmap(file: str, print_all=False):
    missed = False
    with open(Path(file), 'r') as f:
        for line in f:
            if line.startswith("# Memory Map"):
                print("xmap symbols matched!")
                return
            if line.startswith("# ."):
                print(f"checking symbol placement in {line[2:].strip()}")
            if line.startswith("  "):
                ss = line.split()
                if len(ss) == 4: # this is the memory map
                    continue
                address, _, segment, label, obj_file = ss
                if segment == label:
                    continue
                if address[-6:].upper() == label[-6:].upper():
                    continue
                if "0x" not in label:
                    continue
                missed = True
                print(f"symbol misplaced: {label} placed at {address}:{segment} {obj_file}")
                if not print_all:
                    break
        if missed:
            print(f"verify prior symbol(s)!")

def byte_diff(built: str, target: str, start: int, length: int, ignores_file=None):
    with open(built, 'rb') as f:
        bytes_a = f.read()
    with open(target, 'rb') as f:
        bytes_b = f.read()

    ignore_pos = 0
    ignores = []
    if ignores_file is not None:
        with open(ignores_file, 'rb') as f:
           ignores= f.readlines()

    diff_positions = []
    mismatch = -1
    mm_base = -1
    ctr = 0
    mislen = 0
    astr = ""
    bstr = ""
    num_ignores = len(ignores)
    for pos in range(start, start + length):
        if ignores and ignore_pos < num_ignores:
            igdat = ignores[ignore_pos].split()
            igstart = int(igdat[0], 16)
            igend = igstart + int(igdat[1], 16)

            if pos >= igstart and pos < igend:
                continue
            if pos == igend:
                ignore_pos += 1
                continue
        if bytes_a[pos:pos+1] != bytes_b[pos:pos+1]:
            if mislen == 0:
                mismatch = pos
                mm_base = mismatch - (mismatch % 4)
                astr = ""
                bstr = ""
                for c in range(4):
                    astr += f"{bytes_a[mm_base+c]:02X}"
                    bstr += f"{bytes_b[mm_base+c]:02X}"
            mislen += 1
        else:
            if mislen != 0:
                print(f"{BLUE}{built}: {mismatch:X} {mislen:X}: snapshot {mm_base:06X}: {RED}{astr} -> {bstr}{RESET}")
                diff_positions.append(mismatch + 0x100000 - start) # rva stuff
                mislen = 0
                ctr += 1
                if ctr == 100:
                    print("reporting limit reached")
                    break
    return sorted(diff_positions)

def compare_addr(sym1: lief.ELF.Symbol, sym2: lief.ELF.Symbol):
    color = ""
    sym_addr_diff = sym1.value - sym2.value
    if sym_addr_diff > 0:
        color = YELLOW
    elif sym_addr_diff < 0:
        color = RED 
    if color != "":
        print(f"{GREEN}{sym1.name}:{BLUE}{sym1.value:08X} - {GREEN}{sym2.name}:{BLUE}{sym2.value:08X} {color}offset={hex(-1*sym_addr_diff)}{RESET}")
    return sym_addr_diff != 0

# this has to return the file binary too, and you cant just ignore it when setting a var to it
# otherwise it causes a seg fault
def get_symbols(file: str):
    file_binary = lief.parse(file)
    file_symbols = {sym.name: sym for sym in file_binary.symbols if sym.value != 0 and sym.is_function}
    file_symbols = dict(sorted(file_symbols.items(), key=lambda s: s[1].value))
    return file_symbols, file_binary

def compare_positions(built: str, target: str, print_all=False):
    built_symbols, built_bin = get_symbols(built)
    target_symbols, target_bin = get_symbols(target)
    for _, target_sym in target_symbols.items():
        if (built_sym := built_symbols.get(target_sym.name)) is None:
            if (built_sym := built_symbols.get(f"{target_sym.name}0x{target_sym.value:06x}")) is None:
                print(f"Could not find function {target_sym.name} in built")
                continue

        different = compare_addr(target_sym, built_sym)
        # why the fuck is this inverted?
        if different and not print_all:
            break
    print("Verify prior functions (there might be more)")

# this is messy but it works ?
def function_diff(built: str, target: str, args):
    diff_positions = byte_diff(built, target, args.start, args.length, args.ignores_file)
    built_symbols, built_bin = get_symbols(built)
    target_symbols, target_bin = get_symbols(target)

    # this is just to properly make the diffs (search and replace the symbols that have 0x... on them)
    target_to_built = {}
    for _, target_sym in target_symbols.items():
        if (built_sym := built_symbols.get(target_sym.name)) is None:
            built_sym = built_symbols.get(f"{target_sym.name}0x{target_sym.value:06x}")
        if built_sym is not None:
            target_to_built[target_sym.name] = built_sym.name

    target_symbols_list = list(sorted(target_symbols.values(), key=lambda s: s.value))
    diff_functions = set()
    sym_idx = 0
    for pos in diff_positions:
        while sym_idx < len(target_symbols) - 1 and target_symbols_list[sym_idx].value + target_symbols_list[sym_idx].size <= pos:
            sym_idx += 1
        target_sym = target_symbols_list[sym_idx]
        diff_functions.add(target_sym.name)

    # do it like this to not duplicate
    for diff_function in diff_functions:
        target_sym = target_symbols.get(diff_function)
        if (built_sym := built_symbols.get(target_sym.name)) is None:
            if (built_sym := built_symbols.get(f"{target_sym.name}0x{target_sym.value:06x}")) is None:
                print(f"Could not find function {target_sym.name} in built")
                continue
        built_asm = disassemble(built, built_sym.name)
        target_asm = disassemble(target, target_sym.name)
        # kinda cursed but necessary i think
        for target_name, built_name in target_to_built.items():
            target_asm = target_asm.replace(f"<{target_name}+", f"<{built_name}+")
            target_asm = target_asm.replace(f"<{target_name}>", f"<{built_name}>")

        print(f"{BLUE}{target_sym}/{built_sym}{RESET}")
        if target_asm == built_asm:
            continue

        a = target_asm.splitlines(keepends=True)
        b = built_asm.splitlines(keepends=True)
        #diff = context_diff(a, b, fromfile=target_sym.name, tofile=built_sym.name)
        #diff = ndiff(a, b)
        diff = unified_diff(a, b, fromfile=target_sym.name, tofile=built_sym.name, n=5)
        print(f"{YELLOW}{"".join(diff)}{RESET}")

def main():
    if args.command == "xmap":
        check_xmap(args.file, args.print_all)
    elif args.command == "positions":
        compare_positions(args.built, args.target, args.print_all)
    elif args.command == "funcdiff":
        function_diff(args.built, args.target, args)
    elif args.command == "bytediff":
        byte_diff(args.built, args.target, args.start, args.length, args.ignores_file)
    pass

if __name__ == "__main__":
    main()
