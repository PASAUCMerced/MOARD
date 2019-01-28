# merge the aDVF result files into one reuslt file, because
# the result files are generated from the sub-tracefiles of
# the original trace file. There should be only one result 
# file for the original dynamic trace file.

import math
import os

# define your working path
DIR_PATH = "./files_to_merge/"
# define your target path
DST_PATH = "./"
# define your destination file prefix
DST_FILE = "merged_info.txt"

dvf = []
dvf_sum = 0
dvf_num = 0
dvf_ratio = 0
dvf_opcode = []

for root, dirs, files in os.walk(DIR_PATH):
  for file in files:
    with open(DIR_PATH + file, 'r') as f:
      dvf = f.readline().split(' ')
      dvf_sum += float(dvf[1])
      dvf_num += int(dvf[3])
      dvf_opcode.append(f.read())
    f.close()

dvf_ratio = dvf_sum / dvf_num

with open(DST_PATH + DST_FILE, "w+") as merged_info:
  info = "dvf_sum: " + str(dvf_sum) + " dvf_num: " + str(dvf_num) + " dvf_ratio: " + str(dvf_ratio) + '\n'
  merged_info.write(info)
  for cnt in dvf_opcode:
    merged_info.write(cnt)


