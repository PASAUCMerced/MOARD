export WORKLOAD=solve
#TRACER_HOME=/home/jingl/LLVM_Tracer_Work_Station/LLVM-Tracer
TRACER_HOME=/home/azguolu/Projects/resiliencePatternHunting/LLVM_Tracer_Work_Station/llvm-tracer

SRCS = solve.c util.c mmio.c main.c
EXEC = samg
CPPFLAGS = -L/usr/lib/ #-llapack -lblas -lm
LOGGER = $(TRACER_HOME)/profile-func/trace_logger.llvm
TRACER = $(TRACER_HOME)/full-trace/full_trace.so

LLVM_OBJS = $(patsubst %.c, %-opt.llvm, $(SRCS))


$(EXEC)-instrumented: full.s
	g++ -O0 -fno-inline -o $@ $< -lm -lz #-lblas llapack

full.s: full.llvm
	llc -O0 -disable-fp-elim -filetype=asm -o $@ $<

full.llvm: $(LLVM_OBJS)
	llvm-link -o $@ $^ $(LOGGER)

%-opt.llvm: %.c
	clang -g -O1 -S -fno-slp-vectorize -fno-vectorize -fno-unroll-loops \
        -fno-inline -fno-builtin \
        -emit-llvm \
        $(CPPFLAGS) \
        -o $*.llvm $<
	opt -S -load=$(TRACER) -fulltrace $*.llvm -o $@

clean: 
	rm -f *.ll* *.s *.core *-instrumented *.o *.gz 
