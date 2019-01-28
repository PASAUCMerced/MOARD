#ifndef _FAULT_MASK_COUNTER_H_
#define _FAULT_MASK_COUNTER_H_
#include <string>
#include <vector>
#include "argu_config_space.h"

using namespace std;

#ifdef LESS_DETAILS_VERSION

#else
struct sglCounter{
	int numOfMaskBits;
	string regnam;
	string dynId;
	int opId;
	double ratio;
};
#endif

class fmCounter
{
public:
#ifndef LESS_DETAILS_VERSION
	vector<sglCounter *> mulCounter;
#else
	double ratio_sum;//the sum of fault masking ratio on the entire space
	double space_sum;//the element space, i.e., the number of operands related to the target data
#endif
	int opcode_count[150][2];
	int opcode_counter_on_td[150];
	int three_sorts_fm_statement_level[3];//the first element is for value overwriting; the second is for the logical operations;
	//the third is for the value shadowing.
	int three_sorts_fm_err_propagtion_level[3];//the first element is for value overwriting; the second is for the logical operations;
	//the third is for the value shadowing.
	int phi_exception_counter;
	int bottom_hit_counter;
	double fm_ratio_sum_statement_tier;
	double fm_ratio_sum_error_prop_tier;
	double fm_ratio_sum_fault_injection_tier;
	fmCounter(void);
	virtual ~fmCounter(void);
};


#endif