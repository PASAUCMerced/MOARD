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

#export WORK_FUNC=x_solve

CCC=$(LLVM_PATH)/clang++
CC=$(LLVM_PATH)/clang
OPT=$(LLVM_PATH)/opt
LLINK=$(LLVM_PATH)/llvm-link
LLVM_CONFIG=$(LLVM_PATH)/llvm-config
SRCS = add.c c_timers.c exact_rhs.c initialize.c pinvr.c rhs.c sp.c tzetar.c wtime.c y_solve.c  error.c exact_solution.c ninvr.c print_results.c set_constants.c txinvr.c verify.c  z_solve.c #x_solve.c adi.c

LLVM_OBJS = $(patsubst %.c, %.llvm, $(SRCS))

sp-instrumented: full-opt.o
	$(CCC) -std=c++11  -I/usr/apps/gnu/4.8.5 -static -O0 -fno-inline -o sp-instrumented full-opt.o

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
