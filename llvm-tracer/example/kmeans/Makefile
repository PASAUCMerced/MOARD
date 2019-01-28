export WORKLOAD=kmeans_clustering
TRACER_HOME=/home/azguolu/Projects/resiliencePatternHunting/LLVM_Tracer_Work_Station/llvm-tracer

SRCS = cluster.c getopt.c kmeans.c kmeans_clustering.c 
EXEC = kmeans
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
	clang -g -O1 -S -static \
        -emit-llvm \
        $(CPPFLAGS) \
        -o $*.llvm $<
	opt -S -load=$(TRACER) -fulltrace $*.llvm -o $@

clean: 
	rm -f *.ll* *.s *.core *-instrumented *.gz
