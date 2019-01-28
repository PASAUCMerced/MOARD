#!/bin/bash

# a function to check if an envir variable exists or not
#
existOrnot()
{
  [ -z $1 ] && echo "Need to set on $2 !" && return;
}

# This is a bash file to handle the LLVM-Tracer execution 
#
#[ -z "$BENCHMARK" ] && echo "Need to set BENCHMARK, the name of your application with lowercase!" && return;
#[ -z "$WORKLOAD" ] && echo "Need to set WORKLOAD, the target function of your application!" && return;
#[ -z "$LLVM_HOME" ] && echo "Need to set LLVM_HOME, the location of your llvm-3.4.2 library!" && return;
#[ -z "$MOARD_HOME" ] && echo "Need to set MOARD_HOME, the location of the current working station!" && return;
#[ -z "$TAR_DATA" ] && echo "Need to set TAR_DATA, the target data object that you want to understand its resilience within the function ${WORKLOAD} of your application ${BENCHMARK}!" && return;
#[ -z "$GCC_INSTALL_HOME" ] && echo "Need to set GCC_INSTALL_HOME, the location of your gcc-4.7.3+ compiler!" && return;
#[ -z "$ERR_PROP_THRESHOLD" ] && echo "Set the error propagation threshold ERR_PROP_THRESHOLD (the default is 10)!" && return;
#[ -z "$FAULT_MASK_THRESHOLD" ] && echo "Set the fault shadowing threshold FAULT_MASK_THRESHOLD (the default value is 0.001)!" && return;

existOrnot "$BENCHMARK" "BENCHMARK"
existOrnot "$WORKLOAD" "WORKLOAD"
existOrnot "$LLVM_HOME" "LLVM_HOME"
existOrnot "$MOARD_HOME" "MOARD_HOME"
existOrnot "$TAR_DATA" "TAR_DATA"
existOrnot "$GCC_INSTALL_HOME" "GCC_INSTALL_HOME"
existOrnot "$ERR_PROP_THRESHOLD" "ERR_PROP_THRESHOLD"
existOrnot "$FAULT_MASK_THRESHOLD" "FAULT_MASK_THRESHOLD"
existOrnot "$LLVM_PATH" "LLVM_PATH"


export TRACER_HOME=${MOARD_HOME}/llvm-tracer/

echo "Step 1: running the llvm-tracer to generate the trace of the function ${WORKLOA} ... "
cd $TRACER_HOME/example/$BENCHMARK
make -f Makefile clean
make -f Makefile
gzip -d *.gz 
mv dynamic_trace ../../../tracefile/


# please note that here we usually partition the dynamice trace file into pieces
# and then move them all to the tracefile directory. These pieces will be processed
# one by one by the trace analysis tool.
#[ -z "$INI_ADDR_ON_TDD" ] && echo "Printf the memory address of the data object while trace generation, then setting the memory address of the data object ${TAR_DATA} here!" && return;
echo "Step 2: running the trace analysis tool to analyze the resilience of individual data objects of the application ${BENCHMARK} ... "
cd ../../../
export INI_ADDR_ON_TDD=$(<INI_ADDR_ON_TDD.txt) 
export FAULT_INJECTION_RESULT_DIR=${MOARD_HOME}/faultInjectionSites/renewFaultInjectionSites/
echo "the target memory address is: $INI_ADDR_ON_TDD"
existOrnot "$INI_ADDR_ON_TDD" "INI_ADDR_ON_TDD"
cd traceAnalysisTool_1.2/

echo "Set the address on the data object ${TAR_DATA} on ${BENCHMARK} benchmark as $INI_ADDR_ON_TDD..."
export SERIAL_NUM=${BENCHMARK}'_'${TAR_DATA}
echo ${SERIAL_NUM}
./oneFileRunning.sh


echo "Step 3: starting doing fault injection into the deterministic fault injection sites ..."
export WORK_FUNC=$WORKLOAD
cd ../faultInjectionSites/
python fault_sites_sampling.py
cd ../benchmark_working_station/${BENCHMARK}/
./acquire_enviro_info.sh

echo "Step 4: rerunning the trace analysis tool to get the final results on ${TAR_DATA}"
cd ../traceAnalysisTool_1.2/
./oneFileRunning.sh
echo "the resilience report for the target data object ${TAR_DATA}" is under result_collection directory ... "
cd ..
echo "the result is as follows: "
cat result_collection/dvf_counters_$BENCHMARK_*


