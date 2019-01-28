export LLVM_PATH=/opt/pasa_lib/llvm-3.8.0/bin
ifndef LLVM_PATH
   $(error LLVM_PATH is undefined)
endif
#ifndef OPRAND_ID
#   $(error OPRAND_ID is undefined)
#endif

CCC=$(LLVM_PATH)/clang++
CC=$(LLVM_PATH)/clang
OPT=$(LLVM_PATH)/opt
LLINK=$(LLVM_PATH)/llvm-link
LLVM_CONFIG=$(LLVM_PATH)/llvm-config

export WORK_FUNC=triad

SRC_FILES=triad.c
LL_FILES=$(SRC_FILES:%.c=%.ll)

full-opt: full-opt.o
	$(CCC) -std=c++11  -I/usr/apps/gnu/4.8.5 -static -O0 -fno-inline -o full-opt full-opt.o

full-opt.o: full-opt.ll
	$(CC) -c full-opt.ll -o full-opt.o

full-opt.ll: full.ll
	$(OPT) -disable-inlining -S -load $(PWD)/../../src/*.so -Corruption full.ll -o full-opt.ll

full.ll: $(LL_FILES) instrument.ll floating_point_Binary_32_64_convertor.ll
	$(LLINK) instrument.ll floating_point_Binary_32_64_convertor.ll $(LL_FILES) -o full.ll

instrument.ll: instrument.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
	-D__STDC_CONSTANT_MACROS instrument.cpp -o instrument.ll

floating_point_Binary_32_64_convertor.ll: floating_point_Binary_32_64_convertor.cpp
	$(CC)  -fPIC -emit-llvm -O3 -S -D__STDC_LIMIT_MACROS \
	-D__STDC_CONSTANT_MACROS floating_point_Binary_32_64_convertor.cpp -o floating_point_Binary_32_64_convertor.ll

$(LL_FILES): $(SRC_FILES)
	$(CC) -fPIC -g -static -O1 -S -fno-slp-vectorize -fno-vectorize \
	-fno-unroll-loops -fno-inline -fno-builtin -emit-llvm $(SRC_FILES) -o $(LL_FILES)

clean:
	rm -f full* *.bc *.ll
