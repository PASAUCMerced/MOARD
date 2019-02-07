# MOARD-0.1: a tool for application resilience study on individual data objects 
====================================================================================

MOARD is a resilience modeling tool 
measuring the resilience of an application from the individual data objects within 
the application. The core of MOARD is a trace analysis tool. The current version
is open sourced for the artifact evaluation of SC'18 conference. Here we will explain
how to build to use our tool and the general workflow. For more methodology details, 
please read our IPDPS'19 paper (MOARD: Modeling Application Resilience to Transient 
Faults on Data Objects). Please cite our work using the following BIBTEX: 

```
@inproceedings{guo2019moard,
  title={MOARD: Modeling Application Resilience to Transient Faults on Data Objects},
  author={Guo, Luanzheng and Li, Dong},
  booktitle={{IEEE International Parallel Distributed Processing Symposium (IPDPS)}},
  year={2019},
  organization={IEEE Press}
}
```

- General Description:
====================================================================================
The overall target is to compute the aDVF(application-level Data Vulnerability Factor)
for a given data object in an application. At first, MOARD generate the dynamic trace of 
the function where the data object operated on, with the trace generation tool, 
LLVM-Tracer(an open source tool to generate the dynamic trace, https://github.com/ysshao
/LLVM-Tracer). The dynamic trace is then fed to the trace analysis module of MOARD as an
input. In the trace analyses, we classify fault masking events into three levels (i.e., 
the operation-level, the fault propagation-level, and the algorithm-level), and further 
break down the fault masking events at the operation level into three categories (i.e., 
value overwriting, value shadowing, and logical and comparison operations) to count the 
number of fault maskings on the given data object. If a fault masking cannot be determined
at the fault propagation boundary, we use algorithm-level analysis by triggering a fault 
into the data object at the current operation. And then we will know if the fault is masked
or not at the end of application execution with the fault injection. Finally, the determined
result (i.e., fault masked or not) of the fault is returned back to the trace analysis 
module for computing the aDVF value of the given data object. 


- The program: c++, shell, python

- Compilation: Compiling with clang-3.4.2, clang-3.8.1 and gcc-4.7.3

- Data sets: SNU C-version NPB benchmark suite, LULESH and AMG. All datasets are provided 
along MOARD source code, but they can also be downloaded from 
http://aces.snu.ac.kr/software/snu-npb/ and https://codesign.llnl.gov/proxy-apps.php

- Run-time environment: any Linux/Unix system

- Hardware: There is no hardware dependency to use MOARD

- Input: an application and a given data object in the application

- Output: the aDVF (i.e., the application-level Data Vulnerability Factor) value of given data 
objects within an application

- Software: MOARD requires LLVM-3.4.2 library, LLVM-3.8 library, clang-3.4.2, clang-3.8, and 
gcc-4.7.3 or above


- Installation:
====================================================================================
a. download the MOARD-0.1 package from the git repository

	$ git clone https://LNLLSC17@gitlab.com/LNLLSC17/MOARD-0.1.git

b. Set environment variables, including the path and name of your application and the name 
of your target data objects.

	$ export LLVM_HOME=/your/path/to/LLVM/ installation
	$ export LLVM_PATH=/path/of/llvm-3.8.0
	$ export MOARD_HOME=/your/path/to/MOARD
	$ export GCC_INSTALL_HOME=/your/path/to/gcc
	$ export BENCHMARK=/name/of/your/application/
	$ export WORKLOAD=/name/of/target/function
	$ export TAR_DATA=/name/of/target/data/object/
	$ export INI_ADDR_ON_TDD=/initial/memory/address/of/target/data/object
	$ export ERR_PROP_THRESHOLD=/error/propagation/threshold
	$ export FAULT_MASK_THRESHOLD=/fault/shadowing/threshold

c. Change your application by adding the following code into your application to expose the 
addresses of target data objects into an environment variable (INI_ADDR_ON_TDD).	
	
	> FILE *tmp=fopen("INI_ADDR_ON_TDD.txt", "w+");	
	> fprintf(tmp, "%ld", the memory address of the target_obj);
	> fclose(tmp);

d. Go to the main directory of MOARD (MOARD HOME). You will find a shell script called MOARD_EXE.sh.
Run it with the following command. Then you can see the aDVF value of the target data object. 
If you miss one of the above environment variables, the script will remind you to set it.
	
	$ cd MOARD-0.1	
	$ source MOARD_EXE.sh


- Experiment Workflow:
====================================================================================
In the installation section, we use a single shell script MOARD_EXE.sh to hide all computation 
details from users. However, for a user who wants to examine the tool and run the aDVF 
calculation step by step. You can use the following experiment workflow.

a. Generate a dynamic LLVM trace of your application. You need to tell MOARD your target function 
and the data objects within the function that you want to calculate aDVF for. We use 
LLVM-Tracer(https://github.com/ysshao/LLVM-Tracer), an open source tool to generate the dynamic 
trace.
	
	$ export WORKLOAD, LLVM_HOME, GCC_INSTALL_HOME as requested by LLVM-Tracer	
	$ cd llvm-tracer/full-trace
	$ make clean; make
	$ cd llvm-tracer/example
	$ cd /the/target/benchmark/directory
	$ make clean; make

b. Copy the dynamic trace to a directory named “tracefile” in the MOARD directory.

c. Run the trace analysis tool. There are three versions of the trace analysis tool. There are 
slight differences between the three, some bugs are fixed in the advanced version 1.2 when the 
inputs become more complicated. We suggest the 1.2 version. In this version, there are three 
scripts to run the trace analysis tool. Please read the traceAnalysisTool/ReadM.txt carefully 
to run those scripts. Typically you start from the first script, oneFileRunning.sh.
	
	$ cp llvm-tracer/example/benchmark/dynamic_trace  MOARD-0.1/tracefile	
	$ cd MOARD-0.1/traceAnalysisTool_1.2
	$ export INI_ADDR_ON_TDD, ERR_PROP_THRESHOLD, FAULT_MASK_THRESHOLD
	$ export SERIAL_NUM=$BENCHMARK_$TAR_DATA
	$ ./oneFileRunning.sh

This step will generate three result files: the fault injection file, dvf-counter file, and 
fault-masking-event file. The fault-injection file contains a list of deterministic fault 
injection sites for fault injection in the next step. The other two files will be used in Step 
4 by some scripts. As a user, you do not need to take care of the two files.

d. In this step, we do deterministic fault injection based on the fault injection file produced 
in Step 3. We need to use LLVM-3.8.0 to build the deterministic fault injection tool. Change 
Makefile in MOARD to specify the LLVM-3.8.0 path. Build and run the fault injection tool by running 
acquire_enviro_info.sh.
	
	$ cd MOARD-0.1/src
	$ export LLVM_PATH=/path/of/llvm-3.8.0
	$ export WORK_FUNC=/name/of/target/function
	$ make clean; make
	$ cd faultInjectionSites
	$ python fault_sites_sampling.py
	$ cd benchmark_working_station/benchmark/
	$ ./acquire_enviro_info.sh
	$ export FAULT_INJECTION_RESULT_DIR=$MOARD_HOME/faultInjectionSites/renewFaultInjectionSites/

After each deterministic fault injection, a script refresh fm states.py must be triggered to update 
a column (particularly the fault masking state column) within the fault injection file, if the 
injected fault is masked after the fault injection. For those benchmarks included in the MOARD 
package, they are patched to call the script. However, for a new application, the user must add the 
following code into the verification phase of the application to trigger the script.
	
	> system("python refresh_fm_states.py");

e. Rerun the trace analysis tool. The trace analysis tool will check FAULT_INJECTION_RESULT_DIR 
(see above for FAULT_INJECTION_RESULT_DIR) to make a decision if the current step is Step 3 or 
Step 5. If FAULT_INJECTION_RESULT_DIR is not empty, then the trace analysis tool reads the updated 
fault injection file for Step 5.
	
	$ cd MOARD-0.1/traceAnalysisTool_1.2	
	$ ./oneFileRunning.sh
	$ rm $MOARD_HOME/faultInjectionSites/renewFaultInjectionSites/*

The final results are two files: the dvf-counter file and fault-masking-event file. These two files 
include the information from the old version of the two files generated in Step 3. The dvf-counter 
file contains opcode distribution, a breakdown of aDVF at the three fault masking levels, and a 
breakdown of the operation level analysis classified into three fault masking types.

The other notes:
====================================================================================
The dynamic instruction trace generated by LLVM-Tracer can be large. We have some scripts to help 
you optimize the above steps and accelerate analysis during the experiments. You can find those 
scripts in MOARD-0.1/aid\_scripts. Please refer to the ReadMe.txt under the aid_scripts directory
for more detailed instruction.

====================================================================================
Copyright (c) 2016-2020

