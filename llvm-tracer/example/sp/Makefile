export WORKLOAD=x_solve
TRACER_HOME=/home/azguolu/Projects/resiliencePatternHunting/LLVM_Tracer_Work_Station/llvm-tracer

SRCS = add.c c_timers.c exact_rhs.c initialize.c pinvr.c rhs.c sp.c tzetar.c wtime.c y_solve.c \
	adi.c error.c exact_solution.c ninvr.c print_results.c set_constants.c txinvr.c verify.c x_solve.c z_solve.c
EXEC = sp
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
