import sys
import struct
import hashlib

crypt1listing = {}
crypt2listing = {}
crypt3listing = {}

crypt4listing = {}
crypt5listing = {}

ins_cryptdata = []
net_cryptdata = []
keysbin = []
keysbinpos = 0

garbo = []
garbopos = 0
keys = []
codebuf = []
ins_filedata = {}
net_filedata = {}
filedata = {}
filepos = 0
overlaystart = 0xA06200
with open('overlays/dnas_ins.bin', 'rb') as f:
  ins_filedata = bytearray(f.read())
with open('overlays/dnas_net.bin', 'rb') as f:
  net_filedata = bytearray(f.read())
with open('config/cryptlist1.txt', 'r') as f:
  crypt1listing = f.readlines()
with open('config/cryptlist2.txt', 'r') as f:
  crypt2listing = f.readlines()
with open('config/cryptlist3.txt', 'r') as f:
  crypt3listing = f.readlines()
with open('config/cryptlist4.txt', 'r') as f:
  crypt4listing = f.readlines()
with open('config/cryptlist5.txt', 'r') as f:
  crypt5listing = f.readlines()
with open('config/dnas_ins_crypt_symbols.txt', 'r') as f:
  ins_cryptdata = f.readlines()
with open('config/dnas_net_crypt_symbols.txt', 'r') as f:
  net_cryptdata = f.readlines()


def readuint():
  global filepos, filedata
  val = struct.unpack('I', filedata[filepos:filepos+4])[0]
  filepos += 4
  return val

def writeuint(arg:int):
  global filepos, filedata
  arg = arg & 0xFFFFFFFF
  struct.pack_into('I', filedata, filepos, arg)
  filepos += 4
  return

def readbyte():
  global filepos, filedata
  val = struct.unpack('B', filedata[filepos:filepos+1])[0]
  filepos += 1
  return val

def writebyte(arg:int):
  global filepos, filedata
  val = struct.pack_into('B', filedata, filepos, arg)
  filepos += 1
  return

def seek(pos):
  global filepos, overlaystart
  filepos = pos - overlaystart

def decrypt(listings, table):
  global filepos, overlaystart
  #print("starting decrypt")
  for listing in listings:
    #listing = l.split()
    seek(int(listing, 16))
    off = -1
    for i in range(16):
      val = readuint()
      if val & 0xFFFFFF00 == 0x10000000:
        off = filepos + overlaystart + ((val & 0xFF) << 2)
        #branch found, copy out and overwrite garbo?
        readuint() #nop branch delay
        #bookmark = filepos + overlaystart
        for op in range(6):
          garbo.append(readuint()) #garbo value
          filepos -= 4
          writeuint(0) #clean it out
        break
    if off == -1:
      print(f"didn't find branch following {listing}")
      continue
    #print(f"start is {off:X}")
    readuint() #lockvar
    sequence = readuint()
    key = readuint()
    length = readuint()
    length ^= sequence
    sequence &= 0x77777777
    seqcount = sequence >> 0x1C
    if seqcount == 0:
      seqcount = 5
    #print(f"keys are {key:X} {length:X} {sequence:X}")
    tableentry = -1
    if key != 0:
     for t in range(len(table)):
       if key == table[t][0]:
         tableentry = t
         break
     if tableentry == -1:
       print("didn't find match for key?")
       #print(f"keys are {key:X} {length:X} {sequence:X}")
       continue
    #print(f"matched entry is {tableentry}, starting val is {table[tableentry][1]:X}")
    seek(off)
    for b in range(int(length/4)):
      val = readuint()
      if key != 0 and table[tableentry][1] + b*4 in table[tableentry][2]:
        #print(f"filepos: {(filepos + overlaystart):X}  tab: {(table[t][1] + b*4):X} op: {val:08X}")
        #match (val >> 24) & 0xFC:
        #  case 0x3C:
        #    print(f"0x3C load hi arg {(val & 0xFF):02X}")
        #  case 0x24:
        #    print(f"0x24 load lo arg {(val & 0xFFFF):04X}")
        #  case 0x0C:
        #    print(f"0x0C call arg {((val & 0xFFFFFF)*4):06X}")
        #  case 0x8C:
        #    print(f"0x8C load word arg $gp + {(val & 0xFFFF):04X}")
        #  case 0xAC:
        #    print(f"0xAC stor word arg $gp + {(val & 0xFFFF): 04X}")
        #  case 0x08:
        #    print(f"0x08 jump arg {((val & 0xFFFFFF)*4):06X}")
        continue
      for s in range(seqcount):
        operand = (sequence >> (s*4)) & 0xF
        #print(f"operand is {(sequence >> (s*4))& 0xF}")
        filepos -= 4
        match operand:
          case 0:
            val ^= 0x9F8ED17
            writeuint(val)
          case 1:
            val ^= 0xA95128C3
            writeuint(val)
          case 2:
            val = ((val >> 0xd) & 0x7FFFF) | (val << 0x13)
            writeuint(val)
          case 3:
            val = ((val >> 0x8) & 0xFFFFFF) | (val << 0x18)
            writeuint(val)
          case 4:
            val = ((val & 0xFF) << 8 ) | ((val >> 8) & 0xFF0000) | ((val >> 0x10) & 0xFF) | ((val & 0xFF00) << 0x10)
            writeuint(val)
          case 5:
            val ^= 0x9f8ed17
            val = ((val >> 0xd) & 0x7FFFF) | (val << 0x13)
            writeuint(val)
          case 6:
            val = ((val & 0xFF) << 8 ) | ((val >> 8) & 0xFF0000) | ((val >> 0x10) & 0xFF) | ((val & 0xFF00) << 0x10)
            val ^= 0xa95128c3
            val = ((val >> 0x8) & 0xFFFFFF) | (val << 0x18)
            writeuint(val)
          case 7:
            val ^= 0x9f8ed17
            val = ((val >> 0x8) & 0xFFFFFF) | (val << 0x18)
            val = ((val >> 0xd) & 0x7FFFF) | (val << 0x13)
            val = ((val & 0xFF) << 8 ) | ((val >> 8) & 0xFF0000) | ((val >> 0x10) & 0xFF) | ((val & 0xFF00) << 0x10)
            writeuint(val)
      filepos -= 4
      op = readuint()
      #top = (op & 0xFC000000) >> 24
      #match = [0x3C, 0x0C, 0x24, 0x8C, 0x08, 0xAC]
      #if (top in match):
        #print(f"opcode match: {op:08X} at filepos {(filepos + overlaystart):08X}")
      #else:
      #print(f"final opstate is {op:08X}")
    #print("cryption happened!")
    if readuint() != 0x1000000b:
      print("no branch following chunk?")
    else:
      readuint() #branch delay nop
      for i in range(6):
        garbo.append(readuint())
        filepos -= 4
        writeuint(0)
    #print(f"done unencrypting pass at {(filepos+overlaystart):08X}")
    #print("    ")
  #now that all is unencrypted, read the cryptdata and dump the keys and strings


def extractkeys(cryptdata):
  global filepos
  for i in range(len(cryptdata)):
    addroff = cryptdata[i].find("= ")
    if addroff == -1:
      continue
    addr = int(cryptdata[i][addroff+2:addroff+2+8], 16)
    #print(f"{addr:X}")
    typ = cryptdata[i].find("size:")
    seek(addr)
    if typ != -1:
      #set of four uint keys/raw data
      lgt = int(int(cryptdata[i][typ+5:], 16)/4)
      #print(f"symbol size: {lgt}")
      for i in range(lgt):
        val = readuint()
        #print(f"{val:X}")
        keys.append(struct.pack("I", val))
        filepos -= 4
        writeuint(0)
    elif cryptdata[i].find("char") != -1:
      #string
      #find end (00)
      start = addr-overlaystart
      end = filedata.find(b'\x00', filepos)+1
      bstr = filedata[start:end]
      #print(bstr)
      keys.append(bstr)
      #print(f"{bstr.decode('utf-8')}")
      #slice [:] and convert .decode('utf-8') to print out?
      for i in range(end - start):
        writebyte(0)



def injectkeys(cryptdata):
  global codebuf, keysbinpos
  #print(f"file has {len(codebuf)} lines")
  cryptline = 0
  print(f"{len(cryptdata)} keys")
  #get current address
  keypos = cryptdata[cryptline].find(" = 0x")
  keypos += 5
  keystr = cryptdata[cryptline][keypos:keypos+6].upper()
  keytype = cryptdata[cryptline].find("size:") #-1 means string, otherwise four uints!
  #print(keystr)
  for i in range(len(codebuf)):
    #check if this line has our next address
    #if so, replace with our data
    exists = codebuf[i].find(f"00{keystr} 00000000 */")
    if exists != -1:
      #print(f"found key at line {i}:")
      #print(codebuf[i])
      #handcraft a new line
      if keytype != -1:
        #print(f"uint at line {i}")
        lgt = int(int(cryptdata[cryptline][keytype+5:-1], 16)/4)
        for u in range(lgt):
          codebuf[i+u] = f"    /* injected key val:uint */  .word 0x{(struct.unpack_from('I', keysbin, keysbinpos)[0]):08X}\n"
          #print(f"{struct.unpack_from('I', keysbin, keysbinpos)[0]:08X}")
          keysbinpos += 4
      elif cryptdata[cryptline].find("char") != -1:
        #print(f"text at line {i}")
        strend = keysbin.find(b'\x00', keysbinpos)
        strlen = strend - keysbinpos
        codebuf[i] = f"    /* injected key val:text */  .asciiz \"{struct.unpack_from(f'{strlen}s', keysbin, keysbinpos)[0].decode('utf-8')}\"\n.balign 4\n"
        strlen -= 4
        extra = 1
        while strlen + 1 > 0: #include nul terminator here
          codebuf[i+extra] = "    /* line removed for text */\n"
          strlen -= 4
          extra += 1
        keysbinpos = strend + 1
      else:
        print(f"other at line {i}")
      #grab next
      cryptline += 1
      if cryptline == len(cryptdata):
        break
      while True:
        keypos = cryptdata[cryptline].find(" = 0x")
        if keypos == -1 or (cryptdata[cryptline].find("label") != -1 and cryptdata[cryptline].find("size:") == -1): #skip the labels!
          cryptline += 1
          continue
        break
      keypos += 5
      keystr = cryptdata[cryptline][keypos:keypos+6].upper()
      keytype = cryptdata[cryptline].find("size:") #-1 means string, otherwise four uints!
      #print(f"{keystr} sizepos? {keytype}")
  if cryptline == len(cryptdata):
    print("all keys found")
  else:
    print(f"didn't find key {keystr}")

ins_tableaddrs = [0xa2f8a0, 0xa2eb68, 0xa26970]
net_tableaddrs = [0xa32d48, 0xa6b128]

def extracttables(tableaddrs):
 global filepos
 for t in range(len(tableaddrs)):
  seek(tableaddrs[t])
  count = readuint()
  table = []
  filepos -= 4
  writeuint(0)
  for i in range(count):
   st = []
   st.append(readuint())
   filepos -= 4
   writeuint(0) #key
   writeuint(0) #offset
   table.append(st)
  for i in range(count):
   table[i].append(readuint())
   filepos -= 4
   writeuint(0) #init
   offcount = readuint()
   filepos -= 4
   writeuint(0) #count
   offs = []
   for b in range(offcount):
    offs.append(readuint())
    filepos -= 4
    writeuint(0) #offsets
   table[i].append(offs)
  keytables.append(table)

def writetables(tableaddrs):
 global codebuf
 for t in range(len(tableaddrs)):
  line = -1
  for l in range(len(codebuf)):
   exists = codebuf[l].find(f" {tableaddrs[t]:08X} 00000000 */")
   if exists != -1:
    line = l
    break
  if line == -1:
   print(f"didn't find table stub: {t} {tableaddrs[t]:08X}")
   return
  table = []
  if t == 0 and len(tableaddrs) == 3:
   table = keytables[0]
  elif t == 1 and len(tableaddrs) == 3:
   table = keytables[1]
  elif t == 2 and len(tableaddrs) == 3:
   table = keytables[2]
  elif t == 0 and len(tableaddrs) == 2:
   table = keytables[3]
  elif t == 1 and len(tableaddrs) == 2:
   table = keytables[4]
  codebuf[l] = f"    /* keytable injected # {t}   */ .word 0x{(len(table)):08X}\n"
  off = 0
  for r in range(len(table)):
   codebuf[l+1+(r*2)] = f"    /* keytable injected key   */ .word 0x{table[r][0]:08X}\n"
   #writeuint(table[r][0])
   codebuf[l+1+(r*2)+1] = f"    /* keytable injected off   */ .word 0x{(off*4):08X}\n"
   #writeuint(off)
   off += 2+len(table[r][2])
  off = 1+(len(table))*2
  for r in range(len(table)):
   codebuf[l+off] = f"    /* keytable injected init  */ .word 0x{table[r][1]:08X}\n"
   #count
   count = len(table[r][2])
   codebuf[l+off+1] = f"    /* keytable injected count */ .word 0x{count:08X}\n"
   #the entries
   for v in range(count):
    codebuf[l+off+2+v] = f"    /* keytable injected value */ .word 0x{table[r][2][v]:08X}\n"
   off += 2+count
  codebuf[l+off] = "    /* keytable end, TODO size */\n" #we clobbered a .size line so we need to eat a nop to align

def encrypt(listings, table):
  global filepos, garbopos
  #print("starting encrypt")
  for listing in listings:
    #listing = l.split()
    seek(int(listing, 16))
    off = -1
    for i in range(16):
      val = readuint()
      if val & 0xFFFFFF00 == 0x10000000:
        off = filepos + overlaystart + ((val & 0xFF) << 2)
        #branch found, copy out and overwrite garbo?
        readuint() #nop branch delay
        #bookmark = filepos + overlaystart
        for op in range(6):
          writeuint(garbo[garbopos])
          garbopos += 1
        break
    if off == -1:
      print(f"didn't find branch following {listing}")
      continue
    #print(f"start is {off:X}")
    readuint() #lockvar
    sequence = readuint()
    key = readuint()
    length = readuint()
    length ^= sequence
    sequence &= 0x77777777
    seqcount = sequence >> 0x1C
    if seqcount == 0:
      seqcount = 5
    #print(f"keys are {key:X} {length:X} {sequence:X}")
    tableentry = -1
    if key != 0:
     for t in range(len(table)):
       if key == table[t][0]:
         tableentry = t
         break
     if tableentry == -1:
       print("didn't find match for key?")
       #print(f"keys are {key:X} {length:X} {sequence:X}")
       continue
    #print(f"matched entry is {tableentry}, starting val is {table[tableentry][1]:X}")
    seek(off)
    for b in range(int(length/4)):
      val = readuint()
      if key != 0 and table[tableentry][1] + b*4 in table[tableentry][2]:
        #print(f"filepos: {(filepos + overlaystart):X}  tab: {(table[t][1] + b*4):X} op: {val:08X}")
        #match (val >> 24) & 0xFC:
        #  case 0x3C:
        #    print(f"0x3C load hi arg {(val & 0xFF):02X}")
        #  case 0x24:
        #    print(f"0x24 load lo arg {(val & 0xFFFF):04X}")
        #  case 0x0C:
        #    print(f"0x0C call arg {((val & 0xFFFFFF)*4):06X}")
        #  case 0x8C:
        #    print(f"0x8C load word arg $gp + {(val & 0xFFFF):04X}")
        #  case 0xAC:
        #    print(f"0xAC stor word arg $gp + {(val & 0xFFFF): 04X}")
        #  case 0x08:
        #    print(f"0x08 jump arg {((val & 0xFFFFFF)*4):06X}")
        continue
      for s in range(seqcount):
        operand = (sequence >> ((seqcount-1-s)*4)) & 0xF
        #print(f"operand is {(sequence >> (s*4))& 0xF}")
        filepos -= 4
        match operand:
          case 0:
            val ^= 0x9F8ED17
            writeuint(val)
          case 1:
            val ^= 0xA95128C3
            writeuint(val)
          case 2:
            val = (val << 0xd) | ((val >> 0x13) & 0x1FFF)
            writeuint(val)
          case 3:
            val = (val << 0x8) | ((val >> 0x18) & 0xFF)
            writeuint(val)
          case 4:
            val = ((val >> 8) & 0xFF) | ((val << 8) & 0xFF000000) | ((val << 0x10) & 0xFF0000) | ((val >> 0x10) & 0xFF00)
            writeuint(val)
          case 5:
            val = (val << 0xd) | ((val >> 0x13) & 0x1FFF)
            val ^= 0x9f8ed17
            writeuint(val)
          case 6:
            val = (val << 0x8) | ((val >> 0x18) & 0xFF)
            val ^= 0xa95128c3
            val = ((val >> 8) & 0xFF) | ((val << 8) & 0xFF000000) | ((val << 0x10) & 0xFF0000) | ((val >> 0x10) & 0xFF00)
            writeuint(val)
          case 7:
            val = ((val << 0x10) & 0xFF0000) | ((val >> 8) & 0xFF) | ((val << 0x8) & 0xFF000000) | ((val >> 0x10) & 0xFF00)
            val = (val << 0xd) | ((val >> 0x13) & 0x1FFF)
            val = (val << 0x8) | ((val >> 0x18) & 0xFF)
            val ^= 0x9f8ed17
            writeuint(val)
      filepos -= 4
      op = readuint()
      #top = (op & 0xFC000000) >> 24
      #match = [0x3C, 0x0C, 0x24, 0x8C, 0x08, 0xAC]
      #if (top in match):
        #print(f"opcode match: {op:08X} at filepos {(filepos + overlaystart):08X}")
      #else:
      #print(f"final opstate is {op:08X}")
    #print("cryption happened!")
    if readuint() != 0x1000000b:
      print("no branch following chunk?")
    else:
      readuint() #branch delay nop
      for i in range(6):
        writeuint(garbo[garbopos])
        garbopos += 1
    #print(f"done encrypting pass at {(filepos+overlaystart):08X}")
    #print("    ")
  return

def loadkeytables():
      global keytables
      with open("tools/keytables.bin", "rb") as file:
        tct = int.from_bytes(file.read(4), byteorder='little')
        #print(f"{tct} tables (should be five)")
        for t in range(tct):
          e = []
          ect = int.from_bytes(file.read(4), byteorder='little')
          for el in range(ect):
            row = []
            row.append(int.from_bytes(file.read(4), byteorder='little')) #key
            row.append(int.from_bytes(file.read(4), byteorder='little')) #size
            act = int.from_bytes(file.read(4), byteorder='little')
            row.append([])
            for ad in range(act):
              row[2].append(int.from_bytes(file.read(4), byteorder='little'))
            e.append(row)
          keytables.append(e)

keytables = []


if __name__ == "__main__":
  if len(sys.argv) == 2: #TODO arg should be -d for decrypt or -e for encrypt
    if sys.argv[1] in ["decrypt", "-d"]:
      filedata = ins_filedata
      extracttables(ins_tableaddrs)
      decrypt(crypt1listing, keytables[0])
      decrypt(crypt2listing, keytables[1])
      decrypt(crypt3listing, keytables[2])
      extractkeys(ins_cryptdata)
      with open("overlays/dnas_ins_noencrypt.bin", "wb") as outfile:
        outfile.write(filedata)
        outfile.flush()
      print(f"ins sha1: {hashlib.sha1(filedata).hexdigest()}")
      filedata = net_filedata
      extracttables(net_tableaddrs)
      decrypt(crypt4listing, keytables[3])
      decrypt(crypt5listing, keytables[4])
      extractkeys(net_cryptdata)
      with open("overlays/dnas_net_noencrypt.bin", "wb") as outfile:
        outfile.write(filedata)
        outfile.flush()
      print(f"net sha1: {hashlib.sha1(filedata).hexdigest()}")
      bytes_out = b""
      for uint in garbo:
        bytes_out += struct.pack("I", uint)
      with open("tools/garbopad.bin", "wb") as outfile:
        outfile.write(bytes_out)
        outfile.flush()
      bytes_out = b""
      for key in keys:
        bytes_out += key
      with open("tools/keys.bin", "wb") as outfile:
        outfile.write(bytes_out)
        outfile.flush()
      #save the keytables?
      with open("tools/keytables.bin", "wb") as outfile:
        outfile.write(len(keytables).to_bytes(4, byteorder='little')) #table count, should be five
        for t in range(len(keytables)):
          ect = len(keytables[t])
          outfile.write(ect.to_bytes(4, byteorder='little'))
          for el in range(ect):
            outfile.write(keytables[t][el][0].to_bytes(4, byteorder='little')) #key
            outfile.write(keytables[t][el][1].to_bytes(4, byteorder='little')) #size
            act = len(keytables[t][el][2])
            outfile.write(act.to_bytes(4, byteorder='little'))
            for ad in range(act):
              outfile.write(keytables[t][el][2][ad].to_bytes(4, byteorder='little'))
        outfile.flush()
      print("done!")
    elif sys.argv[1] in ["inject", "-i"]:
      with open("tools/keys.bin", 'rb') as file:
        keysbin = file.read()
      with open("asm/overlay/dnas_ins/dnas_ins_code.s", 'r') as file:
        codebuf = file.readlines()
      #load the keytables
      loadkeytables()
      #print(keytables)
      injectkeys(ins_cryptdata)
      writetables(ins_tableaddrs)
      with open("asm/overlay/dnas_ins/dnas_ins_code.s", 'w') as outfile:
        outfile.writelines(codebuf)
      with open("asm/overlay/dnas_net/dnas_net_code.s", 'r') as file:
        codebuf = file.readlines()
      injectkeys(net_cryptdata)
      writetables(net_tableaddrs)
      with open("asm/overlay/dnas_net/dnas_net_code.s", 'w') as outfile:
        outfile.writelines(codebuf)
    elif sys.argv[1] in ["encrypt", "-e"]:
      #now we need to reencrypt the bins!
      with open('build/dnas_ins.bin', 'rb') as f:
        ins_filedata = bytearray(f.read())
      with open('build/dnas_net.bin', 'rb') as f:
        net_filedata = bytearray(f.read())
      loadkeytables()
      with open('tools/garbopad.bin', 'rb') as f:
        while True:
          gd = f.read(4)
          if not gd:
            break
          gv = struct.unpack("I", gd)[0]
          garbo.append(gv)
      print(f"garbo uint count: {len(garbo)}")
      filedata = ins_filedata
      encrypt(crypt1listing, keytables[0])
      encrypt(crypt2listing, keytables[1])
      encrypt(crypt3listing, keytables[2])
      with open("build/dnas_ins.bin", "wb") as outfile:
        outfile.write(filedata)
        outfile.flush()
      filedata = net_filedata
      encrypt(crypt4listing, keytables[3])
      encrypt(crypt5listing, keytables[4])
      with open("build/dnas_net.bin", "wb") as outfile:
        outfile.write(filedata)
        outfile.flush()
    elif sys.argv[1] in ["null", "-n"]:
      print("leaving unencrypted")
    else:
      print(f"bad arg {sys.argv[1]}")
  else:
    print("missing arg")
