# This is a bug on PHI instructions in the LLVM-Tracer. 
# The operand value is not consistent on PHI instructions
# with the previous instructions.

import os
DIR_PATH = "/home/hhe3/temp_test/mg_temp/mg_split"
THRESHOLD = 1000
for root, dirs, files in os.walk(DIR_PATH):  #for name in files:	#print(name)
  for name in files:
    print("Working with: ", name)
# begin algorithm for single file
    _orgnl_file = DIR_PATH + name
    _fixed_file = _orgnl_file + "_fixed.txt"
    phi_blocks = []
    tmp_phi = []
    len_phi = 0
    not_found = True
    # read data
    with open(_orgnl_file, "r") as f_orgnl:
      lines_orgnl = f_orgnl.readlines()
    f_orgnl.close()
    # store data in a structure form
    lines_orgnl.append('\n') # ensure to put the last block
    for line_orgnl in lines_orgnl:
      if(line_orgnl != "\n"):
        tmp_phi.append(line_orgnl.split(','))
      else:
        if(tmp_phi != []):
          phi_blocks.append(tmp_phi)
          tmp_phi = []
    # print(phi_blocks)
    # find the blocks need to be fixed
    len_phi = len(phi_blocks)
    for i in range(0, len_phi):
      if(phi_blocks[i][0][1] == "-1" and phi_blocks[i][0][5] == "48"):
        # find the wrong value need to be fixed
        len_line_err = len(phi_blocks[i]) # err short for error block needed to be fixed
        		for line_err in range(1, len_line_err):
          if(phi_blocks[i][line_err][0] != 'r' and phi_blocks[i][line_err][3] == '1'):
            info_size = phi_blocks[i][line_err][1]
            info_reg_name = phi_blocks[i][line_err][4]
            # trace back to find the error
            j = i - 1
            not_found = True
            while (i - j < THRESHOLD and j > -1 and not_found):
              len_line_cand = len(phi_blocks[j]) # cand short for candidate blocks for compare
              for line_cand in range(1, len_line_cand):
                if phi_blocks[j][line_cand][3] == '1' and info_size == phi_blocks[j][line_cand][1] and info_reg_name == phi_blocks[j][line_cand][4]:
                  phi_blocks[i][line_err][2] = phi_blocks[j][line_cand][2]
                  not_found = False
              j = j - 1
            # end of fix loop. If didn't find it, no change will apply to the phi block.
    # end of algorithm
    # write fixed data
    with open(_fixed_file, "w") as f_fixed:
      for block in phi_blocks:
        for line in block:
          f_fixed.write(','.join(line))
        f_fixed.write('\n')
      f_fixed.close()
# end algorithm for single file
