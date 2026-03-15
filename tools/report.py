from dataclasses import dataclass, field
import pprint
import json

GAME = "SLPM_654.95"
CONSOLELOG = 0
REPORTLOG = 0

@dataclass
class Measure:
  fuzzy_match_percent: float = 0
  total_code: int = 0
  matched_code: int = 0
  matched_code_percent: float = 0
  total_data: int = 0
  matched_data: int = 0
  matched_data_percent: float = 0
  total_functions: int = 0
  matched_functions: int = 0
  matched_functions_percent: float = 0
  #complete_code: int = 0
  #complete_code_p: float = 0
  #complete_data: int = 0
  #complete_data_p: float = 0
  total_units: int = 0
  #complete_units: int = 0

@dataclass(kw_only=True)
class Category:
  id: str = ""
  name: str = ""
  measures: Measure

@dataclass
class Section:
  name: str = ""
  size: int = 0
  fuzzy_match_percent: float = 0
  parent: str = ""

@dataclass
class Function:
  name: str = ""
  size: int = 0
  fuzzy_match_percent: float = 0
  address: int = 0

@dataclass
class UnitMeta:
  complete: bool = False
  source_path: str = "foo/bar.c"
  progress_categories: list[str] = "" #this is the id string of the category?

@dataclass(kw_only=True)
class Unit:
  name: str = ""
  measures: Measure
  sections: list[Section] = field(default_factory=list)
  functions: list[Function] = field(default_factory=list)
  metadata: UnitMeta

@dataclass(kw_only=True)
class Report:
  measures: Measure
  units: list[Unit] = field(default_factory=list)
  version: int = 2
  categories: list[Category] = field(default_factory=list)

@dataclass
class MapUnit:
  name: str = ""
  sections: list[Section] = field(default_factory=list)
  functions: list[Function] = field(default_factory=list)
  datasize: int = 0
  rdatasize: int = 0
  sdatasize: int = 0
  sbsssize: int = 0
  bsssize: int = 0
  path: str = ""

@dataclass
class MapOverlay:
  name: str = ""
  units: list[MapUnit] = field(default_factory=list)

#first, we shall open the .xmap file
file = []
with open("build/"+GAME+".xMAP", 'r') as f:
  file = f.readlines()
#for each overlay, populate a MapOverlay with the units?
#as you scan each line, only use lines with a size! [address] [size] [type] [name] [(source)]?
savedOverlay = ""
savedTU = ""
savedSection = ""
savedpos = 0
mapdata = []
mo = MapOverlay()
mu = MapUnit()
ms = Section()
for l in file:
  v = l.split()
  ln = len(v)
  if(ln < 2):
    continue
  if(v[1].startswith(".")):
    #new overlay, save existing (if not initial) and set up new MapOverlay and MapUnit
    if(savedOverlay != ""):
      if(savedTU != ""):
        if(savedSection != ".text" and ms.name != ""):
          matched = False
          #save the section!
          for u in mo.units:
            if(u.name[:-2] == ms.parent.split(".")[0]):
              u.sections.append(ms)
              #print("  matched " + ms.name + " for " + ms.parent + " (1st)")
              matched = True
              break
          if(not(matched)):
            #no matching .text section, make a new one
            u = MapUnit(name = ms.parent.split(".")[0])
            u.sections.append(ms)
            mo.units.append(u)
            #print("  created " + ms.name + " section for " + ms.parent + " (1st)")
          savedSection = ms.name
          savedSection = ""
          #ms.name = ""
        elif(savedSection == ".text"):
          mo.units.append(mu)
      mapdata.append(mo)
    mo = MapOverlay(name=v[1][1:])
    #print(mo.name)
    savedOverlay = mo.name
    savedTU = ""
  if(ln < 5):
    continue
  if(v[2].startswith(".")):
    #this is a symbol entry
    #if different from prior, save (if not text)
    size = int(v[1], 16)
    if(size > 0):
      #it's a real object, add it to our MapUnit?
      if(v[2] != savedSection):
        #just changed section! save the old if applicable
        if(savedSection != "" and savedSection != ".text" and ms.name != ""):
          matched = False
          for u in mo.units:
            if(u.name[:-2] == ms.parent.split(".")[0]):
              u.sections.append(ms)
              #print("  matched " + ms.name + " for " + ms.parent + " (2nd)")
              matched = True
              break
          if(not(matched)):
            #no matching .text section, make a new one
            u = MapUnit(name = ms.parent.split(".")[0])
            u.sections.append(ms)
            mo.units.append(u)
            #print("  created " + ms.name + " section for " + ms.parent + " (2nd)")
          #ms.name = ""
          #print("saved old section")
        #print("new section!")
        if(savedSection == ".text"):
          mo.units.append(mu)
        if(v[2] != ".text"):
          #if new section isn't text, set up the section!
          ms = Section(name = v[2], fuzzy_match_percent = 0, parent = v[4][1:-1])
          #print("found section " + v[2])
        else:
          mu = MapUnit(name = v[4][1:-3])
        savedSection = v[2]
      if(v[4] != savedTU): #filename change, set up the unit?
        if(savedTU != ""):
          if(savedSection == ".text"):
            mo.units.append(mu)
            mu = MapUnit(name = v[4][1:-3])
            #print(" "+ mu.name)
          else:
            if(ms.size != 0):
              matched = False
              for u in mo.units:
                if(u.name[:-2] == ms.parent.split(".")[0]):
                  u.sections.append(ms)
                  #print("  matched " + ms.name + " for " + ms.parent + " (3rd)")
                  matched = True
                  break
              if(not(matched)):
                #no matching .text section, make a new one
                u = MapUnit(name = ms.parent.split(".")[0])
                u.sections.append(ms)
                mo.units.append(u)
                #print("  created " + ms.name + " section for " + ms.parent + " (3rd)")
            ms = Section(name = v[2], fuzzy_match_percent = 0, parent = v[4][1:-1])
            #print("found section " + v[2])
        #set up a new MapUnit
        savedTU = v[4]
        savedpos = int(v[0], 16)
      #save + new done, now handle this entry
      #.text get added as a full func, others just have their size totaled?
      if(v[2] == ".text"):
        #if(ms.name != ""):
          #new section is text, clear saved section if present
          #ms.name = ""
        #add new func entry
        func = Function(name=v[3], size = int(v[1], 16), address = int(v[0], 16) - savedpos)
        if(v[4].endswith(".s.o)")):
          #guaranteed unmatched, no C file yet
          func.fuzzy_match_percent = 0
        elif(v[4].endswith(".c.o)")):
          #open the src/ c file and check if it's got an INCLUDE_ASM line that ends with v[3] plus );
          tulines = []
          fname = "src/" + mo.name + "/" + v[4][1:-3]
          #print("  opening " + fname)
          with open(fname, 'r') as tu:
            tulines = tu.readlines()
          func.fuzzy_match_percent = 100 #so far i've only been inserting "done" funcs
          for line in tulines:
            if(line.startswith("INCLUDE_ASM") and (v[3] in line)):
              #print("undecomped: " + line)
              func.fuzzy_match_percent = 0
              break
            #elif(v[3] in line):
              #print("func ref: " + line)
        else:
          print("unknown text filetype?")
          continue
        mu.functions.append(func)
        continue
      else:
        ms.size += size
        #add up size totals
        continue
      #print("  "+ v[3] + "  size: " + hex(size))
#save the current TU we're looking at, if current is different from last then update our listing!
#mo.units.append(mu)
mapdata.append(mo)
#then once our listing is populated, begin populating the report, calcing values as needed.
if(CONSOLELOG > 0):
  print("overlays found: " + str(len(mapdata)))
#print(mapdata[0].name)
#print("TUs present: " + str(len(mapdata[0].units)))
#print(mapdata[0].units[1].name)
#print("funcs present in 2nd TU: " + str(len(mapdata[0].units[1].functions)))
#print(mapdata[0].units[1].functions[0].name)
if(CONSOLELOG > 0):
  for o in mapdata:
    print(o.name)
    if(CONSOLELOG > 1):
      for u in o.units:
        size = 0
        for f in u.functions:
          size += f.size
        print(" " + u.name + " (" + str(len(u.functions)) + "):" + hex(size))
        if(CONSOLELOG > 2):
          for s in u.sections:
            print("  " + s.name + ":" + hex(s.size))

#now that mapdata has all our needed data, let's generate a report log?
report = Report(measures = Measure())
rm = Measure()
for o in mapdata:
  #need to generate the measures!
  om = Measure()
  for tu in o.units :
    ru = Unit(name = tu.name, metadata = UnitMeta(), measures = Measure())
    rum = Measure()
    for mf in tu.functions:
      ru.functions.append(mf)
      rum.total_code += mf.size
      rum.matched_code += int(mf.size*mf.fuzzy_match_percent/100)
      rum.total_functions += 1
      rum.matched_functions += (1 if mf.fuzzy_match_percent == 100 else 0)
    if(rum.total_functions > 0):
      rum.matched_functions_percent = rum.matched_functions / rum.total_functions * 100
    rum.total_units = 1
    #don't forget the sections now
    for ms in tu.sections:
      ru.sections.append(ms)
      rum.total_data += ms.size
      rum.matched_data += int(ms.size*ms.fuzzy_match_percent/100)
    if(rum.total_data > 0):
      rum.matched_data_percent = rum.matched_data / rum.total_data * 100
    #and metadata!
    umeta = UnitMeta(source_path = o.name+"/"+tu.name, progress_categories = [o.name])
    if(rum.matched_data_percent == 100 and rum.matched_code_percent == 100):
      umeta.complete = True
    ru.measures = rum
    ru.metadata = umeta
    report.units.append(ru)
    #now update the overlay's measures
    om.total_code += rum.total_code
    om.matched_code += rum.matched_code
    om.total_functions += rum.total_functions
    om.matched_functions += rum.matched_functions
    om.total_data += rum.total_data
    om.matched_data += rum.matched_data
    om.total_units += rum.total_units #always += 1
  #done with all the units in the overlay, calc final measures
  if(om.total_functions > 0):
    om.matched_functions_percent = om.matched_functions / om.total_functions * 100
  if(om.total_code > 0):
    om.matched_code_percent = om.matched_code / om.total_code * 100
  if(om.total_data > 0):
    om.matched_data_percent = om.matched_data / om.total_data * 100
  #then add the data to the report
  oc = Category(id=o.name, name=o.name, measures = Measure())
  oc.measures = om
  report.categories.append(oc)
  #add overlay measures to top-level report?
  rm.total_code += om.total_code
  rm.matched_code += om.matched_code
  rm.total_data += om.total_data
  rm.matched_data += om.matched_data
  rm.total_functions += om.total_functions
  rm.matched_functions += om.matched_functions
  rm.total_units += om.total_units
  if(rm.total_code > 0):
    rm.matched_code_percent = rm.matched_code / rm.total_code
  if(rm.total_data > 0):
    rm.matched_data_percent = rm.matched_data / rm.total_data
  if(rm.total_functions > 0):
    rm.matched_functions_percent = rm.matched_functions / rm.total_functions
report.measures=rm

if(REPORTLOG > 0):
  pprint.pprint(report.measures)
  for o in report.categories:
    pprint.pprint(o)
if(REPORTLOG > 1):
  for tu in report.units:
    for f in tu.functions:
      if(f.fuzzy_p == 100):
        pprint.pprint(f)

with open("tools/report.json", 'w') as file:
  file.write(json.dumps(report, default=lambda o: o.__dict__, indent=2))

print("report generated for " + GAME + "!")
