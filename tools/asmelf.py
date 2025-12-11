from pathlib import Path

from mwccgap.mwccgap.assembler import Assembler
from mwccgap.mwccgap.elf import Elf

o_file=Path("build/asmbin.o")

assembler = Assembler(
  as_path="bin/mips-ps2-decompals-as",
  as_flags=["-EL", "-I include/", "-G 128", "-march=r5900", "-mabi=eabi", "-no-pad-sections", "-mno-pdr"],
  as_march="r5900",
  as_mabi="eabi",
  macro_inc_path=Path("include/macro.inc"),
)

asm_bytes = assembler.assemble_file(Path("asm/main/nonmatchings/stage/stage_set_set0x15bbe0.s"))
assembled_elf = Elf(asm_bytes)

o_file.write_bytes(assembled_elf.pack())
