#export WORK_FUNC=solve
#export LLVM_PATH=/opt/pasa_lib/llvm-3.8.0/bin
WORK_FUNC?=PLEASE_SET_WORK_FUNC
LLVM_PATH?=PLEASE_SET_LLVM_PATH
OPRAND_ID?=PLEASE_SET_OPRAND_ID
BIT_POSITION?=PLEASE_SET_BIT_POSITION
DYN_INSTR_ID?=PLEASE_SET_DYN_INSTR_ID
STATIC_INSTR_ID?=PLEASE_SET_STATIC_INSTR_ID
OPCODE_ID?=PLEASE_SET_OPCODE_ID
REG_NAME?=PLEASE_SET_REG_NAME

CCC=$(LLVM_PATH)/clang++
CC=$(LLVM_PATH)/clang
OPT=$(LLVM_PATH)/opt
LLINK=$(LLVM_PATH)/llvm-link
LLVM_CONFIG=$(LLVM_PATH)/llvm-config

SRCS = main.c mmio.c solve.c util.c
EXEC = samg
#CPPFLAGS = -L/usr/lib -lblas -lm -lgsl -lpthread
CPPFLAGS = -L/usr/lib

LLVM_OBJS = $(patsubst %.c, %.llvm, $(SRCS)) 


amg-instrumented: full-opt.o
	$(CCC) -std=c++11  -I/usr/apps/gnu/4.8.5 -static -O0 -fno-inline -o amg-instrumented full-opt.o 

full-opt.o: full-opt.ll
	$(CC) -c full-opt.ll -o full-opt.o

full-opt.ll: full.ll
	$(OPT) -disable-inlining -S -load $(PWD)/../../src/*.so -Corruption full.ll -o full-opt.ll

full.ll: instrument.ll floating_point_Binary_32_64_convertor.ll main.llvm mmio.llvm solve.llvm util.llvm
	$(LLINK) -o full.ll instrument.ll floating_point_Binary_32_64_convertor.ll main.llvm mmio.llvm solve.llvm util.llvm

mmio.llvm: mmio.c
	$(CC) -g -O1 -S -fno-slp-vectorize -fno-vectorize -fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(CPPFLAGS) -o mmio.llvm mmio.c

solve.llvm: solve.c
	    $(CC) -g -O1 -S -fno-slp-vectorize -fno-vectorize -fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(CPPFLAGS) -o solve.llvm solve.c

util.llvm: util.c
	    $(CC) -g -O1 -S -fno-slp-vectorize -fno-vectorize -fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(CPPFLAGS) -o util.llvm util.c

main.llvm: main.c
	    $(CC) -g -O1 -S -fno-slp-vectorize -fno-vectorize -fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(CPPFLAGS) -o main.llvm main.c


instrument.ll: instrument.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
        -D__STDC_CONSTANT_MACROS instrument.cpp -o instrument.ll

floating_point_Binary_32_64_convertor.ll: floating_point_Binary_32_64_convertor.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
        -D__STDC_CONSTANT_MACROS floating_point_Binary_32_64_convertor.cpp -o floating_point_Binary_32_64_convertor.ll

clean:   
	rm -f *.ll* *.o *.core full* *-instrumented
