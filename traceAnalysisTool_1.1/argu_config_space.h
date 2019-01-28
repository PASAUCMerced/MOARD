#ifndef _ARGU_CONFIG_SPACE_H_
#define _ARGU_CONFIG_SPACE_H_
//#define LESS_DETAILS_VERSION
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class arguConfigSpace
{
public:
	string targetData1;
	string targetData1_addr;//the base address
	//int targetData1_size;//the number of elements 
	//string targetData1_type;//the type
	/*string targetData2;
	int targetData2_size;
	string targetData2_addr;*/
	int errPropStepThred;
	double faultMaskRatio;
	int STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
	int NUMBER_OF_BLOCKS_PROCESS_PER_BATCH;
public:
	arguConfigSpace(void);
	virtual ~arguConfigSpace(void);

	//other configuration funtions:
	
};
#endif
