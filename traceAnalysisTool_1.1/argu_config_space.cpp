#include "argu_config_space.h"


arguConfigSpace::arguConfigSpace(void)
{
	char* ini_addr = getenv("INI_ADDR_ON_TDD");
	char* err_prop_thred = getenv("ERR_PROP_THRESHOLD");
	char* fm_thred = getenv("FAULT_MASK_THRESHOLD");
	string ini_addr_str(ini_addr);
	string err_prop_thred_str(err_prop_thred);
	string fm_thred_str(fm_thred);
	//the name of the target data object
	targetData1 = "";//The register of .
	//the address or base address of the target data object (i.e., including constants or aggregate structure)
	targetData1_addr = ini_addr_str.c_str();//The base address of *a on CG.
	/*the size of the target data object, whose default value is 1, 
	while it is a single variable. It varies, while it is an aggregate data structure.*/

	//targetData1_size = 1;
	//the type of the target data object
	//targetData1_type = "int";//default type is 'int'
	/*targetData2 = "XXXXXX";
	targetData2_size = 1;
	targetData2_addr = "DFSFSADFSDF";*/
	//The number of error propagation steps while error blasting.
	errPropStepThred = atoi(err_prop_thred_str.c_str());
	//A threshold to determine if a value is significantly big to mask faults.
	faultMaskRatio = atof(fm_thred_str.c_str()); //1%
	STRIDE_LEN_FOR_TRAVERSING_MUL_BITS  = 4;//selecting from 2, 4, 8...
	NUMBER_OF_BLOCKS_PROCESS_PER_BATCH = 50000;//the related lines are 2000*5 = 10000, and process and free 80% each time
}

arguConfigSpace::~arguConfigSpace(void)
{
	//DESTROY THE POINTER'S MEMORY HERE
}
