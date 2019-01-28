import pdb
import os

DIR_PATH = "../../faultInjectionSites/renewFaultInjectionSites/"
pdb.set_trace()
operandID=os.environ['OPRAND_ID']
bitID=os.environ['BIT_POSITION']
sInstID=os.environ['STATIC_INSTR_ID']
opcodeID=os.environ['OPCODE_ID']

for root, dirs, files in os.walk(DIR_PATH):
	files.sort()
	file_num = len(files)

	# processing files one by one
	for i in range(0, file_num):
	  print("Working with: ", files[i])

	  # fetch line
	  w_file = DIR_PATH + files[i]
	 
	  lines = [] 
	  with open(w_file, 'r') as file_r:
	      for line in file_r:
	        if len(line) > 0:
		  list1 = list(line)
		  spLine = line.split()
  		  #print spLine
		  if spLine[0] == operandID and spLine[1] == bitID and spLine[3] == sInstID and spLine[4] == opcodeID:
		     #line = line.replace(' 0 ', ' 1 ')
		     list1[-5] = '1'
                     line = ''.join(list1)
		  lines.append(line)
                  print line
          with open(w_file, 'w') as file_w:
	      for line in lines:
		 file_w.write(line)

