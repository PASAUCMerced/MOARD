//#include "stdafx.h"
#include "fault_mask_counter.h"

fmCounter::fmCounter(void)
{
#ifdef LESS_DETAILS_VERSION
	space_sum = 0;
	ratio_sum = 0;
#endif
	for (int i = 0; i < 150; i++)
		for (int j = 0; j < 2; j++)
		{
			opcode_count[i][j] = 0;
		}
		phi_exception_counter = 0;
		bottom_hit_counter = 0;
		fm_ratio_sum_statement_tier = 0;
		fm_ratio_sum_error_prop_tier = 0;
		fm_ratio_sum_fault_injection_tier = 0;
		for (int i = 0; i < 150; i++)
		{
			opcode_counter_on_td[i] = 0;
		}
		for (int j = 0; j < 3; j++)
		{
			three_sorts_fm_statement_level[j] = 0;
			three_sorts_fm_err_propagtion_level[j] = 0;
		}
}

fmCounter::~fmCounter(void)
{
#ifndef LESS_DETAILS_VERSION
	int s = mulCounter.size();
	for(int i=0;i<s;i++)
	{
		if (mulCounter[i]!=NULL)
		{
			mulCounter[i] = NULL;
			delete mulCounter[i];
		}	
	}
#endif
}

