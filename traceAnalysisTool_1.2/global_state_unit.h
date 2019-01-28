#ifndef _GLOBAL_STATE_UNIT_H_
#define _GLOBAL_STATE_UNIT_H_
#include <string>
#include <vector>
#include "argu_config_space.h"

using namespace std;

struct sglStUni{
	string regName;
	//long long int corrValue;
	string corrAddr;
};

class globalStateUnit
{
public:
	vector<sglStUni *> mulStUni;
	globalStateUnit(void);
	virtual ~globalStateUnit(void);
};

#endif
