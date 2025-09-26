import sys
from dataclasses import dataclass
from pathlib import Path
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry, LinkerWriter

@dataclass
class Run:
    entries: list[LinkerEntry]
    is_game: bool
    section: str

def split_into_runs(entries: list[LinkerEntry]) -> list[Run]:
    runs: list[Run] = list()
    runs.append(Run(list(), False, ".text"))
    
    for entry in entries:
        if entry.section_link_type == "pad":
            continue

        entry_is_game = "main" in str(entry.object_path)
        #print(entry_is_game, entry.object_path, entry.section_link_type)

        if entry.section_link_type != runs[-1].section or entry_is_game != runs[-1].is_game:
            runs.append(Run(list(), entry_is_game, entry.section_link_type))

        runs[-1].entries.append(entry)

    return runs



def strip_path(path: Path) -> str:
    return path.name


class LCFWriter:
    def __init__(self, config_path: Path):
        self.config_path = config_path
        self.file = None
        self.last_line_blank = False

    def __enter__(self) -> 'LCFWriter':
        self.file = open(self.config_path, "w")

        with open("tools/lcf/lcf_header.txt") as header:
            self.file.write(header.read())

        return self

    def __exit__(self, *args):
        with open("tools/lcf/lcf_footer.txt") as footer:
            self.file.write(footer.read())

        self.file.close()

    def write_line(self, line: str):
        #print(line)
        self.file.write(f"\t\t{line}\n")
        self.last_line_blank = False

    def blank(self):
        self.file.write("\n")
        self.last_line_blank = True

    def seperator(self):
        self.write_line("# " + "=" * 75)

    def begin_section(self, title: str):
        if not self.last_line_blank:
            self.blank()

        self.seperator()
        self.write_line(f"# {title}")
        self.seperator()
        self.blank()

    def align(self, alignment: int):
        self.write_line(f". = ALIGN(0x{alignment:X});")

    def align_all(self, alignment: int):
        self.write_line(f"ALIGNALL(0x{alignment:X});")

    def add_entry(self, entry: LinkerEntry, section: str):
        self.write_line(f"{strip_path(entry.object_path)} ({section})")

    def add_entries(self, entries: list[LinkerEntry], section: str):
        for entry in entries:
            self.add_entry(entry, section)

    def add_runs(self, runs: list[Run], section: str):
        for run in runs:
            self.add_entries(run.entries, section)

    def write_segment_runs(self, runs: list[Run], segment: str, overlay: bool=False):
        self.file.write(f"\t.{segment}\t:\n\t{{\n")
        self.write_line("_gp = 0x38EB70;")
        #overlay head
        if(overlay):
            self.begin_section("overlay header")
            self.write_line(f"_{segment}_segment_start = .;")
            self.write_line("")
            self.write_line("# declare variables")
            self.write_line(f"_{segment}_text_size = 0;")
            self.write_line(f"_{segment}_data_size = 0;")
            self.write_line(f"_{segment}_bss_size = 0;")
            self.write_line(f"_{segment}_static_init = 0;")
            self.write_line(f"_{segment}_static_init_end = 0;")
            self.write_line("")
            self.write_line("# overlay header")
            self.write_line("WRITEB 0x4D;\t# 'M'")
            self.write_line("WRITEB 0x57;\t# 'W'")
            self.write_line("WRITEB 0x6F;\t# 'o'")
            self.write_line("WRITEB 0x33;\t# '3', ver.3")
            self.write_line(f"WRITEW OVERLAYID(.{segment});\t# overlay ID")
            self.write_line(f"WRITEW ADDR(.{segment});\t# load address")
            self.write_line(f"WRITEW _{segment}_text_size;\t# size of text")
            self.write_line(f"WRITEW _{segment}_data_size;\t# size of data")
            self.write_line(f"WRITEW _{segment}_bss_size;\t# size of bss")
            self.write_line(f"WRITEW _{segment}_static_init;\t# start address of static init")
            self.write_line(f"WRITEW _{segment}_static_init_end;\t# end address of static init")
            self.write_line("")
            self.write_line("# name of overlay in hex")
            #now the overlay name!
            segname = f"{segment}.bin"
            #TODO loop over the name, 32 WRITEBs
            for l in range(0x20):
                letter = "0x00"
                if l < len(segname):
                    letter = hex(ord(segname[l:l+1]))
                self.write_line(f"WRITEB {letter};")
            self.write_line(f"_{segment}_text_start = .;")
        # text
        self.begin_section("text section")
        self.align(0x80)
        text_runs = [x for x in runs if x.section == ".text"]
        for run in text_runs:
            if(len(run.entries) == 0):
                #print(f"zero entries for obj {run}")
                continue
            path = str(run.entries[0].object_path)
            is_lib_vib = "libvib" in path
            is_cri = "cri" in path
            is_crt0 = "crt0" in path
            is_sce = "sce" in path
            alignment = 0x4

            if run.is_game:
                alignment = 0x10
            elif is_lib_vib or is_cri or is_sce:
                alignment = 0x8
            elif is_crt0:
                self.add_entry(run.entries, ".text")
                self.align(0x10)
                continue

            self.align_all(alignment)
            self.add_entries(run.entries, ".text")
        if(overlay):
            self.write_line(f"_{segment}_text_end = .;")
            self.write_line(f"_{segment}_text_size = _{segment}_text_end - _{segment}_text_start;")
        self.blank()

        #for _ in range(2):
        #    self.write_line("WRITEW 0x0; # text section patch for EE pipeline")

        # data/rodata

        self.begin_section("data sections")

        if(overlay):
            self.write_line(f"_{segment}_data_start = .;")

        data_runs = [x for x in runs if (x.section == ".data" and "/elf/" not in str(x.entries[0].object_path) and "_header.s" not in x.entries[0].object_path.name)]
        #for x in data_runs:
        #  print(f"{x.entries[0].object_path}")
        #  if "/elf/" in str(x.entries[0].object_path):
        #    print("HEY OMIT THIS!")
        #  and not "elf" in str(run.entries[0].object_path) ?? todo fix up
        self.begin_section(".data")
        self.align(0x80)
        self.align_all(0x8)
        self.add_runs(data_runs, ".data")

        rodata_runs = [x for x in runs if x.section == ".rodata"]
        self.begin_section(".rodata")
        self.align(0x80)
        self.align_all(0x8)
        self.add_runs(rodata_runs, ".rodata")

        #TODO check sfiii once files are decompiled

        # small data

        self.begin_section("small data sections")

        sdata_runs = [x for x in runs if x.section == ".sdata"]
        self.align(0x80)
        self.align_all(0x4)
        self.add_runs(sdata_runs, ".sdata")

        if(overlay):
            self.write_line(f"_{segment}_static_init = .;")
            self.write_line(f"_{segment}_static_init_end = .;")
            self.write_line(f"_{segment}_data_end = .;")
            self.write_line(f"_{segment}_data_size = _{segment}_data_end - _{segment}_data_start;")

        self.blank()

        if(overlay):
            self.write_line(f"_{segment}_bss_start = .;")
        self.begin_section("sbss sections")

        sbss_runs = [x for x in runs if x.section == ".sbss"]
        self.align(0x080)
        self.align_all(0x4)
        self.add_runs(sbss_runs, ".sbss")

        # bss

        self.begin_section("bss sections")

        bss_runs = [x for x in runs if x.section == ".bss"]

        self.align_all(0x4)

        for run in bss_runs:
            for entry in run.entries:
                self.add_entry(entry, ".bss")
                if "cri" in str(entry.object_path):
                    self.add_entry(entry, "COMMON")

        if(overlay):
            self.write_line(f"_{segment}_bss_end = .;")
            self.write_line(f"_{segment}_bss_size = _{segment}_bss_end - _{segment}_bss_start;")

        self.blank()

        # finalize

        self.align(0x80)
        if(overlay):
            self.write_line(f"_{segment}_segment_end = .;")

        self.file.write(f"\t}}\t>\t{segment}{'' if segment == 'main' else '.bin'}\n")
        self.blank()


def main():
    config_path = Path(sys.argv[1])
    split.main([Path("config/main.yaml")], modes="all", verbose=False)
    #main_backup = split.linker_writer.entries
    runs_main = split_into_runs(split.linker_writer.entries)

    #ctx_backup = split.symbols.spim_context

    #print(len(runs_main))

    #write_segment_runs(runs_main, "main")

    split.main([Path("config/select.yaml")], modes="all", verbose=False)
    runs_select = split_into_runs(split.linker_writer.entries)

    split.symbols.spim_context = split.symbols.spimdisasm.common.Context()
    #split.main(["config/main.yaml"], modes="all", verbose=False)

    #split.linker_writer.entries = main_backup

    split.main([Path("config/game.yaml")], modes="all", verbose=False)
    runs_game = split_into_runs(split.linker_writer.entries)

    split.symbols.spim_context = split.symbols.spimdisasm.common.Context()
    #split.main(["config/main.yaml"], modes="all", verbose=False)

    #print(len(runs_game))

    split.main([Path("config/yn.yaml")], modes="all", verbose=False)
    runs_yn = split_into_runs(split.linker_writer.entries)

    split.symbols.spim_context = split.symbols.spimdisasm.common.Context()
    #split.main(["config/main.yaml"], modes="all", verbose=False)


    split.main([Path("config/lobby.yaml")], modes="all", verbose=False)
    runs_lobby = split_into_runs(split.linker_writer.entries)
    split.symbols.spim_context = split.symbols.spimdisasm.common.Context()

    split.main([Path("config/dnas_ins.yaml")], modes="all", verbose=False)
    runs_dnas_ins = split_into_runs(split.linker_writer.entries)
    split.symbols.spim_context = split.symbols.spimdisasm.common.Context()

    split.main([Path("config/dnas_net.yaml")], modes="all", verbose=False)
    runs_dnas_net = split_into_runs(split.linker_writer.entries)
    #split.symbols.spim_context = split.symbols.spimdisasm.common.Context()



    #write_segment_runs(runs_game, "game")

    with LCFWriter(config_path) as lcf:
        lcf.write_segment_runs(runs_main, "main", False)
        lcf.write_segment_runs(runs_select, "select", True)
        lcf.write_segment_runs(runs_game, "game", True)
        lcf.write_segment_runs(runs_yn, "yn", True)
        lcf.write_segment_runs(runs_lobby, "lobby", True)
        lcf.write_segment_runs(runs_dnas_net, "dnas_net", True)
        lcf.write_segment_runs(runs_dnas_ins, "dnas_ins", True)
    #patch CRI rodata segments
    print("LCF written!")

    cri_nonmatchings = Path("asm/nonmatchings/cri")

    for asm_file in cri_nonmatchings.rglob("*.s"):
        text = asm_file.read_text()
        text = text.replace(".section .rodata", ".rdata")
        asm_file.write_text(text)

if __name__ == "__main__":
    main()
