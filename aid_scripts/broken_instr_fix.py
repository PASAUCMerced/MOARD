# trace block could be divided into two parts in two subfiles,
# which is incorrect. The entire trace block must be in the 
# same file. A trace block represents the information for a 
# dynmaic instruction. Each trace block is separated by blank
# line in the dynamic trace file.

import os

# define your working path
DIR_PATH = "./final_version_split_bt_trace/"

tmp_block = []
lines = ['\n']
_file_num = 0

def if_first_line_of_block(line):
  contents = line.split(',')
  return



for root, dirs, files in os.walk(DIR_PATH, topdown=False):
  files.sort()
  files.reverse()
  _file_num = len(files)
  for i in range(0, _file_num - 1): # no need to check the first file
    print "Reading ", files[i], ' ', (i+1), "/", _file_num
    with open(DIR_PATH + files[i], 'r+') as rf:
      # Read till reach one first line of block
      line = rf.readline()
      while not(line.startswith('0,')):
        if line != '\n':
          tmp_block.append(line)
        line = rf.readline()

      # if tmp_block has more than one line, 
      # this file not begin with a brand new block
      if len(tmp_block) > 0:
        # Append the contents into the previous file
        print "--Brocken part found, appendding it to ", files[i+1]
        with open(DIR_PATH + files[i+1], 'a') as wf:
          wf.write(''.join(tmp_block))
          tmp_block = []
        # delete the duplicated party of original file
        print "--Deleting brocken part in ", files[i]
        lines.append(line)
        lines = lines + rf.readlines()
        with open(DIR_PATH + files[i], 'w') as rbf:
          rbf.write(''.join(lines))
        lines = ['\n']

      else:
        print "--Perfect file, no work need to do."

