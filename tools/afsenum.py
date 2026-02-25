filenames = []
filenum = 0
with open("tools/AFS_files.txt", 'r') as f:
  for line in f:
    filenames.append("    "+line.split()[0].replace(".", "_")+", //"+hex(filenum))
    filenum+=1

output = ""

output += """#ifndef FILES_H
#define FILES_H

typedef enum {
"""

output += "\n".join(filenames)

output += """
    NONE = -1
} FILES;

#endif"""

#print(output)
with open("include/files.h", "w") as f:
  f.write(output)
print("dumped afs list to include/files.h")
