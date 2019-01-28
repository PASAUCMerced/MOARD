#include "global_state_unit.h"


globalStateUnit::globalStateUnit(void)
{
}


globalStateUnit::~globalStateUnit(void)
{
	int s;
	s = mulStUni.size();
	for(int i = 0; i<s; i++)
	{
		if (mulStUni[i]!= NULL)
		{
			mulStUni[i] = NULL;
		    delete mulStUni[i];
		}
	}
}
