#ifndef _INFOR_FAULT_INJECTION_H_
#define _INFOR_FAULT_INJECTION_H_
#include <string>
#include <vector>

using namespace std;

struct inFaInject{
	string subTarData;
	int elePositId;
	string dynId;
	int opId;
	string lyId;
	string regName;
	bool isFmBitwise;
};

class inforFaultInjection
{
public:
	vector<inFaInject *> inFaInjectVect;
	inforFaultInjection(void);
	virtual ~inforFaultInjection(void);
};
#endif
