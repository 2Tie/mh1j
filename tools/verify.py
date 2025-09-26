import sys
from pathlib import Path

bytes_a = []
bytes_b = []
ignores = []

def main():
  if(len(sys.argv) < 4):
    print("missing args")
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
      mislen += 1
    else:
      if(mislen != 0):
        print(f"{mismatch:X} {mislen:X}")
        mislen = 0
        ctr += 1
        if(ctr == 100):
          print("reporting limit reached")
          break
  if(mislen != 0):
    print(f"{mismatch:X} {mislen:X}")
  if(mismatch != -1):
    print("not funny, didn't match")
    return
  print("all bytes verified!")

if __name__ == '__main__':
  main()
