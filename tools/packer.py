import sys
from datetime import datetime
from pathlib import Path

filepos = 0;
bin = b''
manifest = []

def readUint():
  global bin, filepos
  value = int.from_bytes(bin[filepos:filepos+4], byteorder='little', signed=False)
  filepos += 4
  return value

def readUshort():
  global bin, filepos
  value = int.from_bytes(bin[filepos:filepos+2], byteorder='little', signed=False)
  filepos += 2
  return value

def melt(filebin):
  bitcounter = 0
  newbuf = []
  binpos = 0
  run = 0
  while(True):
    if bitcounter == 0 :
      bitcounter = 0x8000
      run = int.from_bytes(filebin[binpos:binpos+2], byteorder='little', signed=False)
      binpos += 2
    if run & bitcounter == 0:
      newbuf.append(filebin[binpos])
      newbuf.append(filebin[binpos+1])
      binpos += 2
    else:
      offset = int.from_bytes(filebin[binpos:binpos+2], byteorder='little', signed=False)
      binpos += 2
      count = offset >> 11
      if count == 0 :
        count = int.from_bytes(filebin[binpos:binpos+2], byteorder='little', signed=False)
        binpos += 2
      else:
        offset = (offset & 0x7FF)*2
      if offset == 0:
        if count == 0:
          break
        for c in range(count):
          newbuf.append(0)
          newbuf.append(0)
      else:
        for c in range(count):
          newbuf.append(newbuf[len(newbuf)-offset])
          newbuf.append(newbuf[len(newbuf)-offset])
    bitcounter >>= 1
  return newbuf

def unpack(file, dir):
  global bin, filepos
  filelist = []
  print(f"unpacking {file}")
  with open(file, 'rb') as binfile:
    bin = binfile.read()
  #do the shit
  #read the magic to verify it's a regular AFS1 archive
  magic = bin[0:4].decode('utf-8')
  filepos += 4
  print(magic)
  if magic != "AFS\x00":
    print(f"incorrect magic: {bin[0:4]}")
    return
  filecount = readUint()
  print(f"file count: {filecount}")
  #then for the filecount, read pointer and size!
  for f in range(filecount):
    fileoff = readUint()
    filesize = readUint()
    #print(f"{f}: off {fileoff:X}, size {filesize:X}, readpos {filepos:X}")
    filelist.append([fileoff, filesize])
  #now fetch the attributes table
  filepos = filelist[0][0]-8
  attpos = readUint()
  attsize = readUint()
  print(f"attributes info: pos {attpos:X} size {attsize:X}")
  if attpos == len(bin):
    print("no attributes table!") #MHDOS does this for the top-level asset AFS (DATA.BIN)
  else:
    filepos = attpos
    for f in range(filecount):
      filename = bin[filepos:filepos+0x20].decode('utf-8').rstrip('\x00')
      filepos += 0x20
      filemod = datetime(readUshort(), readUshort(), readUshort(), readUshort(), readUshort(), readUshort())
      filesize = readUint()
      #print(f"{f:X}: {filename} {filelist[f][1]:X}")
      if filesize != filelist[f][1]:
        print(f"file {filename} has size mismatch: {filelist[f][1]:X} in header vs {filesize:X} in attrs!")
      filelist[f].append(filename)
      filelist[f].append(filemod)
  for f in range(filecount):
    filename = f"{f}.bin"
    if len(filelist[f]) > 2:
      filename = filelist[f][2]
    #filepath = dir + filename
    #check the list to grab final filepath, also check if we need to decompress
    newfile = bin[filelist[f][0]:filelist[f][0]+filelist[f][1]]
    compressed = True
    #some heuristics to start off with
    #compressed will always have 4 trailing 00 bytes
    if newfile[len(newfile)-4:len(newfile)] != b'\x00\x00\x00\x00':
      candidate = False
    asci = True
    #compressed will never have a valid magic(?)
    for c in range(3):
      if (newfile[c] < 0x20) or (newfile[c] > 0x7E):
        asci = False
        break
    if asci:
      compressed = False
    #print(f"{f}: {filename} {compressed}")
    folder = ""
    if len(manifest) != 0:
      mrow = manifest[f].split(" ")
      if mrow[0] != filename:
        print(f"error: name mismatch at file {f}: manifest \"{mrow[0]}\" vs AFS \"{filename}\"")
        #print(filename.encode())
        #print(mrow[0].encode())
        return
      elif (mrow[1] == "Y") != compressed:
        #heuristics failed, log this for investigation
        print(f"warning: file {filename} manifest ({mrow[1]}) mismatches compress heuristic ({compressed})")
        #and flip to match manifest, we trust manifest
        compressed = not compressed
      folder = mrow[2]
    filepath = dir + folder + filename
    #print(filepath)
    pp = Path(dir + folder)
    if not pp.exists():
      pp.mkdir(parents=True)
    if compressed:
      newfile = bytes(melt(newfile))
    #print(f"writing {filepath}")
    with open(filepath, 'wb') as outfile:
      outfile.write(newfile)

if __name__ == "__main__":
  if len(sys.argv) == 5: #packer -u AFS_DATA.AFS assets/AFS/ tools/AFS_files.txt
    with open(sys.argv[4]) as m:
      manifest = [line.rstrip() for line in m]
  if len(sys.argv) >= 4: #packer -u AFS_DATA.AFS assets/AFS/
    if(sys.argv[1] == "-u"):
      print(f"unpacking {sys.argv[2]} to {sys.argv[3]}")
      unpack(sys.argv[2], sys.argv[3])
      #go through the table, unpacking and then decompressing as needed. generate a txt file of the files in order with a y or n based on if it was compressed, for repacking purposes? also maybe original filesize, to see if compression is a simple pattern?
    elif(sys.argv[1] == "-p"):
      print(f"packing {sys.argv[3]} to {sys.argv[2]}")
      #if the list exists, use that. else, just grab all the files and stuff!
  else:
   print("insufficient args. -flag archive folder")

