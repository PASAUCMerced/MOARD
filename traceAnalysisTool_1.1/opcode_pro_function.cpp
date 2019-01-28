//#include "stdafx.h"
#include "opcode_pro_function.h"
#include "floating_point_Binary_32_64_convertor.h"
#include <string.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

//processing the trace blocks according to its opcode
opcodeProFunction::opcodeProFunction(int opId, instrInfo* an_instr_info_agu, fmCounter *fmc, arguConfigSpace *an_arguConfig_pasa)
{
	opcode = opId;
	//pass a single block of trace to initialize AN_INSTR_INFO
	an_instr_info = an_instr_info_agu;
	//configure the environment variables and functions with arguConfigSpace class
	an_arguConfig = an_arguConfig_pasa;
	/*create a fault-masking counter for the target data strucutre, 
	and initialize the arguments of the faultMaskCounter*/
	fCounter = fmc;
}

opcodeProFunction::~opcodeProFunction(void)
{
	if (this->an_instr_info!=NULL)
	{
		this->an_instr_info = NULL;
		delete this->an_instr_info;
	}
	if (this->fCounter!=NULL)
	{
		this->fCounter = NULL;
		delete this->fCounter;
	}
}

//One principle is used here that instructions without data flow is useless in the 
//trace analysis. And there mustn't be fault masking if there is no data flow. data
//flow is only related to the global state units(targetData1Relat and targetAddr1Relat)
void opcodeProFunction::opcodeProcess(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData, fmCounter *fmc)
{
	int a = opcode;
	switch (a)
	{
	//case 0://llvm_ir_move
	//	//TODO
	//	if (sign == "ini")
	//	{
	//		fCounter->opcode_count[0]++;  //Dong's comment: TODO
	//	}
	//	break;
	case 1://llvm_ir_ret
		/* there is no data flow, so no fault masking here.
		OPCODE_RET(an_instrStateUnit, targetData1Relat, targetAddr1Relat, statVector);
		*/
		if (sign == "ini")
		{
			fCounter->opcode_count[1][0]++; 
			fCounter->opcode_count[1][1] = 1;//means processed
		}
		break;
	case 2://llvm_ir_br
		/* the basic-block-id more likly will not be used in the data transference and fault masking anaylsis,
		so we don't want to add it to the temp_state_vector currently before we find it is useful. There is
		no data flow, and no fault masking here.
		OPCODE_BR(an_instrStateUnit,  targetData1Relat,targetAddr1Relat);		
		*/
		if (sign == "ini")
		{
			fCounter->opcode_count[2][0]++;
			fCounter->opcode_count[2][1] = 1;//means processed
		}
		break;
	case 3://llvm_ir_switch
		if (sign == "ini")
		{
			fCounter->opcode_count[3][0]++;
			fCounter->opcode_count[3][1] = 1;//means processed
		}
		OPCODE_SWITCH(an_instrStateUnit,  an_globalStateUnit, sign);
		break;
	case 8://llvm_ir_add
		if (sign == "ini")
		{
			fCounter->opcode_count[8][0]++;
			fCounter->opcode_count[8][1] = 1;//means processed
		}
		//both of data flow and possibility of fault masking happen here
		OPCODE_ADD(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 9://llvm_ir_Fadd
		if (sign == "ini")
		{
			fCounter->opcode_count[9][0]++;
			fCounter->opcode_count[9][1] = 1;//means processed
		}
		//possibility of fault masking happen here
		OPCODE_FADD(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 10://llvm_ir_sub
		if (sign == "ini")
		{
			fCounter->opcode_count[10][0]++;
			fCounter->opcode_count[10][1] = 1;//means processed
		}
		//both of data flow and possibility of fault masking happen here
		OPCODE_SUB(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 11://llvm_ir_Fadd
		if (sign == "ini")
		{
			fCounter->opcode_count[11][0]++;
			fCounter->opcode_count[11][1] = 1;//means processed
		}
		//possibility of fault masking happen here
		OPCODE_FSUB(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 12://llvm_ir_mul
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[12][0]++;
			fCounter->opcode_count[12][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_MUL(an_instrStateUnit,  an_globalStateUnit, signSubTaData);
		break;
	case 13://llvm_ir_fmul
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[13][0]++;
			fCounter->opcode_count[13][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_FMUL(an_instrStateUnit,  an_globalStateUnit, signSubTaData);
		break;
	case 15://llvm_ir_sdiv
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[15][0]++;
			fCounter->opcode_count[15][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_SDIV(an_instrStateUnit,  an_globalStateUnit, signSubTaData);
		break;
	case 16://llvm_ir_fdiv
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[16][0]++;
			fCounter->opcode_count[16][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_FDIV(an_instrStateUnit,  an_globalStateUnit, signSubTaData);
		break;
	case 18://llvm_ir_srem
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[18][0]++;
			fCounter->opcode_count[18][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_SREM(an_instrStateUnit,  an_globalStateUnit, signSubTaData);
		break;
	case 20://llvm_ir_shl
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[20][0]++;
			fCounter->opcode_count[20][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_SHL(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 21://llvm_ir_lshr
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[21][0]++;
			fCounter->opcode_count[21][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_SHR(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 22://llvm_ir_ashr
		//TO add counter
		if (sign=="ini")
		{
			fCounter->opcode_count[22][0]++;
			fCounter->opcode_count[22][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking happening here
		OPCODE_SHR(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 23://llvm_ir_and
		if (sign == "ini")
		{
			fCounter->opcode_count[23][0]++;
			fCounter->opcode_count[23][1] = 1;//means processed
		}
		//both of data flow and possibility of fault masking happen here
		OPCODE_AND_OR(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData, fmc);
		break;
	case 24://llvm_ir_or
		if (sign == "ini")
		{
			fCounter->opcode_count[24][0]++;
			fCounter->opcode_count[24][1] = 1;//means processed
		}
		//both of data flow and possibility of fault masking happen here
		OPCODE_AND_OR(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData, fmc);
		break;
	case 26://llvm_ir_alloca
		/* there is no data flow, so no fault masking here.
		OPCODE_ALLOCA(an_instrStateUnit,  targetData1Relat,targetAddr1Relat);
		*/
		//To add counter
		if (sign == "ini")
		{
			fCounter->opcode_count[26][0]++;
			fCounter->opcode_count[26][1] = 1;//means processed
		}
		break;
	case 27://llvm_ir_load
		//there is no fault masking happening here, but there is data transference.
		//To add counter
		if (sign == "ini")
		{
			fCounter->opcode_count[27][0]++;
			fCounter->opcode_count[27][1] = 1;//means processed
		}
		OPCODE_LOAD(an_globalStateUnit, an_instrStateUnit, signSubTaData);
		break;
	case 28://llvm_ir_store
		//To add counter
		if (sign == "ini")
		{
			fCounter->opcode_count[28][0]++;
			fCounter->opcode_count[28][1] = 1;//means processed
		}
		//there are both data flow and possibility of fault masking here.
		OPCODE_STORE(an_instrStateUnit, an_globalStateUnit, signSubTaData);//load and store are confusing here
		break;
	case 29://llvm_ir_getelementptr
		//there is data flow here, but no fault masking.
		//To add counter
		if (sign == "ini")
		{
			fCounter->opcode_count[29][0]++;
			fCounter->opcode_count[29][1] = 1;//means processed
		}
		OPCODE_GETELEMENTPTR(an_globalStateUnit);
		break;
	case 33://llvm_ir_trunc
		if (sign == "ini")
		{
			fCounter->opcode_count[33][0]++;
			fCounter->opcode_count[33][1] = 1;//means processed
		}
		OPCODE_TRUNC(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 34://llvm_ir_zext
		if (sign == "ini")
		{
			fCounter->opcode_count[34][0]++;
			fCounter->opcode_count[34][1] = 1;//means processed
		}
		OPCODE_ZSEXT(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 35://llvm_ir_sext
		if (sign == "ini")
		{
			fCounter->opcode_count[35][0]++;
			fCounter->opcode_count[35][1] = 1;//means processed
		}
		OPCODE_ZSEXT(an_instrStateUnit,  an_globalStateUnit, sign, signSubTaData);
		break;
	case 46://llvm_ir_icmp
		//there is no data flow, but possiblity of fault masking here. And if the argument 
		//is related to target data, the ratio of fault masking should be 50%.
		//To add counter
		if (sign == "ini")
		{
			fCounter->opcode_count[46][0]++;
			fCounter->opcode_count[46][1] = 1;//means processed
		}
		OPCODE_ICMP(an_instrStateUnit, an_globalStateUnit, fmc);
		break;
	case 47://llvm_ir_FCmp
		if (sign == "ini")
		{
			fCounter->opcode_count[47][0]++;
			fCounter->opcode_count[47][1] = 1;//means processed
		}
		OPCODE_FCMP(an_instrStateUnit, an_globalStateUnit, fmc);
		break;
	case 48://llvm_ir_phi
		//there is data flow, but no fault masking here.
		//To add counter
		if (sign == "ini")
		{
			fCounter->opcode_count[48][0]++;
			fCounter->opcode_count[48][1] = 1;//means processed
		}
		OPCODE_PHI(an_globalStateUnit, an_instrStateUnit,signSubTaData);
		break;
	default:
		if (sign == "ini")
		{
			fCounter->opcode_count[a][0]++;
			fCounter->opcode_count[a][1] = 0; //means unprocessed
			//printf("EXCEPTION: 'UN-PROCESSED OPCODES' ARE FOUND!");
		}
		break;
	} 

}

//For 'BR' trace blocks
//There is no fault-masking happening at this operator
/*
1) according to the number of following lines to judge the module of 'Br'; if there is 
only one following line, it is uncondition ¡®Br¡¯; or there are three following lines, 
it is condition ¡®Br¡¯; else print ¡®EXCEPTION FOUND (IR_Br has more than 2 lines)!¡¯; 

2) in uncondition ¡®Br¡¯ we just record the label (i.e., a register value) of the next 
basic block where the unconditional branch will go.
*/
/*
void opcodeProFunction::OPCODE_BR(instrStateUnit *an_instrStateUnit, vector<string> targetData1Relat,vector<string> targetAddr1Relat){
//creat a state unit to store intermidiate variables
tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();

//There are several conditions for BR operator, including condition and uncondition
//1) condition
if((an_instr_info->line3_arguId == "3")&&(an_instr_info->line2_arguId == "2"))
{
string nextBasicBlockId;
if (an_instr_info->line1_dynValue == 1)
{
string nextBasicBlockId= an_instr_info->line3_regName;
}else if (an_instr_info->line1_dynValue == 0)
{
string nextBasicBlockId= an_instr_info->line2_regName;

}else{
printf("EXCEPTION: A NEW KIND OF CONDITIONAL 'Br' MODULE IS FOUND!");
string nextBasicBlockId = "EXCEPTION";
}
an_tempStateUnitTier1->brBasBloId = nextBasicBlockId;
//2) uncondition
}else if(an_instr_info->line3_arguId == "1"){
string nextBasicBlockId = an_instr_info->line1_regName;
an_tempStateUnitTier1->brBasBloId = nextBasicBlockId;
}else {printf("EXCEPTION: A NEW KIND OF 'Br' MODULE BEYOND CONDITION AND UNCONDITION IS FOUND!");}

//push back the state unit into the state vector 'statVector'
statVector.push_back(an_tempStateUnitTier1);
}
*/

//For 'PHI' trace blocks
//there is no fault-masking happening at this operator, just data transmission.
/*
1) (optional) judging whether the basic-block-id  follows the control-flow option 
in 'Br' operation; if so, 
2) we check the register-names of the two predecessor blocks, and record the register 
names and values in the two predecessor blocks (input arguments 1 and 2) which should 
not be empty (hopefully). We also need to examine the existing state-unit data structure 
to check which input argument this PHI instruction is taking.
3) record the register-name and dynamic value of the output block (output argument) into 
the ¡®state-unit¡¯ data structure; 
*/
void opcodeProFunction::OPCODE_PHI(globalStateUnit *an_globalStateUnit, instrStateUnit *an_instrStateUnit, string signSubTaData){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	struct sglStUni *an_sglStUni = new sglStUni();
	//we should contrast the values of predecessor basic-blocks and current 
	//basic-block, to see which branch is taken.And catch the value transmission
	//of varialbes, and whether one of them is related to the target data object.
	double v_line1 = an_instr_info->line1_dynValue;
	double v_line2 = an_instr_info->line2_dynValue;
	double v_liner = an_instr_info->liner_dynValue;
	int bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
	bool r1 = (v_line1 == v_liner);
	bool r2 = (v_line2 == v_liner);
	bool r3 = (an_instr_info->line1_regORnot);
	bool r4 = (an_instr_info->line2_regORnot);
	if (an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty())
	{
		if (r1&&r3){/*
				//the function of 'phi' instruction is to transfer data, so there is not necessary to analyse an instruction
				//which will not result in fault masking in the future since we have take a note of the data transmission. 
				an_tempStateUnitTier1->phiLast1Val = an_instr_info->line1_dynValue;
				an_tempStateUnitTier1->phiLast1Reg = an_instr_info->line1_regName;
				an_tempStateUnitTier1->phiNextVal = an_instr_info->liner_dynValue;
				an_tempStateUnitTier1->phiNextReg = an_instr_info->liner_regName;*/
			//push back the new register name related to the target data object, and to be added into the global state unit
			bool yesNo1 = false;
			int index1 = 0;
			add2TarDataOrNot(an_instr_info->line1_regName, "",an_globalStateUnit, &yesNo1, &index1);
			bool yesNo2 = false;
			int index2 = 0;
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit, &yesNo2, &index2);
			if (yesNo1&&!yesNo2){
				an_sglStUni->regName = an_instr_info->liner_regName;
				an_sglStUni->corrAddr = an_globalStateUnit->mulStUni[index1]->corrAddr;
				an_globalStateUnit->mulStUni.push_back(an_sglStUni);
			}
		}else if(r2&&r4){
			bool yesNo1 = false;
			int index1 = 0;
			add2TarDataOrNot(an_instr_info->line2_regName, "",an_globalStateUnit, &yesNo1, &index1);
			bool yesNo2 = false;
			int index2 = 0;
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit, &yesNo2, &index2);
			if (yesNo1&&!yesNo2){
				an_sglStUni->regName = an_instr_info->liner_regName;
				an_sglStUni->corrAddr = an_globalStateUnit->mulStUni[index1]->corrAddr;
				an_globalStateUnit->mulStUni.push_back(an_sglStUni);

			}
		}else 
		{
			fCounter->phi_exception_counter++;
			printf("PHI EXCEPTION: found r1=%d and r2=%d in non-error propagation analysis\n", r1, r2);
		}
	}else
	{
		if(signSubTaData == "1")
		{
			int index1 = 0,index2 = 0;
			if (r1&&r3)
			{
				bool r3 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
				bool r4 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index2);
				if(r3&&!r4)
				{
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->liner_regName;
					for (int i = 0; i < bitLen;)
					{
						eleStates->tempSts[i] = an_instrStateUnit->subTarData1[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else if (!r3&&r4)
				{
					an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index2);
				}else if (r3&&r4)
				{
					for (int i = 0; i < bitLen;)
					{
						an_instrStateUnit->subTarData1[index2]->tempSts[i] = an_instrStateUnit->subTarData1[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
				}
				/*else
				   printf("PHI EXCEPTION (error propagation analysis): signSubTaData=1 and r1=1 and r3=%d and r4=%d\n", r3, r4);
			       fCounter->phi_exception_counter++;*/
			}
			else if (r2&&r4)
			{
				bool r3 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index1);
				bool r4 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index2);
				if(r3&&!r4)
				{
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->liner_regName;
					for (int i = 0; i < bitLen;)
					{
						eleStates->tempSts[i] = an_instrStateUnit->subTarData1[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else if (!r3&&r4)
				{
					an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index2);
				}else if (r3&&r4)
				{
					for (int i = 0; i < bitLen;)
					{
						an_instrStateUnit->subTarData1[index2]->tempSts[i] = an_instrStateUnit->subTarData1[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
				}
				/*else
			       fCounter->phi_exception_counter++;
				   printf("PHI EXCEPTION (error propagation analysis): signSubTaData=1 and r2=1 and r3=%d and r4=%d\n", r3, r4);*/
			}
		}
		else if (signSubTaData == "2")
		{
			int index1 = 0,index2 = 0;
			if (r1&&r3)
			{
				bool r3 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
				bool r4 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index2);
				if(r3&&!r4)
				{
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->liner_regName;
					for (int i = 0; i < bitLen;)
					{
						eleStates->tempSts[i] = an_instrStateUnit->subTarData2[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else if (!r3&&r4)
				{
					an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index2);
				}else if (r3&&r4)
				{
					for (int i = 0; i < bitLen;)
					{
						an_instrStateUnit->subTarData2[index2]->tempSts[i] = an_instrStateUnit->subTarData2[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
				}
				/*else
			       fCounter->phi_exception_counter++;
				   printf("PHI EXCEPTION (error propagation analysis): signSubTaData=2 and r1=1 and r3=%d and r4=%d\n", r3, r4);*/
			}
			else if (r2&&r4)
			{
				bool r3 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index1);
				bool r4 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index2);
				if(r3&&!r4)
				{
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->liner_regName;
					for (int i = 0; i < bitLen;)
					{
						eleStates->tempSts[i] = an_instrStateUnit->subTarData2[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else if (!r3&&r4)
				{
					an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index2);
				}else if (r3&&r4)
				{
					for (int i = 0; i < bitLen;)
					{
						an_instrStateUnit->subTarData2[index2]->tempSts[i] = an_instrStateUnit->subTarData2[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
				}
				/*else
        		   fCounter->phi_exception_counter++;
				   printf("PHI EXCEPTION (error propagation analysis): signSubTaData=2 and r2=1 and r3=%d and r4=%d\n", r3, r4);*/
			}
		}
		else if (signSubTaData == "3")
		{
			int index1 = 0,index2 = 0;
			if (r1&&r3)
			{
				bool r3 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
				bool r4 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index2);
				if(r3&&!r4)
				{
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->liner_regName;
					for (int i = 0; i < bitLen;)
					{
						eleStates->tempSts[i] = an_instrStateUnit->subTarData3[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else if (!r3&&r4)
				{
					an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index2);
				}else if (r3&&r4)
				{
					for (int i = 0; i < bitLen;)
					{
						an_instrStateUnit->subTarData3[index2]->tempSts[i] = an_instrStateUnit->subTarData3[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
				}
				/*else
   			       fCounter->phi_exception_counter++;
				   printf("PHI EXCEPTION (error propagation analysis): signSubTaData=3 and r1=1 and r3=%d and r4=%d\n", r3, r4);*/
			}
			else if (r2&&r4)
			{
				bool r3 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3,&index1);
				bool r4 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3,&index2);
				if(r3&&!r4)
				{
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->liner_regName;
					for (int i = 0; i < bitLen;)
					{
						eleStates->tempSts[i] = an_instrStateUnit->subTarData3[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else if (!r3&&r4)
				{
					an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index2);
				}else if (r3&&r4)
				{
					for (int i = 0; i < bitLen;)
					{
						an_instrStateUnit->subTarData3[index2]->tempSts[i] = an_instrStateUnit->subTarData3[index1]->tempSts[i];
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
				}
				/*else
			       fCounter->phi_exception_counter++;
				   printf("PHI EXCEPTION (error propagation analysis): signSubTaData=3 and r2=1 and r3=%d and r4=%d\n", r3, r4);*/
			}
		}
	}	
}

//For 'GETELEMENTPTR' trace blocks
//there is no fault-masking happening at this operator, also there is no data movement.
//just to get the element address of a congregation data object.
/*
1) the base address of the aggregate data structure is stored in following line1,
while the address of this element is stored in the following result line. 
2) from the other following lines, we can know the index of the element in the 
aggregate data structure, so 3) at least we should reserve the register-name and
dynamic-value of line1, and the register-name and dynamic-value in the result line. 
One is for base-address and variable-name of the aggregate data, another one is for the current element.
*/
void opcodeProFunction::OPCODE_GETELEMENTPTR(globalStateUnit *an_globalStateUnit){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	struct sglStUni *an_sglStUni = new sglStUni();
	//At least the base address of the congregation data shoule be recorded, and 
	//the current address of element should be recorded as well.
	/*an_tempStateUnitTier1->getelptrLastReg = an_instr_info->line1_regName;
	an_tempStateUnitTier1->getelptrLastAddr = convertToString(an_instr_info->line1_dynValue);
	an_tempStateUnitTier1->getelptrNextReg = an_instr_info->liner_regName;
	an_tempStateUnitTier1->getelptrNextAddr = convertToString(an_instr_info->liner_dynValue);*/

	//push back the new memory addresses related to the target data address, and to be added into the global state unit
	bool yesNo1 = false;
	int index1 = 0;
	add2TarDataOrNot("", convertToString(an_instr_info->line1_dynValue),an_globalStateUnit,&yesNo1,&index1);
	bool yesNo2 = false;
	int index2 = 0;
	add2TarDataOrNot("", convertToString(an_instr_info->liner_dynValue),an_globalStateUnit,&yesNo2,&index2);
	if (yesNo1&&!yesNo2)
	{
		an_sglStUni->corrAddr = convertToString(an_instr_info->liner_dynValue);
		an_globalStateUnit->mulStUni.push_back(an_sglStUni);
	}
	//push back the state unit into the state vector 'statVector'
	//statVector.push_back(an_tempStateUnitTier1);
}	

//For 'LOAD' trace blocks
//read data out of a memory cell into a register
//there is no fault-masking for this operator, as well as data movement
void opcodeProFunction::OPCODE_LOAD(globalStateUnit *an_globalStateUnit, instrStateUnit *an_instrStateUnit, string signSubTaData){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	struct sglStUni *an_sglStUni = new sglStUni();
	//reserve the values into temp_state
	//an_tempStateUnitTier1->loadAddr = convertToString( an_instr_info->line1_dynValue);//the memory address
	//an_tempStateUnitTier1->loadAddrReg = an_instr_info->line1_regName;//the register used to store the memory address
	//an_tempStateUnitTier1->loadVal = an_instr_info->liner_dynValue;//the value read from the memory
	//an_tempStateUnitTier1->loadValReg = an_instr_info->liner_regName;//the register used to store the value

	//To judge whether the memory address is related to the target data address
	//there are four situations here, 11, 10, 01, 00, according to whether related to target data or not.
	//and to be added into the global state unit
	int sz = atoi(an_instr_info->liner_sizeOfArgu.c_str());
	bool yesNo1 = false;
	int index1 = 0;
	bool yesNo2 = false;
	int index2 = 0;
	
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty())
	{
		//if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot("", convertToString(an_instr_info->line1_dynValue),an_globalStateUnit,&yesNo1,&index1);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&yesNo2,&index2);
		}
		if(yesNo1&&!yesNo2&&an_instr_info->liner_regORnot)//'10'
		{
			if(an_instr_info->liner_regORnot){
			an_sglStUni->regName = an_instr_info->liner_regName;
			an_sglStUni->corrAddr = convertToString(an_instr_info->line1_dynValue);
			an_globalStateUnit->mulStUni.push_back(an_sglStUni);
			}
		}else if(yesNo2&&an_instr_info->liner_regORnot)
		{
			an_globalStateUnit->mulStUni[index2]->corrAddr = convertToString(an_instr_info->line1_dynValue);
		}
	}else
	{
		int index3 = 0, index4 = 0;
		bool is1 = false, is2 = false;
		if(signSubTaData == "1")
		{   
			if (an_instr_info->liner_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData1, &index3);
			}
			if (an_instr_info->line1_regORnot)
			{
				is2 = isOnInstrStaUnit(convertToString(an_instr_info->line1_dynValue),an_instrStateUnit->subTarData1, &index4);
			}
			
			if (is1&&is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instrStateUnit->subTarData1[index4]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = convertToString(an_instr_info->line1_dynValue);
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData1[index3]->tempSts[i];//Anzheng's comment: I am not sure if there is fm.
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
			}else if (!is1&&is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				if(an_instr_info->liner_regORnot){
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData1[index4]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				}
			}
		}
		if(signSubTaData == "2")
		{
			if (an_instr_info->liner_regORnot)
			{
		        is1 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData2, &index3);/* code */
			}
			if (an_instr_info->line1_regORnot)
			{
				is2 = isOnInstrStaUnit(convertToString(an_instr_info->line1_dynValue),an_instrStateUnit->subTarData2, &index4);
			}
			
			if (is1&&is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instrStateUnit->subTarData2[index4]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = convertToString(an_instr_info->line1_dynValue);
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates);
			}else if (!is1&&is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				if(an_instr_info->liner_regORnot){
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData2[index4]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates);
				}
			}
		}
		if(signSubTaData == "3")
		{
			if (an_instr_info->liner_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData3, &index3);
			}
			if (an_instr_info->line1_regORnot)
			{
				is2 = isOnInstrStaUnit(convertToString(an_instr_info->line1_dynValue),an_instrStateUnit->subTarData3, &index4);
			}
			
			if (is1&&is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instrStateUnit->subTarData3[index4]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = convertToString(an_instr_info->line1_dynValue);
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates);
			}else if (!is1&&is2&&an_instr_info->liner_regORnot&&an_instr_info->line1_regORnot)
			{
				if(an_instr_info->liner_regORnot){
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData3[index4]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates);
				}
			}
		}
	}
	//push back the state unit into the state vector 'statVector'
	//statVector.push_back(an_tempStateUnitTier1);
}

//For 'ADD' trace blocks
//which is used to add two variables and then store the result in a new register.
/*
Here we store the two variables and their register-names (line1 and line 2), and 
then the result and its register-name (liner). Update the state-unit data structure.
*/
void opcodeProFunction::OPCODE_ADD(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign, string signSubTaData){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	//an_tempStateUnitTier1->addVal1 = an_instr_info->line1_dynValue;//the first varialbe for addtion
	//an_tempStateUnitTier1->addVal1Reg = an_instr_info->line1_regName;//the register of the first varialbe
	//an_tempStateUnitTier1->addVal2 = an_instr_info->line2_dynValue;//the secode varibale for addtion
	//an_tempStateUnitTier1->addVal2Reg = an_instr_info->line2_regName;//the register of the secode varibale
	//an_tempStateUnitTier1->addValr = an_instr_info->liner_dynValue;//the final result for addtion
	//an_tempStateUnitTier1->addValrReg = an_instr_info->liner_regName;//the register of the final result

	//To judge whether the register of variables are related to the target data object, and to be added into the global state unit
	//There is no need to do this step here, because the control flow here is not just related to the target data but also others.

	//To judge whether the registers and addresses and variables needed to be added into the instruction level state unit
	/*
	bool i = add2TarDataOrNot(an_instr_info->liner_regName, "",targetData1Relat,targetAddr1Relat);
	if(add2TarDataOrNot(an_instr_info->line1_regName, "",targetData1Relat,targetAddr1Relat)&&!i){
	targetData1Relat.push_back(an_instr_info->liner_regName);
	}else if(add2TarDataOrNot(an_instr_info->line2_regName, "",targetData1Relat,targetAddr1Relat)&&!i){
	targetData1Relat.push_back(an_instr_info->liner_regName);
	}
	*/

	//First of all and all, we should judge how many operand of the entire operands are belong to the target data, according to which, 
	//we start our following analysis steps.
	//So, there will be 8 situations: 0 0 0; 1 0 0; 0 1 0; 0 0 1; 1 1 0; 0 1 1; 1 0 1; 1 1 1;

	bool yesNo1 = false, yesNo2 = false, yesNo3 = false;
	int index1 = 0, index2 = 0, index3 = 0;
	long long int deciN1 = an_instr_info->line1_dynValue;
	long long int deciN2 = an_instr_info->line2_dynValue;
	long long int deciNXor;	
	bool is_fm = false;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&yesNo2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit, &yesNo3, &index3);
		}

		//if yesNo1=0, yesNo2=0, and yesNo3=0, do nothing

		//if 1 0 0, 
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
		{
	        long long int w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN1^w;
				long long int negTurn;
				negTurn = deciNXor-deciN1;  
				if (negTurn<0)
					negTurn = -negTurn;
				is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;

				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor+deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
			
		}

		//for 0 1 0;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			long long int w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			
			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN2^w;
				long long int negTurn;
				negTurn = deciNXor-deciN2;
				if (negTurn<0)
					negTurn = -negTurn;
				is_fm = (an_arguConfig->faultMaskRatio>=(double)negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor+deciN1;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 0 0 1;
		if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			/*fmcVector[0]->counter = 1;
			fmcVector[0]->dynId = an_instr_info->line0_dynInstId;
			fmcVector[0]->numOfBits = atoi(an_instr_info->liner_sizeOfArgu.c_str());
			fmcVector[0]->numOfMaskBits = fmcVector[0]->numOfBits;
			fmcVector[0]->opId = an_instr_info->line0_opcodeId;*/
		}
		//for 1 1 0, although there are two operand related to the target data, we only consider one because they are the same
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=2*negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor;
						eleStates_ret->tempSts[i] = deciNXor*2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}else
			{
				long long int w = 1;
				//while faults on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 1 0 1, 
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates_val->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				long long int w = 1;
				//while the faults on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;

				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 0 1 1;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates_val->tempSts[i] = deciNXor+deciN1;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				long long int w = 1;
				//while the fault on yesNo2
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 1 1 1;
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
				&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=2*negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor*2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				long long int w = 1;
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=2*negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates_val1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
			    w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val1->tempSts[i] = deciNXor+deciN1;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				//bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				w = 1;
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				long long int w = 1;
				//while the fault on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				//bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else{
		if(signSubTaData == "1")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
	     		an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								eleStates->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								eleStates->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1+deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1+deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=2*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=2*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1+deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1+deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1+deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
	     		an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								eleStates->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								eleStates->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1+deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1+deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=2*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=2*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1+deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1+deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1+deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if(signSubTaData == "3")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
	     		an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								eleStates->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								eleStates->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1+deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1+deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=2*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=2*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1+deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1+deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1+deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}


//For 'Fadd' instructions
void opcodeProFunction::OPCODE_FADD(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign, string signSubTaData){
	//First of all and all, we should judge how many operand of the entire operands are belong to the target data, according to which, 
	//we start our following analysis steps.
	//So, there will be 8 situations: 0 0 0; 1 0 0; 0 1 0; 0 0 1; 1 1 0; 0 1 1; 1 0 1; 1 1 1;

	bool yesNo1 = false, yesNo2 = false, yesNo3 = false;
	bool is_fm = false;
	int index1 = 0, index2 = 0, index3 = 0;	
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	double deciN1 = an_instr_info->line1_dynValue;
	double deciN2 = an_instr_info->line2_dynValue;
	double deciNXor;
	uint64_t w = 1;

	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&yesNo2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit, &yesNo3, &index3);
		}
		//if yesNo1=0, yesNo2=0, and yesNo3=0, do nothing

		//if 1 0 0, 	
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for(int i=0;i<bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN1)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN1)^w);
				}
				
				double negTurn;
				negTurn = abs(deciNXor-deciN1);
				is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;

				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor+deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}

		//for 0 1 0;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			
			for(int i=0;i<bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN2)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN2)^w);
				}
				
				double negTurn;
				negTurn = abs(deciNXor-deciN2);
				is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor+deciN1;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}

		//for 0 0 1;
		if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 1 1 0, although there are two operand related to the target data, we only consider one because they are the same
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}

					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=2*negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor;
						eleStates_ret->tempSts[i] = deciNXor*2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}else
			{
				w = 1;
				//while faults on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}

					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 1 0 1, 
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					fCounter->three_sorts_fm_statement_level[0]++;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 0 1 1;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
				    double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val->tempSts[i] = deciNXor+deciN1;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 1 1 1;
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
				&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=2*negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor*2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=2*negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val1->tempSts[i] = deciNXor+deciN1;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
				    double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor+deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor+deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}	
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1+deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1+deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=2*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=2*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1+deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1+deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1+deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}	
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1+deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1+deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=2*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=2*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1+deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1+deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1+deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if(signSubTaData == "3")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}	
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor+deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1+deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1+deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=2*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=2*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2+an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1+deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1+deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1+deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//For 'STORE' trace blocks
//which is used to store a value into a memory address.
//there would be fault masking here
/*
Here we store the target value and its register-name (line1), and then the address 
and its register-name (line2). Update the state-unit data structure.
*/
void opcodeProFunction::OPCODE_STORE(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string signSubTaData){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	struct sglStUni *an_sglStUni = new sglStUni();
	//reserve the values into temp_state
	//an_tempStateUnitTier1->storeVal = an_instr_info->line1_dynValue;//the value
	//an_tempStateUnitTier1->storeValReg = an_instr_info->line1_regName;//the register of the value
	//an_tempStateUnitTier1->storeAddr = convertToString(an_instr_info->line2_dynValue);//the address
	//an_tempStateUnitTier1->storeAddrReg = an_instr_info->line2_regName;//the register of the address
	int sz = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	//To judge whether the register related to the target data object, and to be added into the global state unit
	bool yesNo1 = false;
	int index1 = 0;
	bool yesNo2 = false;
	int index2 = 0;
	uint64_t w = 1;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty())
	{
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName, "",an_globalStateUnit,&yesNo1,&index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot("",convertToString(an_instr_info->line2_dynValue),an_globalStateUnit,&yesNo2,&index2);
		}
		
		if(yesNo1&&yesNo2)//1 1
		{
			//whether they are the same varialbe
			if (an_globalStateUnit->mulStUni[index1]->corrAddr == convertToString(an_instr_info->line2_dynValue))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();
				struct an_intrStUni* eleStates_val = new an_intrStUni();
				struct an_intrStUni* eleStates_ret = new an_intrStUni();
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = convertToString(an_instr_info->line2_dynValue);

				for(int i=0;i<sz;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}

				for (int i = 0; i < sz;)
				{
					//eleStates[0].tempSts[i] = 0;
					if (sz==32)
					{
						eleStates_val->tempSts[i] = unpack754_32(pack754_32(an_instr_info->line1_dynValue)^w);
						eleStates_ret->tempSts[i] = unpack754_32(pack754_32(an_instr_info->line1_dynValue)^w);
					}else if (sz==64)
					{
						eleStates_val->tempSts[i] = unpack754_64(pack754_64(an_instr_info->line1_dynValue)^w);
						eleStates_val->tempSts[i] = unpack754_64(pack754_64(an_instr_info->line1_dynValue)^w);
					}
					if(i < sz -1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				struct an_intrStUni* eleStates_val = new an_intrStUni();
				struct an_intrStUni* eleStates_ret = new an_intrStUni();
				//while the fault on the first operand
				w = 1;
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = convertToString(an_instr_info->line2_dynValue);

				for(int i=0;i<sz;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}

				for (int i = 0; i < sz;)
				{
					//eleStates[0].tempSts[i] = 0;
					if (sz==32)
					{
						eleStates_val->tempSts[i] = unpack754_32(pack754_32(an_instr_info->line1_dynValue)^w);
						eleStates_ret->tempSts[i] = unpack754_32(pack754_32(an_instr_info->line1_dynValue)^w);
					}else if (sz==64)
					{
						eleStates_val->tempSts[i] = unpack754_64(pack754_64(an_instr_info->line1_dynValue)^w);
						eleStates_ret->tempSts[i] = unpack754_64(pack754_64(an_instr_info->line1_dynValue)^w);
					}
					if(i < sz -1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				
				//while the fault on the second operand
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();
				eleStates2->name = convertToString(an_instr_info->line2_dynValue);
				for (int i = 0; i < sz; i++)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			an_globalStateUnit->mulStUni[index1]->corrAddr = convertToString(an_instr_info->line2_dynValue);
		}else if (!yesNo1&&yesNo2)//0 1
		{
			struct an_intrStUni* eleStates = new an_intrStUni();
			eleStates->name = convertToString(an_instr_info->line2_dynValue);
			for (int i = 0; i < sz; i++)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);

			if (an_instr_info->line1_regORnot)
			{
				an_sglStUni->regName = an_instr_info->line1_regName;
			 	an_sglStUni->corrAddr = convertToString(an_instr_info->line2_dynValue);
			 	an_globalStateUnit->mulStUni.push_back(an_sglStUni);
			}else
			{
				an_sglStUni = NULL;
				delete an_sglStUni;
			}				
		}else if(yesNo1&&!yesNo2)//1 0
		{
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			w = 1;
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = convertToString(an_instr_info->line2_dynValue);

			for(int i=0;i<sz;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz;)
			{
				//eleStates[0].tempSts[i] = 0;
				if (sz==32)
				{
					eleStates_val->tempSts[i] = unpack754_32(pack754_32(an_instr_info->line1_dynValue)^w);
					eleStates_ret->tempSts[i] = unpack754_32(pack754_32(an_instr_info->line1_dynValue)^w);
				}else if (sz==64)
				{
					eleStates_val->tempSts[i] = unpack754_64(pack754_64(an_instr_info->line1_dynValue)^w);
					eleStates_ret->tempSts[i] = unpack754_64(pack754_64(an_instr_info->line1_dynValue)^w);
				}
				if(i < sz -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			an_instrStateUnit->subTarData1.push_back(eleStates_ret);

			an_globalStateUnit->mulStUni[index1]->corrAddr = convertToString(an_instr_info->line2_dynValue);
		}
	}else
	{
		int index3 = 0, index4 = 0;
		bool is1 = false, is2 = false;
		if(signSubTaData == "1")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1, &index3);
			}
			if (an_instr_info->line2_regORnot)
			{
				is2 = isOnInstrStaUnit(convertToString(an_instr_info->line2_dynValue),an_instrStateUnit->subTarData1, &index4);
			}
			
			if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = convertToString(an_instr_info->line2_dynValue);
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
		if(signSubTaData == "2")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2, &index3);
			}
			if (an_instr_info->line2_regORnot)
			{
				is2 = isOnInstrStaUnit(convertToString(an_instr_info->line2_dynValue),an_instrStateUnit->subTarData2, &index4);
			}
			
			if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = convertToString(an_instr_info->line2_dynValue);
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates);
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
		if(signSubTaData == "3")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3, &index3);
			}
			if (an_instr_info->line2_regORnot)
			{
				is2 = isOnInstrStaUnit(convertToString(an_instr_info->line2_dynValue),an_instrStateUnit->subTarData3, &index4);
			}
			
			if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = convertToString(an_instr_info->line2_dynValue);
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates);
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//For 'And or Or' instructions
void opcodeProFunction::OPCODE_AND_OR(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData, fmCounter *fmc){
	bool isNot1 = false, isNot2 = false, isNot3 = false;
	int index1 = 0,index2 = 0,index3 = 0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	long long deciN1 = an_instr_info->line1_dynValue;
	long long deciN2 = an_instr_info->line2_dynValue;
	long long w = 1;
	long long deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
		}
		//000;100;010;001;110;101;011;111
		// for 100
		if ((isNot1==1)&&(isNot2==0)&&(isNot3==0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for (int i = 0; i < bitLen;)
			{
				deciNXor = deciN1^w;
				switch(opcode)
				{
				case 23://And
					if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
					{
						eleStates->tempSts[i] = 1;
						fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor;
						eleStates_ret->tempSts[i] = deciNXor&deciN2;
					}
					break;
				case 24://Or
					if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
					{
						eleStates->tempSts[i] = 1;
						fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor;
						eleStates_ret->tempSts[i] = deciNXor|deciN2;
					}
					break;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 010
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN2^w;
				switch(opcode)
				{
				case 23://And
					if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
					{
						eleStates->tempSts[i] = 1;
						fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor;
						eleStates_ret->tempSts[i] = deciNXor&deciN1;
					}
					break;
				case 24://Or
					if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
					{
						eleStates->tempSts[i] = 1;
						fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor;
						eleStates_ret->tempSts[i] = deciNXor|deciN1;
					}
					break;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 001
		if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fmc->three_sorts_fm_statement_level[0]++;//statement level: fault masking on overwriting
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 110
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor;
							eleStates_ret->tempSts[i] = deciNXor&deciNXor;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor;
							eleStates_ret->tempSts[i] = deciNXor|deciNXor;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}
			else
			{
				//while faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor&deciN2;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor|deciN2;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor&deciN1;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor|deciN1;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//101
		if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;

					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor&deciN2;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor|deciN2;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor&deciN2;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor|deciN2;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				//for(int i=0;i<bitLen;)
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[0]++;//statement level: fault masking on overwriting
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 011
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;

					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor&deciN1;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor|deciN1;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor&deciN1;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor|deciN1;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[0]++;//statement level: fault masking on overwriting
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 111
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor&deciNXor;
							eleStates_ret->tempSts[i] = deciNXor&deciNXor;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val->tempSts[i] = deciNXor|deciNXor;
							eleStates_ret->tempSts[i] = deciNXor|deciNXor;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor&deciNXor;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor|deciNXor;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[0]++;//statement level: fault masking on overwriting
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor&deciN2;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor|deciN2;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor&deciN1;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor|deciN1;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor&deciN1;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor|deciN1;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor&deciN2;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor|deciN2;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor&deciN2;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates1->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val1->tempSts[i] = deciNXor;
							eleStates_ret1->tempSts[i] = deciNXor|deciN2;
						}
						break;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;

					switch(opcode)
					{
					case 23://And
						if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor&deciN1;
						}
						break;
					case 24://Or
						if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
						{
							eleStates2->tempSts[i] = 1;
							fmc->three_sorts_fm_statement_level[1]++;//statement level: fault masking on logic operations
						}else
						{
							//eleStates->tempSts[i] = 0;
							eleStates_val2->tempSts[i] = deciNXor;
							eleStates_ret2->tempSts[i] = deciNXor|deciN1;
						}
						break;
					}

					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[0]++;//statement level: fault masking on overwriting
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						switch(opcode)
						{
						case 23://And
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor&deciN2;
							}
							break;
						case 24://Or
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor|deciN2;
							}
							break;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						switch(opcode)
						{
						case 23://And
							if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor&deciN1;
							}
							break;
						case 24://Or
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor|deciN1;
							}
							break;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else{
							switch(opcode)
							{
							case 23:
								eleStates->tempSts[i] = deciNXor1&deciNXor2;
							case 24:
								eleStates->tempSts[i] = deciNXor1|deciNXor2;
							}
						}
					}else{
						switch(opcode)
							{
							case 23:
								eleStates->tempSts[i] = deciNXor1&deciNXor2;
							case 24:
								eleStates->tempSts[i] = deciNXor1|deciNXor2;
							}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData1[index1]->tempSts[i]=deciNXor1&deciNXor1;
							case 24://Or
								an_instrStateUnit->subTarData1[index1]->tempSts[i]=deciNXor1|deciNXor1;
							}
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1&deciNXor1;
							case 24://Or
								an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1|deciNXor1;
							}
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1&deciNXor2;
							case 24://Or
								an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1|deciNXor2;
							}
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciN2&deciNXor1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciN2&deciNXor1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciN2|deciNXor1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciN2|deciNXor1;
								}
								break;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1&deciNXor2;
							case 24://Or
								an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1|deciNXor2;
							}
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciN1&deciNXor2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciN1|deciNXor2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciN2|deciNXor1;
								}
								break;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}
					}else{
						switch(opcode)
							{
							case 23://And
								if ((deciNXor1!=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1&deciNXor2;
								}else if ((deciNXor1=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1&deciNXor2;
								}else if ((deciNXor1!=0)&&(deciNXor2=0))
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1&deciN2;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}
							case 24://Or
								if ((deciNXor1!=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1|deciNXor2;
								}else if ((deciNXor1=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1|deciNXor2;
								}else if ((deciNXor1!=0)&&(deciNXor2=0))
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1&deciN2;
								}else
								{
									an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}
							}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if(signSubTaData == "2")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						switch(opcode)
						{
						case 23://And
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor&deciN2;
							}
							break;
						case 24://Or
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor|deciN2;
							}
							break;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						switch(opcode)
						{
						case 23://And
							if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor&deciN1;
							}
							break;
						case 24://Or
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor|deciN1;
							}
							break;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else{
							switch(opcode)
							{
							case 23:
								eleStates->tempSts[i] = deciNXor1&deciNXor2;
							case 24:
								eleStates->tempSts[i] = deciNXor1|deciNXor2;
							}
						}
					}else{
						switch(opcode)
							{
							case 23:
								eleStates->tempSts[i] = deciNXor1&deciNXor2;
							case 24:
								eleStates->tempSts[i] = deciNXor1|deciNXor2;
							}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData2[index1]->tempSts[i]=deciNXor1&deciNXor1;
							case 24://Or
								an_instrStateUnit->subTarData2[index1]->tempSts[i]=deciNXor1|deciNXor1;
							}
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1&deciNXor1;
							case 24://Or
								an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1|deciNXor1;
							}
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1&deciNXor2;
							case 24://Or
								an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1|deciNXor2;
							}
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciN2&deciNXor1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciN2&deciNXor1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciN2|deciNXor1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciN2|deciNXor1;
								}
								break;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1&deciNXor2;
							case 24://Or
								an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1|deciNXor2;
							}
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciN1&deciNXor2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciN1|deciNXor2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciN2|deciNXor1;
								}
								break;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}
					}else{
						switch(opcode)
							{
							case 23://And
								if ((deciNXor1!=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1&deciNXor2;
								}else if ((deciNXor1=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1&deciNXor2;
								}else if ((deciNXor1!=0)&&(deciNXor2=0))
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1&deciN2;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}
							case 24://Or
								if ((deciNXor1!=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1|deciNXor2;
								}else if ((deciNXor1=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1|deciNXor2;
								}else if ((deciNXor1!=0)&&(deciNXor2=0))
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1&deciN2;
								}else
								{
									an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}
							}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if(signSubTaData == "3")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						switch(opcode)
						{
						case 23://And
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor&deciN2;
							}
							break;
						case 24://Or
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor|deciN2;
							}
							break;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						switch(opcode)
						{
						case 23://And
							if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor&deciN1;
							}
							break;
						case 24://Or
							if (an_arguConfig->faultMaskRatio>=abs((deciNXor|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor|deciN1;
							}
							break;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									eleStates->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									eleStates->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else{
							switch(opcode)
							{
							case 23:
								eleStates->tempSts[i] = deciNXor1&deciNXor2;
							case 24:
								eleStates->tempSts[i] = deciNXor1|deciNXor2;
							}
						}
					}else{
						switch(opcode)
							{
							case 23:
								eleStates->tempSts[i] = deciNXor1&deciNXor2;
							case 24:
								eleStates->tempSts[i] = deciNXor1|deciNXor2;
							}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData3[index1]->tempSts[i]=deciNXor1&deciNXor1;
							case 24://Or
								an_instrStateUnit->subTarData3[index1]->tempSts[i]=deciNXor1|deciNXor1;
							}
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1&deciNXor1;
							case 24://Or
								an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1|deciNXor1;
							}
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1&deciNXor2;
							case 24://Or
								an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1|deciNXor2;
							}
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2&deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2&deciN1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor2|deciN1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2|deciN1;
								}
								break;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciN2&deciNXor1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciN2&deciNXor1;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciN2|deciNXor1)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciN2|deciNXor1;
								}
								break;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1&deciNXor2;
							case 24://Or
								an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1|deciNXor2;
							}
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciN1&deciNXor2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciN1&deciNXor2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciN1|deciNXor2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciN2|deciNXor1;
								}
								break;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							switch(opcode)
							{
							case 23://And
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1&deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1&deciN2;
								}
								break;
							case 24://Or
								if (an_arguConfig->faultMaskRatio>=abs((deciNXor1|deciN2)-an_instr_info->liner_dynValue)/(an_instr_info->liner_dynValue))
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
									fCounter->three_sorts_fm_err_propagtion_level[2]++;
								}else
								{
									an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1|deciN2;
								}
								break;
							}
						}
					}else{
						switch(opcode)
							{
							case 23://And
								if ((deciNXor1!=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1&deciNXor2;
								}else if ((deciNXor1=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1&deciNXor2;
								}else if ((deciNXor1!=0)&&(deciNXor2=0))
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1&deciN2;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}
							case 24://Or
								if ((deciNXor1!=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1|deciNXor2;
								}else if ((deciNXor1=0)&&(deciNXor2!=0))
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1|deciNXor2;
								}else if ((deciNXor1!=0)&&(deciNXor2=0))
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1&deciN2;
								}else
								{
									an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
									fCounter->three_sorts_fm_err_propagtion_level[0]++;
								}
							}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//For 'MUL' trace blocks
//which is used to multiply two variables and then store the result in a new register.
/*
Here we store the two variables and their register-names (line1 and line 2), and then the 
result and its register-name (liner).  Update the state-unit data structure.
*/
void opcodeProFunction::OPCODE_MUL(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string signSubTaData){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	//reserve the values into temp_state
	//an_tempStateUnitTier1->mulVal1 = an_instr_info->line1_dynValue;//the first variable for multiplication
	//an_tempStateUnitTier1->mulVal1Reg = an_instr_info->line1_regName;//the register of the first variable
	//an_tempStateUnitTier1->mulVal2 = an_instr_info->line2_dynValue;//the second variable for multiplication
	//an_tempStateUnitTier1->mulVal2Reg = an_instr_info->line2_regName;//the register of the second varibale
	//an_tempStateUnitTier1->mulValr = an_instr_info->liner_dynValue;//the final resutl of the multiplication
	//an_tempStateUnitTier1->mulValrReg = an_instr_info->liner_regName;//the register of the final result
	bool isNot1 = false, isNot2 = false, isNot3 = false;
	int index1 = 0,index2 = 0,index3 = 0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	long long deciN1 = an_instr_info->line1_dynValue;
	long long deciN2 = an_instr_info->line2_dynValue;
	long long w = 1;
	long long deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		//add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		//add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		//add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
        if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
		}
		//000;100;010;001;110;101;011;111
		// for 100
		if ((isNot1==1)&&(isNot2==0)&&(isNot3==0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for (int i = 0; i < bitLen;)
			{
				deciNXor = deciN1^w;
				if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor*deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 010
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN2^w;
				if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciN2)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor*deciN1;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 001
		if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 110
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor*deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}
			else
			{
				//while faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciN2)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 101
		if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 011
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciN2)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciN2)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 111
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor*deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = deciNXor;
					eleStates_ret1->tempSts[i] = deciNXor*deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciN2)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciN2)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciN2)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN1)/(double)deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN2)/(double)deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs((double)deciNXor1-(double)deciN1)/(double)deciN1))
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1*deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1*deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=deciNXor1*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1*deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1*deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1*deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN1)/(double)deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN2)/(double)deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs((double)deciNXor1-(double)deciN1)/(double)deciN1))
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1*deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1*deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=deciNXor1*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1*deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1*deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1*deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "3")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN1)/(double)deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN2)/(double)deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs((double)deciNXor1-(double)deciN1)/(double)deciN1))
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1*deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1*deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=deciNXor1*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1*deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1*deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1*deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}


//For 'FMUL' instruction
void opcodeProFunction::OPCODE_FMUL(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string signSubTaData){
	bool isNot1 = false, isNot2 = false, isNot3 = false;
	int index1 = 0,index2 = 0,index3 = 0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	double deciN1 = an_instr_info->line1_dynValue;
	double deciN2 = an_instr_info->line2_dynValue;
	uint64_t w = 1;
	double deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
		}		
		
		//000;100;010;001;110;101;011;111
		// for 100
		if ((isNot1==1)&&(isNot2==0)&&(isNot3==0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for (int i = 0; i < bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN1)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN1)^w);
				}

				//deciNXor = deciN1^w;
				if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor*deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 010
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for(int i=0;i<bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN2)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN2)^w);
				}
				//deciNXor = deciN2^w;
				if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciN2)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor*deciN1;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 001
		if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 110
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor*deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}
			else
			{
				//while faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciN2)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 101
		if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 011
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciN2)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciN2)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 111
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor*deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = deciNXor;
					eleStates_ret1->tempSts[i] = deciNXor*deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciN2)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciN2)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor*deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciN2)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor*deciN1;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs(deciNXor1-deciN1)/deciN1))
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1*deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1*deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=deciNXor1*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1*deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1*deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1*deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1*deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs(deciNXor1-deciN1)/deciN1))
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1*deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1*deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=deciNXor1*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1*deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1*deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1*deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1*deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "3")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs(deciNXor1-deciN1)/deciN1))
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1*deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1*deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=deciNXor1*deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1*deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciN2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor2*an_instr_info->line1_dynValue;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1*deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1*deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1*deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1*deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//For 'ALLOCA' trace blocks
//which is used to allocate a memory space for write and read operations, etc,.
//Here we just need to take a note of the memory address and its register-name
//there is no fault masking here
//void opcodeProFunction::OPCODE_ALLOCA(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();

	//reserve the values into temp_state
	/*an_tempStateUnitTier1->alloAddr =convertToString( an_instr_info->liner_dynValue);
	an_tempStateUnitTier1->alloAddrReg = an_instr_info->liner_regName;*/

	//there is no need to add to target data list

	//push back the state unit into the state vector 'statVector'
	//statVector.push_back(an_tempStateUnitTier1);
//}

//For 'ICMP' trace blocks
//Which is used for comparison of two input arguments, 
/*
Step 1: determine if any of the two input arguments is from the target data object. 
Step 2: if yes, calculating the bitwise fault-masking probability based on the comparison-threshold. 
Note that the fault-masking probability of the ICMP should not be corresponded to the 
fault-masking probability of its branches. 
*/
void opcodeProFunction::OPCODE_ICMP(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, fmCounter *fmc){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	bool isNot = false;
	int index =0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	long long deciN1 = an_instr_info->line1_dynValue;
	long long w = 1;
	long long deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty())
	{
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot, &index);
		}

		if(isNot == 1)
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;

			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN1^w;
				if((deciN1<=an_instr_info->line2_dynValue)&&(deciNXor<=an_instr_info->line2_dynValue))
				{
					eleStates->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[1]++;//the second element
				}
				else if((deciN1>an_instr_info->line2_dynValue)&&(deciNXor>an_instr_info->line2_dynValue))
				{
					eleStates->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[1]++;//the second element
				}else
				{
					eleStates->tempSts[i] = 0;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
	}else
	{
		bool yesNo1 = false, yesNo2 = false, yesNo3 = false;
		int index1 = 0, index2 = 0, index3 = 0;
		if (an_instr_info->line1_regORnot)
		{
			yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1,&index1);
			yesNo2 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2,&index2);
			yesNo3 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3,&index3);
		}
		
		if (yesNo1)
		{
			for(int i=0;i<bitLen;)
			{
				if (an_instrStateUnit->subTarData1[index1]->tempSts[i] != 0)
				{
					if((deciN1>an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData1[index1]->tempSts[i]>an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}else if ((deciN1<=an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData1[index1]->tempSts[i]<=an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}
				}
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}	
		}
		if (yesNo2)
		{
			for(int i=0;i<bitLen;)
			{
				if (an_instrStateUnit->subTarData2[index2]->tempSts[i] != 0)
				{
					if((deciN1>an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData2[index2]->tempSts[i]>an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}else if ((deciN1<=an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData2[index2]->tempSts[i]<=an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}
				}
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
		}
		if (yesNo3)
		{
			for(int i=0;i<bitLen;)
			{
				if (an_instrStateUnit->subTarData3[index3]->tempSts[i] != 0)
				{
					if((deciN1>an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData3[index3]->tempSts[i]>an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}else if ((deciN1<=an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData3[index3]->tempSts[i]<=an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}
				}	
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
		}
	}
}

//For 'FCMP' trace block
void opcodeProFunction::OPCODE_FCMP(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, fmCounter *fmc){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	bool isNot = false;
	int index =0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	double deciN1 = an_instr_info->line1_dynValue;
	uint64_t w = 1;
	double deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty())
	{
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot, &index);
		}

		if(isNot == 1)
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;

			for(int i=0;i<bitLen;)
			{
				//deciNXor = deciN1^w;
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN1)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN1)^w);
				}
				if((deciN1<=an_instr_info->line2_dynValue)&&(deciNXor<=an_instr_info->line2_dynValue))
				{
					eleStates->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[1]++;//the second element
				}
				else if((deciN1>an_instr_info->line2_dynValue)&&(deciNXor>an_instr_info->line2_dynValue))
				{
					eleStates->tempSts[i] = 1;
					fmc->three_sorts_fm_statement_level[1]++;//the second element
				}else
				{
					eleStates->tempSts[i] = 0;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
	}else
	{
		bool yesNo1 = false, yesNo2 = false, yesNo3 = false;
		int index1 = 0, index2 = 0, index3 = 0;
		if (an_instr_info->line1_regORnot)
		{
			yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1,&index1);
			yesNo2 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2,&index2);
			yesNo3 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3,&index3);
		}
		
		if (yesNo1)
		{
			for(int i=0;i<bitLen;)
			{
				if (an_instrStateUnit->subTarData1[index1]->tempSts[i] != 0)
				{
					if((deciN1>an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData1[index1]->tempSts[i]>an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}else if ((deciN1<=an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData1[index1]->tempSts[i]<=an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}
				}
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}	
		}
		if (yesNo2)
		{
			for(int i=0;i<bitLen;)
			{
				if (an_instrStateUnit->subTarData2[index2]->tempSts[i] != 0)
				{
					if((deciN1>an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData2[index2]->tempSts[i]>an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}else if ((deciN1<=an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData2[index2]->tempSts[i]<=an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}
				}
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
		}
		if (yesNo3)
		{
			for(int i=0;i<bitLen;)
			{
				if (an_instrStateUnit->subTarData3[index3]->tempSts[i] != 0)
				{
					if((deciN1>an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData3[index3]->tempSts[i]>an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}else if ((deciN1<=an_instr_info->line2_dynValue)&&(an_instrStateUnit->subTarData3[index3]->tempSts[i]<=an_instr_info->line2_dynValue))
					{
						an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[1]++;
					}
				}	
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
		}
	}
}

//For 'RET' trace block
//which is used to return a value back while in a function.
//Here we record the returned value and its register-name.
//void opcodeProFunction::OPCODE_RET(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();

	//reserve the values into temp_state
	/*an_tempStateUnitTier1->retVal =convertToString( an_instr_info->line1_dynValue);
	an_tempStateUnitTier1->retValReg = an_instr_info->line1_regName;*/

	//there is no need to add to target data list

//push back the state unit into the state vector 'statVector'
//statVector.push_back(an_tempStateUnitTier1);
//}

//For 'Trunc' instructions
void opcodeProFunction::OPCODE_TRUNC(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign, string signSubTaData){
	struct sglStUni *an_sglStUni = new sglStUni();
	int sz = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	int sz1 = atoi(an_instr_info->liner_sizeOfArgu.c_str());
	uint64_t w = 1;
	bool yesNo1 = false;
	bool yesNo2 = false;
	int index1 = 0;
	int index2 = 0;
	if (sign == "ini")
	{
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1,&index1);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&yesNo2,&index2);
		}
		
		if (yesNo1&!yesNo2)//1 0
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			an_sglStUni->regName = an_instr_info->liner_regName;
			an_sglStUni->corrAddr = "";	

			for(int i=0;i<sz;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz;)
			{
				if (i>sz1-1)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
					//eleStates_val->tempSts[i] = 0;
				}else
				{
					eleStates_val->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
					eleStates_ret->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
				}
				if(i < sz -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				an_globalStateUnit->mulStUni.push_back(an_sglStUni);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
				an_sglStUni = NULL;
				delete an_sglStUni;
			}
			
		}else if (!yesNo1&yesNo2)//0 1, this kind of situation maybe not true in practical, but I still list here.
		{
			struct an_intrStUni* eleStates = new an_intrStUni();
			eleStates->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz; i++)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);

			//an_globalStateUnit->mulStUni.erase(an_globalStateUnit->mulStUni.begin()+index2);
		}else if (yesNo1&&yesNo2)//1 1
		{
			//Anzheng's comment: whether their related memory addresses can be the same? 

			//while the fault on the first operand
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<sz;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz;)
			{
				if (i>sz1-1)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
					//eleStates_val->tempSts[i] = 0;
				}else
				{
					eleStates_val->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
					eleStates_ret->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
				}
				if(i < sz -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			
			//while the fault on the second operand
			struct an_intrStUni* eleStates1 = new an_intrStUni();
			eleStates1->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz; i++)
			{
				eleStates1->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData2.push_back(eleStates);
		}
	}else if (sign == "err")
	{
		int index3 = 0, index4 = 0;
		bool is1 = false, is2 = false;
		if(signSubTaData == "1")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData1, &index4);
			}
			
			if (is1&&is2)//1 1 
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
		if(signSubTaData == "2")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData2, &index4);
			}
			
			if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
		if(signSubTaData == "3")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData3, &index4);
			}
			
			if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}	
}

//For 'FDIV' instruction
void opcodeProFunction::OPCODE_FDIV(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string signSubTaData){
	
	bool isNot1 = false, isNot2 = false, isNot3 = false;
	int index1 = 0,index2 = 0,index3 = 0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	double deciN1 = an_instr_info->line1_dynValue;
	double deciN2 = an_instr_info->line2_dynValue;
	uint64_t w = 1;
	double deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
		}		
		
		//000;100;010;001;110;101;011;111
		// for 100
		if ((isNot1==1)&&(isNot2==0)&&(isNot3==0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for (int i = 0; i < bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN1)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN1)^w);
				}

				//deciNXor = deciN1^w;
				if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor/deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 010
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for(int i=0;i<bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN2)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN2)^w);
				}
				//deciNXor = deciN2^w;
				if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciNXor)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciN1/deciNXor;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 001
		if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 110
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = 0;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}
			else
			{
				//while faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor/deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciNXor)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1/deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 101
		if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor/deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor/deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 011
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciNXor)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciN1/deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciNXor)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciN1/deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 111
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor/deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = deciNXor;
					eleStates_ret1->tempSts[i] = deciNXor/deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor/deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciNXor)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1/deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciNXor)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciN1/deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor/deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN1)/deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor/deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor-deciN2)/deciNXor)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1/deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor/deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/deciNXor;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1/deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs(deciNXor1-deciN1)/deciN1))
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1/deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1/deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;

							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=deciNXor1/deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1/deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1/deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1/deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1/deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor/deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/deciNXor;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1/deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs(deciNXor1-deciN1)/deciN1))
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1/deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1/deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;

							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=deciNXor1/deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1/deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1/deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1/deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1/deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "3")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor/deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/deciNXor;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1/deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs(deciNXor1-deciN1)/deciN1))
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1/deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1/deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;

							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=deciNXor1/deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1/deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue/deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1/deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1/deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1/deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//For 'SExt & ZExt' instructions
void opcodeProFunction::OPCODE_ZSEXT(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign, string signSubTaData){
	struct sglStUni *an_sglStUni = new sglStUni();
	int sz_xiao = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	int sz_da = atoi(an_instr_info->liner_sizeOfArgu.c_str());
	uint64_t w = 1;
	bool yesNo1 = false;	
	bool yesNo2 = false;
	int index1 = 0;
	int index2 = 0;
	if (sign == "ini")
	{
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1,&index1);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&yesNo2,&index2);
		}
		
		if (yesNo1&!yesNo2)//1 0
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			an_sglStUni->regName = an_instr_info->liner_regName;
			an_sglStUni->corrAddr = "";	

			for(int i=0;i<sz_da;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz_da;)
			{
				if (i<sz_xiao)
				{
					eleStates_val->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
					eleStates_ret->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
					//eleStates_val->tempSts[i] = 0;
				}else
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
				}
				if(i < sz_xiao -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				an_globalStateUnit->mulStUni.push_back(an_sglStUni);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
				an_sglStUni = NULL;
				delete an_sglStUni;
			}
		}else if (!yesNo1&&yesNo2)//0 1
		{
			struct an_intrStUni* eleStates = new an_intrStUni();
			eleStates->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz_da; i++)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}else if (yesNo1&&yesNo2)//1 1
		{
			//Anzheng's comment: whether their related memory addresses can be the same? 

			//while the fault on the first operand
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<sz_da;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz_da;)
			{
				if (i<sz_xiao)
				{
					eleStates_val->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
					eleStates_ret->tempSts[i] = (long long)an_instr_info->line1_dynValue^w;
					//eleStates_val->tempSts[i] = 0;
				}else
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
				}
				if(i < sz_xiao -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			
			//while the fault on the second operand
			struct an_intrStUni* eleStates2 = new an_intrStUni();
			eleStates2->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz_da; i++)
			{
				eleStates2->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates2);
		}
	}else if (sign == "err")
	{
		int index3 = 0, index4 = 0;
		bool is1 = false, is2 = false;
		if(signSubTaData == "1")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData1, &index4);
			}

			if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz_da;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz_da;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz_da;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData2, &index4);
			}

			if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz_da;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz_da;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz_da;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "3")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData3, &index4);
			}

			if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz_da;)
				{
					eleStates->tempSts[i] = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz_da;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&is2)//1 1
			{
				for (int i = 0; i < sz_da;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//For 'Switch' instructions
void opcodeProFunction::OPCODE_SWITCH(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign){
	int sz = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	bool yesNo = false;
	int index = 0, index1 = 0, index2 = 0, index3 = 0;
	if (an_instr_info->line1_regORnot)
	{
		add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo,&index);
	}

	bool is1 = false;
	if (an_instr_info->line3_arguId != "")
	{
		bool is1 = (an_instr_info->line3_dynValue != an_instr_info->line1_dynValue);
	}
	if (an_instr_info->line5_arguId != "")
	{
		bool is1 = (an_instr_info->line5_dynValue != an_instr_info->line1_dynValue)&&(an_instr_info->line3_dynValue != an_instr_info->line1_dynValue);
	}
	if (an_instr_info->line7_arguId != "")
	{
		bool is1 = (an_instr_info->line7_dynValue != an_instr_info->line1_dynValue)&&(an_instr_info->line5_dynValue != an_instr_info->line1_dynValue)&&(an_instr_info->line3_dynValue != an_instr_info->line1_dynValue);
	}
	if (an_instr_info->line9_arguId != "")
	{
		bool is1 = (an_instr_info->line9_dynValue != an_instr_info->line1_dynValue)&&(an_instr_info->line7_dynValue != an_instr_info->line1_dynValue)&&(an_instr_info->line5_dynValue != an_instr_info->line1_dynValue)&&(an_instr_info->line3_dynValue != an_instr_info->line1_dynValue);
	}

	if (sign == "ini")
	{
		if (an_instr_info->line1_regORnot)
		{
			if (yesNo)
			{
				if (is1)
				{
					//go to the default branch, it is still go the default branches if only one bit flip happens
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->line1_regName;
					for (int i = 0; i < sz;)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[1]++;
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					//go to certain branch, it cannot go back to the same branch after one bit flip happens
					struct an_intrStUni* eleStates = new an_intrStUni();
					eleStates->name = an_instr_info->line1_regName;
					for (int i = 0; i < sz;)
					{
						eleStates->tempSts[i] = 0;
						i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					}
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}
			}
		}
	}else
	{
		bool isNot1 = false, isNot2 = false, isNot3=false;
		if (an_instr_info->line1_regORnot)
		{
			if(!an_instrStateUnit->subTarData1.empty())
				bool isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1, &index1);
			if(!an_instrStateUnit->subTarData2.empty())
				bool isNot2 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2, &index2);
			if(!an_instrStateUnit->subTarData3.empty())
				bool isNot3 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3, &index3);
		}
		if (isNot1)
		{
			if (is1)
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[1]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (isNot2)
		{
			if (is1)
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[1]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (isNot3)
		{
			if (is1)
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[1]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//for 'SDIV' instructions
void opcodeProFunction::OPCODE_SDIV(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string signSubTaData){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	//reserve the values into temp_state
	//an_tempStateUnitTier1->mulVal1 = an_instr_info->line1_dynValue;//the first variable for multiplication
	//an_tempStateUnitTier1->mulVal1Reg = an_instr_info->line1_regName;//the register of the first variable
	//an_tempStateUnitTier1->mulVal2 = an_instr_info->line2_dynValue;//the second variable for multiplication
	//an_tempStateUnitTier1->mulVal2Reg = an_instr_info->line2_regName;//the register of the second varibale
	//an_tempStateUnitTier1->mulValr = an_instr_info->liner_dynValue;//the final resutl of the multiplication
	//an_tempStateUnitTier1->mulValrReg = an_instr_info->liner_regName;//the register of the final result
	bool isNot1 = false, isNot2 = false, isNot3 = false;
	int index1 = 0,index2 = 0,index3 = 0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	long long deciN1 = an_instr_info->line1_dynValue;
	long long deciN2 = an_instr_info->line2_dynValue;
	long long w = 1;
	long long deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		//add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		//add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		//add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
        if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
		}
		//000;100;010;001;110;101;011;111
		// for 100
		if ((isNot1==1)&&(isNot2==0)&&(isNot3==0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for (int i = 0; i < bitLen;)
			{
				deciNXor = deciN1^w;
				if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = (double)deciNXor/((double)deciN2);
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 010
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN2^w;
				if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciNXor)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = (double)deciN1/((double)deciNXor);
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 001
		if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 110
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = 0;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}
			else
			{
				//while faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = (double)deciNXor/((double)deciN2);
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciNXor)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = (double)deciN1/((double)deciNXor);
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 101
		if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = (double)deciNXor/((double)deciN2);
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = (double)deciNXor/((double)deciN2);
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 011
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciNXor)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = (double)deciN1/((double)deciNXor);
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciNXor)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = (double)deciN1/(double)deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 111
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = ((double)deciNXor)/((double)deciNXor);
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					//eleStates->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = deciNXor;
					eleStates_ret1->tempSts[i] = (double)deciNXor/(double)deciNXor;
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor/deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciNXor)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = (double)deciN1/(double)deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciNXor)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = (double)deciN1/(double)deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = (double)deciNXor/(double)deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN1)/(double)deciN1)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = (double)deciNXor/(double)deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs((double)deciNXor-(double)deciN2)/(double)deciNXor)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = (double)deciN1/(double)deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN1)/(double)deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = (double)deciNXor/(double)deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN2)/(double)deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs((double)deciNXor1-(double)deciN1)/(double)deciN1))
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=(double)deciNXor1/(double)deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=(double)deciNXor1/(double)deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1/deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1/deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1/deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN1)/(double)deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = (double)deciNXor/(double)deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN2)/(double)deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs((double)deciNXor1-(double)deciN1)/(double)deciN1))
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=(double)deciNXor1/(double)deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=(double)deciNXor1/(double)deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1/deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1/deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1/deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "3")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN1)/(double)deciN1;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = (double)deciNXor/(double)deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs((double)deciNXor - (double)deciN2)/(double)deciN2;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor*deciN1;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if(an_arguConfig->faultMaskRatio>=(abs((double)deciNXor1-(double)deciN1)/(double)deciN1))
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=(double)deciNXor1/(double)deciNXor1;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=(double)deciNXor1/(double)deciNXor1;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = (double)deciNXor1/(double)deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor2-(double)deciN2)/(double)deciNXor2;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue/(double)deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs((double)deciNXor1-(double)deciN1)/(double)deciN1;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = (double)deciNXor1/an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1/deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1/deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1/deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}


//for 'SUB' instructions
void opcodeProFunction::OPCODE_SUB(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData){
	//First of all and all, we should judge how many operand of the entire operands are belong to the target data, according to which, 
	//we start our following analysis steps.
	//So, there will be 8 situations: 0 0 0; 1 0 0; 0 1 0; 0 0 1; 1 1 0; 0 1 1; 1 0 1; 1 1 1;
	bool yesNo1 = false, yesNo2 = false, yesNo3 = false;
	int index1 = 0, index2 = 0, index3 = 0;
	long long int deciN1 = an_instr_info->line1_dynValue;
	long long int deciN2 = an_instr_info->line2_dynValue;
	long long int deciNXor;	
	bool is_fm = false;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&yesNo2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit, &yesNo3, &index3);
		}

		//if yesNo1=0, yesNo2=0, and yesNo3=0, do nothing

		//if 1 0 0, 
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
		{
	        long long int w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN1^w;
				long long int negTurn;
				negTurn = deciNXor-deciN1;  
				if (negTurn<0)
					negTurn = -negTurn;
				is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;

				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor-deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
			
		}

		//for 0 1 0;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			long long int w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			
			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN2^w;
				long long int negTurn;
				negTurn = deciNXor-deciN2;
				if (negTurn<0)
					negTurn = -negTurn;
				is_fm = (an_arguConfig->faultMaskRatio>=(double)negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciN1 - deciNXor;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 0 0 1;
		if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			/*fmcVector[0]->counter = 1;
			fmcVector[0]->dynId = an_instr_info->line0_dynInstId;
			fmcVector[0]->numOfBits = atoi(an_instr_info->liner_sizeOfArgu.c_str());
			fmcVector[0]->numOfMaskBits = fmcVector[0]->numOfBits;
			fmcVector[0]->opId = an_instr_info->line0_opcodeId;*/
		}
		//for 1 1 0, although there are two operand related to the target data, we only consider one because they are the same
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}else
			{
				long long int w = 1;
				//while faults on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 1 0 1, 
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates_val->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				long long int w = 1;
				//while the faults on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;

				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 0 1 1;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates_val->tempSts[i] = deciN1-deciNXor;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				long long int w = 1;
				//while the fault on yesNo2
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 1 1 1;
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
				&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				long long int w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				long long int w = 1;
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val1->tempSts[i] = deciN2-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
			    w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				long long int w = 1;
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates_val1->tempSts[i] = deciN1-deciNXor;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				//bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				w = 1;
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				long long int w = 1;
				//while the fault on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					long long int negTurn;
					negTurn = deciNXor-deciN1;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				//bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					long long int negTurn;
					negTurn = deciNXor-deciN2;
					if (negTurn<0)
						negTurn = -negTurn;
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else{
		if(signSubTaData == "1")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor-deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1-deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1-deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1-deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=0;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1-deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1-deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1-deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor-deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1-deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1-deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1-deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=0;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1-deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1-deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1-deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if(signSubTaData == "3")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciNXor-deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
						}else{
							eleStates->tempSts[i] = deciN1-deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1-deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1-deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=0;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1-deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1-deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1-deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}

//for 'FSUB' instructions
void opcodeProFunction::OPCODE_FSUB(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData){
	//First of all and all, we should judge how many operand of the entire operands are belong to the target data, according to which, 
	//we start our following analysis steps.
	//So, there will be 8 situations: 0 0 0; 1 0 0; 0 1 0; 0 0 1; 1 1 0; 0 1 1; 1 0 1; 1 1 1;

	bool yesNo1 = false, yesNo2 = false, yesNo3 = false;
	bool is_fm = false;
	int index1 = 0, index2 = 0, index3 = 0;	
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	double deciN1 = an_instr_info->line1_dynValue;
	double deciN2 = an_instr_info->line2_dynValue;
	double deciNXor;
	uint64_t w = 1;

	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&yesNo2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit, &yesNo3, &index3);
		}
		//if yesNo1=0, yesNo2=0, and yesNo3=0, do nothing

		//if 1 0 0, 	
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			//int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for(int i=0;i<bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN1)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN1)^w);
				}
				
				double negTurn;
				negTurn = abs(deciNXor-deciN1);
				is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor-deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}

		//for 0 1 0;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			
			for(int i=0;i<bitLen;)
			{
				if (bitLen==32)
				{
					deciNXor = unpack754_32(pack754_32(deciN2)^w);
				}else if (bitLen==64)
				{
					deciNXor = unpack754_64(pack754_64(deciN2)^w);
				}
				
				double negTurn;
				negTurn = abs(deciNXor-deciN2);
				is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
				if(is_fm)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciN1-deciNXor;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}

		//for 0 0 1;
		if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 1 1 0, although there are two operand related to the target data, we only consider one because they are the same
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}else
			{
				w = 1;
				//while faults on yesNo1
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}

					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 1 0 1, 
		if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;

				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 0 1 1;
		if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
				    double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val->tempSts[i] = deciN1-deciNXor;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}

		//for 1 1 1;
		if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
				&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val->tempSts[i] = 0;
					//eleStates_ret->tempSts[i] = 0;
				}
				
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				//bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates_val1->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;

					}else{
						eleStates_val1->tempSts[i] = deciN1-deciNXor;

					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
				    double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN1)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN1)^w);
					}
					//deciNXor = deciN1^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN1);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						//eleStates1->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor-deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				
				for(int i=0;i<bitLen;)
				{
					if (bitLen==32)
					{
						deciNXor = unpack754_32(pack754_32(deciN2)^w);
					}else if (bitLen==64)
					{
						deciNXor = unpack754_64(pack754_64(deciN2)^w);
					}
					//deciNXor = deciN2^w;
					double negTurn;
					negTurn = abs(deciNXor-deciN2);
					is_fm = (an_arguConfig->faultMaskRatio>=negTurn/an_instr_info->liner_dynValue);
					if(is_fm)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else{
						eleStates2->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1-deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor-deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}	
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1-deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1-deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1-deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;

						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1-deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1-deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1-deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor-deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}	
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1-deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1-deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1-deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;

						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1-deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1-deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1-deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if(signSubTaData == "3")
		{
			double deciNXor1;
			double deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				yesNo1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				yesNo2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				yesNo3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			
			// 0 0 0
			// 1 0 0
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN1)/an_instr_info->liner_dynValue;
						if (stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciNXor-deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}	
			}
			// 0 1 0 
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						bool stw = an_arguConfig->faultMaskRatio >= abs(deciNXor - deciN2)/an_instr_info->liner_dynValue;
						if(stw)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else{
							eleStates->tempSts[i] = deciN1-deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((yesNo1 == 0)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
	     		an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
				fCounter->three_sorts_fm_err_propagtion_level[0]++;
			}
			// 1 1 0
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))
						{
							if(an_arguConfig->faultMaskRatio>=(deciNXor1-an_instr_info->line1_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if(an_arguConfig->faultMaskRatio>=abs(deciNXor2-an_instr_info->line2_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								eleStates->tempSts[i] = 0;
							}else{
								eleStates->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1-deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1-deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((yesNo1 == 0)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;

						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((yesNo1 == 1)&&(yesNo2 == 0)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((yesNo1 == 1)&&(yesNo2 == 1)&&(yesNo3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor2-deciN2)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = an_instr_info->line1_dynValue-deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							bool stw = an_arguConfig->faultMaskRatio>=abs(deciNXor1-deciN1)/an_instr_info->liner_dynValue;
							if(stw)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1-an_instr_info->line2_dynValue;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1+deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1-deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1-deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1-deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}


//for 'SHR' instructions
void opcodeProFunction::OPCODE_SHR(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit,string sign, string signSubTaData){
	struct sglStUni *an_sglStUni = new sglStUni();
	int sz = atoi(an_instr_info->liner_sizeOfArgu.c_str());
	int shifting_len = an_instr_info->line2_dynValue;
	uint64_t w = 1;
	long long deciN1 = an_instr_info->line1_dynValue;
	long long deciN2 = an_instr_info->liner_dynValue;
	long long deciNXor;
	bool yesNo1 = false;
	bool yesNo2 = false;
	int index1 = 0;
	int index2 = 0;
	if (sign == "ini")
	{
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1,&index1);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&yesNo2,&index2);
		}
		
		if (yesNo1&!yesNo2)//1 0
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			an_sglStUni->regName = an_instr_info->liner_regName;
			an_sglStUni->corrAddr = "";	

			for(int i=0;i<sz;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz;)
			{
				deciNXor = deciN1^w;
				if(an_arguConfig->faultMaskRatio>=(double)(deciNXor>>shifting_len-deciN2)/(double)deciN2)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
				}else
				{
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor>>shifting_len;
				}
				if(i < sz -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				an_globalStateUnit->mulStUni.push_back(an_sglStUni);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
				an_sglStUni = NULL;
				delete an_sglStUni;
			}
			
		}else if (!yesNo1&yesNo2)//0 1, this kind of situation maybe not true in practical, but I still list here.
		{
			struct an_intrStUni* eleStates = new an_intrStUni();
			eleStates->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz; i++)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);

			//an_globalStateUnit->mulStUni.erase(an_globalStateUnit->mulStUni.begin()+index2);
		}else if (yesNo1&&yesNo2)//1 1
		{
			//Anzheng's comment: whether their related memory addresses can be the same? 

			//while the fault on the first operand
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<sz;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz;)
			{
				deciNXor = deciN1^w;
				if(an_arguConfig->faultMaskRatio>=(double)(deciNXor>>shifting_len-deciN2)/(double)deciN2)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
				}else
				{
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor>>shifting_len;
				}
				if(i < sz -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			
			//while the fault on the second operand
			struct an_intrStUni* eleStates1 = new an_intrStUni();
			eleStates1->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz; i++)
			{
				eleStates1->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData2.push_back(eleStates);
		}
	}else if (sign == "err")
	{
		long long deciNXor1, deciNXor2;
		int index3 = 0, index4 = 0;
		bool is1 = false, is2 = false;
		if(signSubTaData == "1")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData1, &index4);
			}
	
			if (is1&&is2)//1 1 
			{
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index4]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1>>shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}else
						{
							an_instrStateUnit->subTarData1[index4]->tempSts[i] = deciNXor1>>shifting_len;
						}
					}else
					{
						an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[0]++;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1>>shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							eleStates->tempSts[i] = 0;
						}else
						{
							eleStates->tempSts[i] = deciNXor1>>shifting_len;
						}
					}else
					{
						eleStates->tempSts[i] = 0;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}if(signSubTaData == "2")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData2, &index4);
			}
	
			if (is1&&is2)//1 1 
			{
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index4]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1>>shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}else
						{
							an_instrStateUnit->subTarData2[index4]->tempSts[i] = deciNXor1>>shifting_len;
						}
					}else
					{
						an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[0]++;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1>>shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							eleStates->tempSts[i] = 0;
						}else
						{
							eleStates->tempSts[i] = deciNXor1>>shifting_len;
						}
					}else
					{
						eleStates->tempSts[i] = 0;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}if(signSubTaData == "3")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData3, &index4);
			}
	
			if (is1&&is2)//1 1 
			{
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index4]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1>>shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}else
						{
							an_instrStateUnit->subTarData3[index4]->tempSts[i] = deciNXor1>>shifting_len;
						}
					}else
					{
						an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[0]++;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1>>shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							eleStates->tempSts[i] = 0;
						}else
						{
							eleStates->tempSts[i] = deciNXor1>>shifting_len;
						}
					}else
					{
						eleStates->tempSts[i] = 0;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}	
}


//for 'SHL' instructions
void opcodeProFunction::OPCODE_SHL(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string sign, string signSubTaData){
	struct sglStUni *an_sglStUni = new sglStUni();
	int sz = atoi(an_instr_info->liner_sizeOfArgu.c_str());
	int shifting_len = an_instr_info->line2_dynValue;
	uint64_t w = 1;
	long long deciN1 = an_instr_info->line1_dynValue;
	long long deciN2 = an_instr_info->liner_dynValue;
	long long deciNXor;
	bool yesNo1 = false;
	bool yesNo2 = false;
	int index1 = 0;
	int index2 = 0;
	if (sign == "ini")
	{
		if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&yesNo1,&index1);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&yesNo2,&index2);
		}
		
		if (yesNo1&!yesNo2)//1 0
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			an_sglStUni->regName = an_instr_info->liner_regName;
			an_sglStUni->corrAddr = "";	

			for(int i=0;i<sz;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz;)
			{
				deciNXor = deciN1^w;
				if(an_arguConfig->faultMaskRatio>=(double)(deciNXor<<shifting_len-deciN2)/(double)deciN2)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
				}else
				{
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor<<shifting_len;
				}
				if(i < sz -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				an_globalStateUnit->mulStUni.push_back(an_sglStUni);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
				an_sglStUni = NULL;
				delete an_sglStUni;
			}
			
		}else if (!yesNo1&yesNo2)//0 1, this kind of situation maybe not true in practical, but I still list here.
		{
			struct an_intrStUni* eleStates = new an_intrStUni();
			eleStates->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz; i++)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);

			//an_globalStateUnit->mulStUni.erase(an_globalStateUnit->mulStUni.begin()+index2);
		}else if (yesNo1&&yesNo2)//1 1
		{
			//Anzheng's comment: whether their related memory addresses can be the same? 

			//while the fault on the first operand
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<sz;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}

			for (int i = 0; i < sz;)
			{
				deciNXor = deciN1^w;
				if(an_arguConfig->faultMaskRatio>=(double)(deciNXor<<shifting_len-deciN2)/(double)deciN2)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[1]++;
				}else
				{
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor<<shifting_len;
				}
				if(i < sz -1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			
			//while the fault on the second operand
			struct an_intrStUni* eleStates1 = new an_intrStUni();
			eleStates1->name = an_instr_info->liner_regName;
			for (int i = 0; i < sz; i++)
			{
				eleStates1->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
			}
			an_instrStateUnit->subTarData2.push_back(eleStates);
		}
	}else if (sign == "err")
	{
		long long deciNXor1, deciNXor2;
		int index3 = 0, index4 = 0;
		bool is1 = false, is2 = false;
		if(signSubTaData == "1")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData1, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData1, &index4);
			}
	
			if (is1&&is2)//1 1 
			{
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index4]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1<<shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}else
						{
							an_instrStateUnit->subTarData1[index4]->tempSts[i] = deciNXor1<<shifting_len;
						}
					}else
					{
						an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[0]++;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index3]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1<<shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							eleStates->tempSts[i] = 0;
						}else
						{
							eleStates->tempSts[i] = deciNXor1<<shifting_len;
						}
					}else
					{
						eleStates->tempSts[i] = 0;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData1[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}if(signSubTaData == "2")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData2, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData2, &index4);
			}
	
			if (is1&&is2)//1 1 
			{
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index4]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1<<shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}else
						{
							an_instrStateUnit->subTarData2[index4]->tempSts[i] = deciNXor1<<shifting_len;
						}
					}else
					{
						an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[0]++;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index3]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1<<shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							eleStates->tempSts[i] = 0;
						}else
						{
							eleStates->tempSts[i] = deciNXor1<<shifting_len;
						}
					}else
					{
						eleStates->tempSts[i] = 0;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData2[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}if(signSubTaData == "3")
		{
			if (an_instr_info->line1_regORnot)
			{
				is1 = isOnInstrStaUnit(an_instr_info->line1_regName,an_instrStateUnit->subTarData3, &index3);
			}
			if (an_instr_info->liner_regORnot)
			{
				is2 = isOnInstrStaUnit(an_instr_info->liner_regName,an_instrStateUnit->subTarData3, &index4);
			}
	
			if (is1&&is2)//1 1 
			{
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index4]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1<<shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}else
						{
							an_instrStateUnit->subTarData3[index4]->tempSts[i] = deciNXor1<<shifting_len;
						}
					}else
					{
						an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
						fCounter->three_sorts_fm_err_propagtion_level[0]++;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}else if (is1&&!is2)//1 0
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for (int i = 0; i < sz;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index3]->tempSts[i];
					if (deciNXor1!=0)
					{
						if(an_arguConfig->faultMaskRatio>=(double)(deciNXor1<<shifting_len-deciN2)/(double)deciN2)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[1]++;
							eleStates->tempSts[i] = 0;
						}else
						{
							eleStates->tempSts[i] = deciNXor1<<shifting_len;
						}
					}else
					{
						eleStates->tempSts[i] = 0;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}else if (!is1&&is2)//0 1
			{
				for (int i = 0; i < sz;)
				{
					an_instrStateUnit->subTarData3[index4]->tempSts[i] = 0;
					fCounter->three_sorts_fm_err_propagtion_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}	
}

//for 'SREM' instructions
void opcodeProFunction::OPCODE_SREM(instrStateUnit *an_instrStateUnit, globalStateUnit *an_globalStateUnit, string signSubTaData){
	//creat a state unit to store intermidiate variables
	//tempStateUnitTier1 * an_tempStateUnitTier1 = new tempStateUnitTier1();
	//reserve the values into temp_state
	//an_tempStateUnitTier1->mulVal1 = an_instr_info->line1_dynValue;//the first variable for multiplication
	//an_tempStateUnitTier1->mulVal1Reg = an_instr_info->line1_regName;//the register of the first variable
	//an_tempStateUnitTier1->mulVal2 = an_instr_info->line2_dynValue;//the second variable for multiplication
	//an_tempStateUnitTier1->mulVal2Reg = an_instr_info->line2_regName;//the register of the second varibale
	//an_tempStateUnitTier1->mulValr = an_instr_info->liner_dynValue;//the final resutl of the multiplication
	//an_tempStateUnitTier1->mulValrReg = an_instr_info->liner_regName;//the register of the final result
	bool isNot1 = false, isNot2 = false, isNot3 = false;
	int index1 = 0,index2 = 0,index3 = 0;
	int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
	long long deciN1 = an_instr_info->line1_dynValue;
	long long deciN2 = an_instr_info->line2_dynValue;
	long long w = 1;
	long long deciNXor;
	if(an_instrStateUnit->subTarData1.empty()&&an_instrStateUnit->subTarData2.empty()&&an_instrStateUnit->subTarData3.empty()){
		//add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		//add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		//add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
        if (an_instr_info->line1_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line1_regName,"",an_globalStateUnit,&isNot1, &index1);
		}
		if (an_instr_info->line2_regORnot)
		{
			add2TarDataOrNot(an_instr_info->line2_regName,"",an_globalStateUnit,&isNot2, &index2);
		}
		if (an_instr_info->liner_regORnot)
		{
			add2TarDataOrNot(an_instr_info->liner_regName,"",an_globalStateUnit,&isNot3, &index3);
		}
		//000;100;010;001;110;101;011;111
		// for 100
		if ((isNot1==1)&&(isNot2==0)&&(isNot3==0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();
			struct an_intrStUni* eleStates_val = new an_intrStUni();
			struct an_intrStUni* eleStates_ret = new an_intrStUni();
			eleStates->name = an_instr_info->line1_regName;
			eleStates_val->name = an_instr_info->line1_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for (int i = 0; i < bitLen;)
			{
				deciNXor = deciN1^w;
				if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciNXor%deciN2;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 010
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			w = 1;
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
			struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
			eleStates->name = an_instr_info->line2_regName;
			eleStates_val->name = an_instr_info->line2_regName + "_val";
			eleStates_ret->name = an_instr_info->liner_regName;

			for(int i=0;i<bitLen;i++)
			{
				eleStates->tempSts[i] = 0;
				eleStates_val->tempSts[i] = 0;
				eleStates_ret->tempSts[i] = 0;
			}
			for(int i=0;i<bitLen;)
			{
				deciNXor = deciN2^w;
				if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
				}else
				{
					//eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = deciNXor;
					eleStates_ret->tempSts[i] = deciN1%deciNXor;
				}
				if(i < bitLen-1)
					w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
			an_instrStateUnit->subTarData1.push_back(eleStates_val);
			//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			if (an_instr_info->liner_regORnot)
			{
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}else
			{
				eleStates_ret = NULL;
				delete eleStates_ret;
			}
		}
		//for 001
		if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
			eleStates->name = an_instr_info->liner_regName;
			for(int i=0;i<bitLen;)
			{
				eleStates->tempSts[i] = 1;
				fCounter->three_sorts_fm_statement_level[0]++;
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
			an_instrStateUnit->subTarData1.push_back(eleStates);
		}
		//for 110
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret);
				}else
				{
					eleStates_ret = NULL;
					delete eleStates_ret;
				}
			}
			else
			{
				//while faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data

				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor%deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				//an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				}else
				{
					eleStates_ret1 = NULL;
					delete eleStates_ret1;
				}

				//while faults on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1%deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				//an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				}else
				{
					eleStates_ret2 = NULL;
					delete eleStates_ret2;
				}
			}
		}
		//for 101
		if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciNXor%deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the faults on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor%deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 011
		if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates->name = an_instr_info->line2_regName;
				eleStates_val->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 0;
					eleStates_val->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val->tempSts[i] = deciN1%deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
			}
			else
			{
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciN1%deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
		}
		//for 111
		if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
		{
			if((an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)&&(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr))
			{
				w = 1;
				struct an_intrStUni* eleStates = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret = new an_intrStUni();//for the contaminated variable of the target data
				eleStates->name = an_instr_info->line1_regName;
				eleStates_val->name = an_instr_info->line1_regName + "_val";
				eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val->tempSts[i] = 0;
					eleStates_ret->tempSts[i] = 0;
				}
				
				an_instrStateUnit->subTarData1.push_back(eleStates);
				an_instrStateUnit->subTarData1.push_back(eleStates_val);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index2]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo2, yesNo3 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[2]++;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);

				//while the fault on yesNo3
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates2->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates2->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
			}
			else if(an_globalStateUnit->mulStUni[index1]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo1 and yesNo3, and yesNo2 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor%deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1%deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else if(an_globalStateUnit->mulStUni[index2]->corrAddr == an_globalStateUnit->mulStUni[index3]->corrAddr)
			{
				//while the fault on yesNo2 and yesNo3, and yesNo1 is clean
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				//struct an_intrStUni* eleStates_ret = new an_intrStUni();//since there is no contaminated variable besides the target data.
				eleStates1->name = an_instr_info->line2_regName;
				eleStates_val1->name = an_instr_info->line2_regName + "_val";
				//eleStates_ret->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
				}

				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciN1%deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);

				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line1_regName;
				eleStates_val2->name = an_instr_info->line1_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciNXor%deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
			}
			else 
			{
				//while the fault on yesNo1
				w = 1;
				struct an_intrStUni* eleStates1 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val1 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret1 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates1->name = an_instr_info->line1_regName;
				eleStates_val1->name = an_instr_info->line1_regName + "_val";
				eleStates_ret1->name = an_instr_info->liner_regName;

				int bitLen = atoi(an_instr_info->line1_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates1->tempSts[i] = 0;
					eleStates_val1->tempSts[i] = 0;
					eleStates_ret1->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN1^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates1->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val1->tempSts[i] = deciNXor;
						eleStates_ret1->tempSts[i] = deciNXor%deciN2;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData1.push_back(eleStates1);
				an_instrStateUnit->subTarData1.push_back(eleStates_val1);
				an_instrStateUnit->subTarData1.push_back(eleStates_ret1);
				
				//while the fault on yesNo2
				w = 1;
				struct an_intrStUni* eleStates2 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				struct an_intrStUni* eleStates_val2 = new an_intrStUni();//for the fault vaule of the target data on bitwise, while the bitwise-fault is unmasked.
				struct an_intrStUni* eleStates_ret2 = new an_intrStUni();//for the contaminated variable of the target data
				eleStates2->name = an_instr_info->line2_regName;
				eleStates_val2->name = an_instr_info->line2_regName + "_val";
				eleStates_ret2->name = an_instr_info->liner_regName;

				bitLen = atoi(an_instr_info->line2_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;i++)
				{
					eleStates2->tempSts[i] = 0;
					eleStates_val2->tempSts[i] = 0;
					eleStates_ret2->tempSts[i] = 0;
				}
				for(int i=0;i<bitLen;)
				{
					deciNXor = deciN2^w;
					if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
					{
						eleStates2->tempSts[i] = 1;
						fCounter->three_sorts_fm_statement_level[2]++;
					}else
					{
						//eleStates->tempSts[i] = 0;
						eleStates_val2->tempSts[i] = deciNXor;
						eleStates_ret2->tempSts[i] = deciN1%deciNXor;
					}
					if(i < bitLen-1)
						w<<=an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData2.push_back(eleStates2);
				an_instrStateUnit->subTarData2.push_back(eleStates_val2);
				an_instrStateUnit->subTarData2.push_back(eleStates_ret2);
				
				//while the fault on yesNo3
				struct an_intrStUni* eleStates3 = new an_intrStUni();//for the fm (fault masking) states 0, 1 of the target data object.
				eleStates3->name = an_instr_info->liner_regName;
				bitLen = atoi(an_instr_info->liner_sizeOfArgu.c_str());
				for(int i=0;i<bitLen;)
				{
					eleStates3->tempSts[i] = 1;
					fCounter->three_sorts_fm_statement_level[0]++;
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				an_instrStateUnit->subTarData3.push_back(eleStates3);
			}
		}
	}else
	{
		if(signSubTaData == "1")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData1, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData1, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData1, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else
						{
							eleStates->tempSts[i] = deciNXor%deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else
						{
							eleStates->tempSts[i] = deciN1%deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData1.erase(an_instrStateUnit->subTarData1.begin()+index3);
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor1%deciN2;
							}

						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciN1%deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1%deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1%deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData1.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData1.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciN1%deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciN1%deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1%deciN2;
							}
						}else{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData1[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData1[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData1[index1]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1%deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciN1%deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1%deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciN1%deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else{
						//an_instrStateUnit->subTarData1[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1%deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciN1%deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=deciNXor1%deciN2;
						}else
						{
							an_instrStateUnit->subTarData1[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "2")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData2, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData2, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData2, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else
						{
							eleStates->tempSts[i] = deciNXor%deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else
						{
							eleStates->tempSts[i] = deciN1%deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData2.erase(an_instrStateUnit->subTarData2.begin()+index3);
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor1%deciN2;
							}

						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciN1%deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1%deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1%deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData2.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData2.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciN1%deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciN1%deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1%deciN2;
							}
						}else{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData2[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData2[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData2[index1]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1%deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciN1%deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1%deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciN1%deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else{
						//an_instrStateUnit->subTarData2[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1%deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciN1%deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=deciNXor1%deciN2;
						}else
						{
							an_instrStateUnit->subTarData2[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}else if (signSubTaData == "3")
		{
			long long deciNXor1;
			long long deciNXor2;
			int i;
			if (an_instr_info->line1_regORnot)
			{
				isNot1 = isOnInstrStaUnit(an_instr_info->line1_regName, an_instrStateUnit->subTarData3, &index1);
			}
			if (an_instr_info->line2_regORnot)
			{
				isNot2 = isOnInstrStaUnit(an_instr_info->line2_regName, an_instrStateUnit->subTarData3, &index2);
			}
			if (an_instr_info->liner_regORnot)
			{
				isNot3 = isOnInstrStaUnit(an_instr_info->liner_regName, an_instrStateUnit->subTarData3, &index3);
			}
			// 0 0 0
			// 1 0 0
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						if (an_arguConfig->faultMaskRatio>=abs(deciNXor%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else
						{
							eleStates->tempSts[i] = deciNXor%deciN2;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
			}
			// 0 1 0 
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;
				for(i=0;i<bitLen;)
				{
					deciN1 = an_instr_info->line1_dynValue;
					deciNXor = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					deciN2 = an_instr_info->line2_dynValue;
					if(deciNXor!=0)
					{
						if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
						{
							eleStates->tempSts[i] = 0;
							an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}else
						{
							eleStates->tempSts[i] = deciN1%deciNXor;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 0 1
			if((isNot1 == 0)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				an_instrStateUnit->subTarData3.erase(an_instrStateUnit->subTarData3.begin()+index3);
			}
			// 1 1 0
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 0))
			{
				struct an_intrStUni* eleStates = new an_intrStUni();
				eleStates->name = an_instr_info->liner_regName;

				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					// 0 0 -> 0; 1 0, 0 1-> whether the fault on 1 can be masked by 0; 1 1-> 1+1
					if(index1!=index2){
						if ((deciNXor1==0)&&(deciNXor2==0))
						{
							eleStates->tempSts[i] = 0;
						}else if((deciNXor1!=0)&&(deciNXor2==0))//some bits equal to 0, while some are not
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciNXor1%deciN2;
							}

						}else if((deciNXor1==0)&&(deciNXor2!=0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								eleStates->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								eleStates->tempSts[i] = deciN1%deciNXor2;
							}
						}else{
							eleStates->tempSts[i] = deciNXor1%deciNXor2;
						}
					}else{
						eleStates->tempSts[i] = deciNXor1%deciNXor2;
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//an_instrStateUnit->subTarData3.push_back(eleStates);
				if (an_instr_info->liner_regORnot)
				{
					an_instrStateUnit->subTarData3.push_back(eleStates);
				}else
				{
					eleStates = NULL;
					delete eleStates;
				}
			}
			// 0 1 1
			if((isNot1 == 0)&&(isNot2 == 1)&&(isNot3 == 1))
			{

				for(i=0;i<bitLen;)
				{
					//deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index2 == index3)
					{ 
						if(deciNXor2!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciN1%deciNXor2;
							}
						}
					}else{
						if(deciNXor2!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciN1%deciNXor2;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 0 1
			if((isNot1 == 1)&&(isNot2 == 0)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					//deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if(index1 == index3)
					{ 
						if(deciNXor1!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else{
						if(deciNXor1!=0)
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1%deciN2;
							}
						}else{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
			// 1 1 1
			if((isNot1 == 1)&&(isNot2 == 1)&&(isNot3 == 1))
			{
				for(i=0;i<bitLen;)
				{
					deciNXor1 = an_instrStateUnit->subTarData3[index1]->tempSts[i];
					deciNXor2 = an_instrStateUnit->subTarData3[index2]->tempSts[i];
					if((index1 == index2)&&(index2 == index3))
					{
						if(deciNXor1 != 0)
						{
							an_instrStateUnit->subTarData3[index1]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[2]++;
						}
					}else if(index1 == index2)
					{
						if(deciNXor1!=0)
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
						else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}else if(index2 == index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1%deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciN1%deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index1]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else if(index1 ==index3)
					{
						if((deciNXor2 != 0)&&(deciNXor1 != 0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1%deciNXor2;
						}else if((deciNXor2 != 0)&&(deciNXor1 == 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciN1%deciNXor2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index2]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[2]++;
							}else
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciN1%deciNXor2;
							}
						}else if ((deciNXor2 == 0)&&(deciNXor1 != 0))
						{
							if (an_arguConfig->faultMaskRatio>=abs(deciNXor1%deciN2-an_instr_info->liner_dynValue)/an_instr_info->liner_dynValue)
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = 0;
								fCounter->three_sorts_fm_err_propagtion_level[0]++;
							}else
							{
								an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1%deciN2;
							}
						}
					}else{
						//an_instrStateUnit->subTarData3[index3]->tempSts[i] = deciNXor1/deciNXor2;
						if ((deciNXor1!=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1%deciNXor2;
						}else if ((deciNXor1=0)&&(deciNXor2!=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciN1%deciNXor2;
						}else if ((deciNXor1!=0)&&(deciNXor2=0))
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=deciNXor1%deciN2;
						}else
						{
							an_instrStateUnit->subTarData3[index3]->tempSts[i]=0;
							fCounter->three_sorts_fm_err_propagtion_level[0]++;
						}
					}
					i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
			}
		}
	}
}



//Whether adding related registers and names or memory address into the stack of the target data;
//regName is the current variable-name like "fact, a, b, c", addrName is its variable-addr. If there is no addr or no 
//reg information, their value is set to "" and NULL.
//elSize is the variable-size or size of its element, calculate by the function:lengthOftype()
void opcodeProFunction::add2TarDataOrNot(string regName, string addrName,globalStateUnit *an_globalStateUnit, bool *isNot, int *index){
	//double basAddr = an_arguConfig->targetData1_addr;
	//double elSize = lengthOftype(an_arguConfig->targetData1_type);
	//double lasAddr = basAddr + (an_arguConfig->targetData1_size * elSize);
	
	*isNot = false;

	if(addrName != "")
	{
		int i = 0;
		int n = an_globalStateUnit->mulStUni.size();
		for(;i<n;i++){
			if(addrName == an_globalStateUnit->mulStUni[i]->corrAddr)
			{
				*isNot = true;
				*index = i;
				break;
			}else{
				continue;
			}
		}
	}
	else if(regName != "")
	{
		int i = 0;
		int n = an_globalStateUnit->mulStUni.size();
		for (;i<n;i++){
			if (regName == an_globalStateUnit->mulStUni[i]->regName)
			{
				*isNot = true;
				*index = i;
				break;
			}else 
			{
				continue;
			}
		}
	}else{
		*isNot = false;
	}
}


//whether the register of operand is belong to the instruction-state-unit while error propagation analysis
bool opcodeProFunction::isOnInstrStaUnit(string name, vector<an_intrStUni *> subTarData, int* index){
	int size = subTarData.size();
	int i;
	for(i=0;i<size;i++)
	{
		if(name == subTarData[i]->name)
		{
			*index = i;
			if ((*index == 0)&&(subTarData[1]->name!="")) //to fix the problem while shuffle between the regname and regname_val on the first line of subTarData
			{
				(*index)++;
			}
			return 1;
		}else
			continue;
	}
	return 0;
}
//calculate the length of the target data object, according to its category like int, char, float.
//int opcodeProFunction::lengthOftype(string dataType)
//{
//	if(dataType == "int"||"unsigned int"||"signed int"){
//		return sizeof(int);
//	}else if(dataType == "char"||"signed char"||"unsigned char"){
//		return sizeof(char);
//	}else if(dataType == "float"){
//		return sizeof(float);
//	}else if(dataType == "double"||"long double"){
//		return sizeof(double);
//	}else if(dataType == "string"){
//		return sizeof(string);
//	}else if(dataType == "short int"||"signed short int"||"unsigned short int"){
//		return sizeof(short int);
//	}else if(dataType == "long int"||"signed long int"||"long long int"){
//		return sizeof(long int);
//	}else if(dataType == "wchar_t"){
//		return sizeof(wchar_t);
//	}else {printf("EXCEPTION: A NEW TYPE OF TARGET DATA OBJECT IS FOUND!");
//	}
//}

/* 
* double×ª»»Îªstring 
*/
string convertToString(double d) {  
	ostringstream os; 
	long long int d1 = d;//much important!!
	os << d1; 
	return os.str();
}

//N is the input decimal variable, bitLen is the required bit length of its binary transmission
//like 32, 64. bitN is the returned value of String like '010011110101101001101010101010100'
//void deciToBinary(long long int N, int bitLen, string bitN){
//	ostringstream os;
//	int aa[100];
//	for (int i=0; i<bitLen; i++)
//	{
//		aa[i] = 0;
//	}
//	long long int temp;
//	temp = N;
//	int num;
//	int i=0;
//	while(temp !=0)
//	{
//		num = temp%2;
//		aa[i] = num;
//		i++;
//		temp = temp/2;
//	}
//	for(num=bitLen-1;num>=0;num--)
//	{
//		os<<aa[num];
//	}
//	bitN = os.str();
//}

//string in_strs = "111111111111111111111111111111111111111111111111111111111111"
//in_strs is the input binary codes using to converted to decimal number, bitLen is 
//the length of the binary codes, while the number is the converted decimal number.
//void binaryToDeci(string in_strs, int bitLen, long long int number)
//{
//	string buff[64];
//	long long int w = 1;
//	for(int i=0;i<bitLen;i++)
//	{
//		buff[i] = in_strs.substr(i,1);
//	}
//	for(int j=bitLen-1;j>=0;j--)
//	{
//		number += atoi(buff[j].c_str())*w;
//		w*=2;
//	}
//	//cout<<number<<endl;
//}

//bitwise error happening
//vid 
