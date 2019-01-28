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

#export WORK_FUNC=conj_grad

SRC_FILES_1= print_results.c
LL_FILES_1=$(SRC_FILES_1:%.c=%.ll)
SRC_FILES_2= randdp.c
LL_FILES_2=$(SRC_FILES_2:%.c=%.ll)
SRC_FILES_3= wtime.c
LL_FILES_3=$(SRC_FILES_3:%.c=%.ll)
SRC_FILES_4= c_timers.c
LL_FILES_4=$(SRC_FILES_4:%.c=%.ll)
SRC_FILES_5= mg.c
LL_FILES_5=$(SRC_FILES_5:%.c=%.ll)




mg-instrumented: full-opt.o
	$(CCC) -std=c++11  -I/usr/apps/gnu/4.8.5 -static -O0 -fno-inline -o mg-instrumented full-opt.o

full-opt.o: full-opt.ll
	$(CC) -c full-opt.ll -o full-opt.o

full-opt.ll: full.ll
	$(OPT) -disable-inlining -S -load $(PWD)/../../src/*.so -Corruption full.ll -o full-opt.ll

full.ll: $(LL_FILES_1) $(LL_FILES_2) $(LL_FILES_3) $(LL_FILES_4) $(LL_FILES_5) instrument.ll floating_point_Binary_32_64_convertor.ll
	$(LLINK) instrument.ll floating_point_Binary_32_64_convertor.ll $(LL_FILES_1) $(LL_FILES_2) $(LL_FILES_3) $(LL_FILES_4) $(LL_FILES_5) -o full.ll

instrument.ll: instrument.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
	-D__STDC_CONSTANT_MACROS instrument.cpp -o instrument.ll

floating_point_Binary_32_64_convertor.ll: floating_point_Binary_32_64_convertor.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
	-D__STDC_CONSTANT_MACROS floating_point_Binary_32_64_convertor.cpp -o floating_point_Binary_32_64_convertor.ll

$(LL_FILES_1): $(SRC_FILES_1)
	$(CC) -fPIC -g -static -O1 -S -fno-slp-vectorize -fno-vectorize \
	-fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(SRC_FILES_1) -o $(LL_FILES_1)

$(LL_FILES_2): $(SRC_FILES_2)
	$(CC) -fPIC -g -static -O1 -S -fno-slp-vectorize -fno-vectorize \
	-fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(SRC_FILES_2) -o $(LL_FILES_2)

$(LL_FILES_3): $(SRC_FILES_3)
	$(CC) -fPIC -g -static -O1 -S -fno-slp-vectorize -fno-vectorize \
	-fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(SRC_FILES_3) -o $(LL_FILES_3)

$(LL_FILES_4): $(SRC_FILES_4)
	$(CC) -fPIC -g -static -O1 -S -fno-slp-vectorize -fno-vectorize \
	-fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(SRC_FILES_4) -o $(LL_FILES_4)

$(LL_FILES_5): $(SRC_FILES_5)
	$(CC) -fPIC -g -static -O1 -S -fno-slp-vectorize -fno-vectorize \
	-fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(SRC_FILES_5) -o $(LL_FILES_5)

clean:
	rm -f full* *.bc *.ll* *.core* *-instrumented *.gz
