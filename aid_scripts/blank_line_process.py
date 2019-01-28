# the format of each subfile must follow the format of the dynamic
# trace file before partition. The special format is that there 
# must have a blank line at the head of a subfile but no blank line 
# at the end of a subfile. 

import os
DIR_PATH = "./final_version_split_bt_trace/"

for root, dirs, files in os.walk(DIR_PATH):
  files.sort()
  file_num = len(files)

  # append contents to target file
  for i in range(0, file_num):
  # for i in range(1, 2):
    print "Working with: ", (i+1), "/", file_num, ' ', files[i]
    with open(DIR_PATH+files[i], "r") as f:
      lines = f.readlines()
      cnt_line = len(lines)
      # cross the blank line at end out
      if lines[cnt_line-1] == '\n':
        lines = lines[:-1]
      # if there is no blank line at the front
      # insert a blank line there
      if lines[0].startswith('0,'):
        lines.insert(0, '\n')

    with open(DIR_PATH+files[i], "w") as ff:
      ff.write(''.join(lines))

print("Finished...")
