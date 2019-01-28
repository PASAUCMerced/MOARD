WORKLOAD=print_results
TRACER_HOME=/home/jingl/LLVM_Tracer_Work_Station/LLVM-Tracer

SRCS = cg.c wtime.c randdp.c print_results.c c_timers.c
EXEC = cg
CPPFLAGS = # Put include directories here
LOGGER = $(TRACER_HOME)/profile-func/trace_logger.llvm
TRACER = $(TRACER_HOME)/full-trace/full_trace.so

LLVM_OBJS = $(patsubst %.c, %-opt.llvm, $(SRCS))


$(EXEC)-instrumented: full.s
	$(CXX) -O0 -fno-inline -o $@ $< -lm -lz

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
