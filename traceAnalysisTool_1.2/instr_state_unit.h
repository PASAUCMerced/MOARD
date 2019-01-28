#ifndef _INSTR_STATE_UNIT_H_
#define _INSTR_STATE_UNIT_H_
#include <string>
#include <vector>
using namespace std;

struct an_intrStUni
{
	string name;//current variable's name
	double tempSts[64];//temperary state for each bit of current variable
	//Dong's comment: uint64_t tempSts[];
};

class instrStateUnit
{
public:
	vector<an_intrStUni *> subTarData1;
        vector<an_intrStUni *> subTarData2;
	vector<an_intrStUni *> subTarData3;
	instrStateUnit(void);
	virtual ~instrStateUnit(void);
};

#endif
