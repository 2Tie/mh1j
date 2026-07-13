import sys
from pathlib import Path

bytes_a = []
bytes_b = []
ignores = []

def main():
  if(len(sys.argv) < 4):
    if(sys.argv[1] != "-m" or len(sys.argv) != 3):
      print("missing args")
      return
    with open(Path(sys.argv[2]), 'r') as f:
      for line in f:
        if(line.startswith("# Memory map")):
          print("symbols matched!")
          return
        if(line.startswith("# .")):
          print("checking symbol placement in " + line[2:])
        if(line.startswith("  ")):
          ss = line.split()
          if(ss[2] == ss[3]): #segment label, e.g. ".bss"
            continue
          if(ss[0][-6:].upper() == ss[3][-6:].upper()): #address and symbol tail tag match
            continue
          if(not("0x" in ss[3])): #assume a lib func like fptodp where we've stripped the tail tag
            continue
          print("symbol misplaced: " + ss[3] + " placed at " + ss[0])
          print("verify prior symbol!")
          return
  file_a = Path(sys.argv[1])
  file_b = Path(sys.argv[2])
  start = int(sys.argv[3], 16)
  length = int(sys.argv[4], 16)
  ignorefile = None
  ignorepos = 0
  ignores = []
  if(len(sys.argv) > 5):
    ignorefile = Path(sys.argv[5])

  with open(file_a, 'rb') as f:
    bytes_a = f.read()
  with open(file_b, 'rb') as f:
    bytes_b = f.read()
  if(ignorefile != None):
    with open(ignorefile, 'r') as f:
      ignores = f.readlines()
  mismatch = -1
  mm_base = -1
  astr = ""
  bstr = ""
  ctr = 0
  mislen = 0
  for b in range(length):
    pos = start+b
    if(ignores and ignorepos < len(ignores)):
      igdat = ignores[ignorepos].split()
      igstart = int(igdat[0], 16)
      igend = igstart + int(igdat[1], 16)
      #print(f"test ignore: {igstart:X} {igend:X} {pos:X}")
      if(pos >= igstart and pos < igend):
        #print(f"ignored {pos:X}")
        continue
      if(pos == igend):
        ignorepos += 1
        continue
    if(bytes_a[pos:pos+1] != bytes_b[pos:pos+1]):
      if(mislen == 0):
        mismatch = pos
        mm_base = mismatch - (mismatch%4)
        astr = ""
        bstr = ""
        for c in range(4):
          astr += f"{bytes_a[mm_base+c]:02X} "
          bstr += f"{bytes_b[mm_base+c]:02X} "
      mislen += 1
    else:
      if(mislen != 0):
        print(f"{mismatch:X} {mislen:X}: snapshot {mm_base:06X}: {astr}-> {bstr}")
        mislen = 0
        ctr += 1
        if(ctr == 100):
          print("reporting limit reached")
          break
  if(mislen != 0):
    print(f"{mismatch:X} {mislen:X}: snapshot {mm_base:06X}: {astr}-> {bstr}")
  if(mismatch != -1):
    print("not funny, didn't match")
    return
  print("all bytes verified!")

if __name__ == '__main__':
  main()
