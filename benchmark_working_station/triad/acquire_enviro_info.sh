#!/bin/bash
#
# SCRIPT: cquire_enviro_info.sh
# read the fault injection sites from fault-injection-info files 
# line by line, and then export these info to enviroment varialbes
#

echo "start to read fault injection info ... "

#
for file in ../../faultInjectionSites/sampFaultInjectionSites/*; do
# make changes here after then *aa ->*
  filename=$(basename "$file");
  #echo "Processing $filename line by line ..."
  while read line; do
  	wordcounter=0;
	#echo -e "$wordcounter\n";
    for word in $line; do
	  #echo -e "$word\n";
	  wordcounter=$((wordcounter+1));
	  #echo -e "current word counter for word: $wordcounter\n";
	  case $wordcounter in
	    1) export OPRAND_ID=2;; 
		2) export BIT_POSITION=3;;
		3) export DYN_INSTR_ID=2;;
		4) export STATIC_INSTR_ID=6;;
		5) export OPCODE_ID=29;;
	    7) export REG_NAME='a';;
	  esac
	  echo -e "export test: oprandID - $OPRAND_ID \n";
	  #echo -e "export test: bitPosition - $bitPosition \n";
	  #echo -e "export test: dynInstrID - $dynInstrID \n";
	  #echo -e "export test: staticInstrID - $staticInstrID \n";
	  #echo -e "export test: opcodeID - $opcodeID \n";
	  #echo -e "export test: regName - $regName \n";
	done
    #echo -e "$line\n\n"; 
	#
	# one fault injection test should be done for each line of the file
	#command1='make clean';
	make -f Makefile clean || exit;
	make -f Makefile || exit;
	./full-opt
	#make -f Makefile clean || exit;
  done < $file 
done
cp ../../faultInjectionSites/renewFaultInjectionSites/* ../../midd_file/  
