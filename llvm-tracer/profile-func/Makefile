LLVM_HOME?=PLEASE_SET_LLVM_HOME_ENVIRONMENT_VARIABLE
LLVM_SRC=$(LLVM_HOME)/llvm-src
LLVM_BIN=$(LLVM_HOME)/

#CFLAGS=-O3
CFLAGS= -O3 -fPIC -I/usr/include/c++/4.8.1/ -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS 
#CFLAGS= -O3 -fPIC -std=c++11 -I/usr/include/c++/4.8.1/ -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS 
#CFLAGS= -O3 -fPIC -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS 
#CFLAGS= -O1 -fno-slp-vectorize -fno-vectorize -fno-unroll-loops -fno-inline

trace_logger.llvm: trace_logger.c
	$(LLVM_BIN)/bin/clang $(CFLAGS) -S -emit-llvm trace_logger.c -o trace_logger.llvm	
	#$(LLVM_BIN)/bin/clang++ $(CFLAGS) -S -emit-llvm -c trace_logger.c -o trace_logger.llvm #this is a bad case that results in the 'undefined reference' errors!!
clean:
	rm -f trace_logger.llvm
