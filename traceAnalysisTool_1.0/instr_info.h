#ifndef _INSTR_INFO_H_
#define _INSTR_INFO_H_

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class instrInfo
{
    public:

	//line 0 
	string line0_blockId;
	string line0_lineId;
	string line0_funcName;
	string line0_basicBlockId;
	string line0_staticInstId;
	int line0_opcodeId;
	string line0_dynInstId;
	  
	//line 1 
	string line1_arguId;
	string line1_sizeOfArgu;
	double line1_dynValue;
	bool line1_regORnot;
	string line1_regName;
	string line1_pre_block_id;

	//line 2
	string line2_arguId;
	string line2_sizeOfArgu;
	double line2_dynValue;
	bool line2_regORnot;
	string line2_regName;
	string line2_pre_block_id;
	
	//line r
	string liner_arguId;
	string liner_sizeOfArgu;
	double liner_dynValue;
	bool liner_regORnot;
	string liner_regName;
	string liner_pre_block_id;	

	//line 3
	string line3_arguId;
	string line3_sizeOfArgu;
	double line3_dynValue;
	bool line3_regORnot;
	string line3_regName;
	string line3_pre_block_id;

	//line 4
	string line4_arguId;
	string line4_sizeOfArgu;
	double line4_dynValue;
	bool line4_regORnot;
	string line4_regName;
	string line4_pre_block_id;

	//line 5
	string line5_arguId;
	string line5_sizeOfArgu;
	double line5_dynValue;
	bool line5_regORnot;
	string line5_regName;
	string line5_pre_block_id;

	//line 6
	string line6_arguId;
	string line6_sizeOfArgu;
	double line6_dynValue;
	bool line6_regORnot;
	string line6_regName;
	string line6_pre_block_id;

	//line 7
	string line7_arguId;
	string line7_sizeOfArgu;
	double line7_dynValue;
	bool line7_regORnot;
	string line7_regName;
	string line7_pre_block_id;

	//line 8
	string line8_arguId;
	string line8_sizeOfArgu;
	double line8_dynValue;
	bool line8_regORnot;
	string line8_regName;
	string line8_pre_block_id;

	//line 9
	string line9_arguId;
	string line9_sizeOfArgu;
	double line9_dynValue;
	bool line9_regORnot;
	string line9_regName;
	string line9_pre_block_id;

	//create some methods if necessory
	instrInfo();
	~instrInfo();

	void printLine1();
}; 

#endif
