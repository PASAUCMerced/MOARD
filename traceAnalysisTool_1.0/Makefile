all: traceAnalysisTool

CC = g++
C_INC = 
#CFLAGS = -O3  
CFLAGS = -O0 -g   #for debugging, use this CFLAGS

CLINK = ${CC} 
CLINKFLAGS = -g 
MY_LIB = 


CCOMPILE= $(CC)  -c $(C_INC) $(CFLAGS)
OBJS = instr_state_unit.o infor_fault_injection.o global_state_unit.o instr_info.o opcode_pro_function.o \
	floating_point_Binary_32_64_convertor.o	fault_mask_counter.o argu_config_space.o traceAnalysisTool.o

instr_state_unit.o: instr_state_unit.cpp instr_state_unit.h
	${CCOMPILE} instr_state_unit.cpp

infor_fault_injection.o: infor_fault_injection.cpp infor_fault_injection.h
	${CCOMPILE} infor_fault_injection.cpp

global_state_unit.o: global_state_unit.cpp global_state_unit.h
	${CCOMPILE} global_state_unit.cpp

instr_info.o: instr_info.cpp instr_info.h
	${CCOMPILE} instr_info.cpp

opcode_pro_function.o: opcode_pro_function.cpp opcode_pro_function.h floating_point_Binary_32_64_convertor.h
	${CCOMPILE} opcode_pro_function.cpp

floating_point_Binary_32_64_convertor.o: floating_point_Binary_32_64_convertor.cpp floating_point_Binary_32_64_convertor.h
	${CCOMPILE} floating_point_Binary_32_64_convertor.cpp

fault_mask_counter.o: fault_mask_counter.cpp fault_mask_counter.h
	${CCOMPILE} fault_mask_counter.cpp 

traceAnalysisTool.o: traceAnalysisTool.cpp instr_info.h opcode_pro_function.h infor_fault_injection.h global_state_unit.h instr_state_unit.h 
	${CCOMPILE} traceAnalysisTool.cpp 

argu_config_space.o: argu_config_space.cpp argu_config_space.h
	${CCOMPILE} argu_config_space.cpp

traceAnalysisTool: ${OBJS}
	${CLINK} ${CLINKFLAGS} -o traceAnalysisTool ${OBJS} ${MY_LIB}	


 
clean:
	rm -f *.o traceAnalysisTool
	rm -f ../analysis_result/*	
