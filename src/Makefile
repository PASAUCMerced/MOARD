#export LLVM_PATH=/usr/global/tools/clang/chaos_5_x86_64_ib/clang-3.8.0/bin
export LLVM_PATH=/opt/pasa_lib/llvm-3.8.0/bin
include Makefile.config

export WORK_FUNC=conj_grad

PROG		= libCorrupt1bit.so
SRC_FILES	= corrupt1bit.cpp utility.cpp

O_FILES		= $(SRC_FILES:%.cpp=%.o)

all: $(PROG)

$(PROG): $(O_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(PROG) $(SHARED_LIB_OPT) $(O_FILES)


clean:
	$(RM) *.o $(PROG)
