export WORKLOAD=ssor
TRACER_HOME=/home/azguolu/Projects/resiliencePatternHunting/LLVM_Tracer_Work_Station/llvm-tracer

SRCS = blts.c c_timers.c erhs.c exact.c jacu.c lu.c print_results.c rhs.c setcoeff.c ssor.c wtime.c \
    buts.c domain.c error.c jacld.c l2norm.c pintgr.c read_input.c setbv.c setiv.c verify.c 
EXEC = lu
CPPFLAGS = # Put include directories here
LOGGER = $(TRACER_HOME)/profile-func/trace_logger.llvm
TRACER = $(TRACER_HOME)/full-trace/full_trace.so

LLVM_OBJS = $(patsubst %.c, %-opt.llvm, $(SRCS))


$(EXEC)-instrumented: full.s
	$(CXX) -O0 -fno-inline -o $@ $< -lm -lz
	./$(EXEC)-instrumented

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
	rm -f *.ll* *.s *.core *-instrumented *.gz
