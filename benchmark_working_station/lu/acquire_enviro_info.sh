#!/bin/bash
#
# SCRIPT: cquire_enviro_info.sh
# read the fault injection sites from fault-injection-info files 
# line by line, and then export these info to enviroment varialbes
#

rm ../../faultInjectionSites/renewFaultInjectionSites/*;
cp ../../faultInjectionSites/orgFaultInjectionSites/* ../../faultInjectionSites/renewFaultInjectionSites/;

echo "start to read fault injection info ... "

#
for file in ../../faultInjectionSites/sampFaultInjectionSites/*; do
  filename=$(basename "$file");
  echo "Processing $filename line by line ..."
  while read line; do
  	wordcounter=0;
	#echo -e "$wordcounter\n";
    for word in $line; do
	  #echo -e "$word\n";
	  wordcounter=$((wordcounter+1));
	  #echo -e "current word counter for word: $wordcounter\n";
	  case $wordcounter in
	    1) export OPRAND_ID=$word;; 
		2) export BIT_POSITION=$word;;
		3) export DYN_INSTR_ID=$word;;
		4) export STATIC_INSTR_ID=$word;;
		5) export OPCODE_ID=$word;;
	    7) export REG_NAME=$word;;
	  esac
	  echo -e "export test: oprandID - $OPRAND_ID \n";
	  echo -e "export test: bitPosition - $BIT_POSITION \n";
	  echo -e "export test: dynInstrID - $DYN_INSTR_ID \n";
	  echo -e "export test: staticInstrID - $STATIC_INSTR_ID \n";
	  echo -e "export test: opcodeID - $OPCODE_ID \n";
	  echo -e "export test: regName - $REG_NAME \n";
	done
    #echo -e "$line\n\n"; 
	#
	# one fault injection test should be done for each line of the file
	#command1='make clean';
	make -f Makefile clean;
	make -f Makefile;
	./lu-instrumented
	#make -f Makefile clean || exit;
  done < $file 
done

cp ../../faultInjectionSites/renewFaultInjectionSites/* ../../midd_file/  
