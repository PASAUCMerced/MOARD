#export LLVM_PATH=/opt/pasa_lib/llvm-3.8.0/bin
#export LLVM_PATH=/usr/global/tools/clang/chaos_5_x86_64_ib/clang-3.8.0/bin
WORK_FUNC?=PLEASE_SET_WORK_FUNC
LLVM_PATH?=PLEASE_SET_LLVM_PATH
OPRAND_ID?=PLEASE_SET_OPRAND_ID
BIT_POSITION?=PLEASE_SET_BIT_POSITION
DYN_INSTR_ID?=PLEASE_SET_DYN_INSTR_ID
STATIC_INSTR_ID?=PLEASE_SET_STATIC_INSTR_ID
OPCODE_ID?=PLEASE_SET_OPCODE_ID
REG_NAME?=PLEASE_SET_REG_NAME

#export WORK_FUNC=ssor

CCC=$(LLVM_PATH)/clang++
CC=$(LLVM_PATH)/clang
OPT=$(LLVM_PATH)/opt
LLINK=$(LLVM_PATH)/llvm-link
LLVM_CONFIG=$(LLVM_PATH)/llvm-config
SRCS = blts.c c_timers.c erhs.c exact.c jacu.c lu.c print_results.c rhs.c setcoeff.c  wtime.c buts.c domain.c error.c jacld.c l2norm.c pintgr.c read_input.c setbv.c setiv.c verify.c #ssor.c

LLVM_OBJS = $(patsubst %.c, %.llvm, $(SRCS))

lu-instrumented: full-opt.o
	$(CCC) -std=c++11  -I/usr/apps/gnu/4.8.5 -static -O0 -fno-inline -o lu-instrumented full-opt.o

full-opt.o: full-opt.ll
	$(CC) -c full-opt.ll -o full-opt.o

full-opt.ll: full.ll
	$(OPT) -disable-inlining -S -load $(PWD)/../../src/*.so -Corruption full.ll -o full-opt.ll

full.ll:  $(LLVM_OBJS) instrument.ll floating_point_Binary_32_64_convertor.ll
	$(LLINK) $(LLVM_OBJS) instrument.ll floating_point_Binary_32_64_convertor.ll  -o full.ll

instrument.ll: instrument.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
	-D__STDC_CONSTANT_MACROS instrument.cpp -o instrument.ll

floating_point_Binary_32_64_convertor.ll: floating_point_Binary_32_64_convertor.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
	-D__STDC_CONSTANT_MACROS floating_point_Binary_32_64_convertor.cpp -o floating_point_Binary_32_64_convertor.ll

%.llvm: %.c
	$(CC) -fPIC -g -static -O1 -S -fno-slp-vectorize -fno-vectorize \
        -fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $< -o $*.llvm

clean:
	rm -f full* *.bc *.ll* *.core* *-instrumented *.gz
