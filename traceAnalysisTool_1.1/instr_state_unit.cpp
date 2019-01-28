#include "instr_state_unit.h"


instrStateUnit::instrStateUnit(void)
{
}

instrStateUnit::~instrStateUnit(void)
{
	//Not sure whether releasing space here is correct.
	int j = subTarData1.size();
	for (int i=0;i<j;i++){
		if (subTarData1[i]!=NULL)
		{
			subTarData1[i] = NULL;
			delete subTarData1[i];
		}
	}
	j = subTarData2.size();
	for (int i=0;i<j;i++){
		if (subTarData2[i]!=NULL)
		{
			subTarData2[i] = NULL;
			delete subTarData2[i];
		}
	}
	j = subTarData3.size();
	for (int i=0;i<j;i++){
		if (subTarData3[i]!=NULL)
		{
			subTarData3[i] = NULL;
			delete subTarData3[i];
		}
	}
}
