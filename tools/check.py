import sys
from pathlib import Path
import argparse

parser = argparse.ArgumentParser()
subparsers = parser.add_subparsers()
bindiff_parser = subparsers.add_parser("bindiff")
bindiff_parser.add_argument("file1", type=str)
bindiff_parser.add_argument("file2", type=str)
bindiff_parser.add_argument("-i", "--ignores-file", type=str)
bindiff_parser = subparsers.add_parser("xmap")
bindiff_parser.add_argument("xmapfile", type=str)
bindiff_parser.add_argument("-p", "--print_all_symbols", action="store_true")
args = parser.parse_args()

def check_xmap(file_path: str, print_all=False):
    missed = False
    with open(Path(file_path), 'r') as f:
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
                address, size, segment, label, obj_file = ss
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



def main():
    print(args)
    if args.xmapfile is not None:
        check_xmap(args.xmapfile, args.print_all_symbols)
    pass

if __name__ == "__main__":
    main()
