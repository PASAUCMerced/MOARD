#ifndef _OPCODE_PRO_FUNCTION_H_
#define _OPCODE_PRO_FUNCTION_H_
#include "instr_info.h"
#include "argu_config_space.h"
#include "temp_state_unit.h"
#include "fault_mask_counter.h"
#include "global_state_unit.h"
#include "instr_state_unit.h"

class opcodeProFunction
{
private:
	int opcode;
	instrInfo *an_instr_info;
	arguConfigSpace *an_arguConfig;
	fmCounter *fCounter;
public:
	opcodeProFunction(int opId, instrInfo* an_instr_info_agu,fmCounter *fmc,arguConfigSpace *an_arguConfig);
	virtual ~opcodeProFunction(void);
	void opcodeProcess(instrStateUnit *an_instrStateUnit,globalStateUnit *an_globalStateUnit, string sign, string signSubTaData, fmCounter *fmc);
	void OPCODE_BR(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit);
	void OPCODE_PHI(globalStateUnit *an_globalStateUnit, instrStateUnit *an_instrStateUnit,string signSubTaData);
	void OPCODE_GETELEMENTPTR(globalStateUnit *an_globalStateUnit);
	void OPCODE_LOAD(globalStateUnit *an_globalStateUnit, instrStateUnit *an_instrStateUnit, string signSubTaData);
	void OPCODE_ADD(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData);
	void OPCODE_FADD(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData);
	void OPCODE_AND_OR(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData, fmCounter *fmc);
	void OPCODE_OR(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData);
	void OPCODE_STORE(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string signSubTaData);
	void OPCODE_MUL(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string signSubTaData);
	void OPCODE_FMUL(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string signSubTaData);
	void OPCODE_SDIV(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string signSubTaData);
	void OPCODE_FDIV(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string signSubTaData);
	void OPCODE_SREM(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string signSubTaData);
	void OPCODE_SUB(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData);
	void OPCODE_FSUB(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData);
	void OPCODE_ICMP(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, fmCounter *fmc);
	void OPCODE_FCMP(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, fmCounter *fmc);
	void OPCODE_RET(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit);
	void OPCODE_SWITCH(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign);
	void OPCODE_TRUNC(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign, string signSubTaData);
	void OPCODE_ZSEXT(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign, string signSubTaData);
	void OPCODE_ALLOCA(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit);
	void OPCODE_SHR(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign,string signSubTaData);
	void OPCODE_SHL(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign,string signSubTaData);
	void add2TarDataOrNot(string regName, string addrName,globalStateUnit *an_globalStateUnit, bool *isNot, int *index);
	bool isOnInstrStaUnit(string name, vector<an_intrStUni *> subTarData, int *index);

	//int lengthOftype(string dataType);
};
string convertToString(double d);
//void deciToBinary(long long int N, int bitLen, string bitN);
//void binaryToDeci(string in_strs, int bitLen, long long int number);
#endif
