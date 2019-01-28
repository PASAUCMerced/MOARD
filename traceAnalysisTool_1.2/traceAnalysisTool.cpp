// traceAnalysisTool.cpp 
//
//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "stdio.h"
#include <sstream>
#include <stdlib.h>
#include<time.h>

#include "instr_info.h"
#include "opcode_pro_function.h"
#include "infor_fault_injection.h"
#include "argu_config_space.h"
#include "global_state_unit.h"
#include "instr_state_unit.h"

using namespace std;

void analysis_on_operand(instrStateUnit *an_instrStateUnit, vector<an_intrStUni *> subTarData, vector<instrInfo*> app_trace, int sum, int sz, string sign, int k, string signSubTaData, int opcodeId, arguConfigSpace *an_arguConfig, globalStateUnit *an_globalStateUnit, fmCounter *fmc, ifstream &isfile, ofstream &isfile1, ifstream &tracefile);    
void refresh_the_fm_state(instrStateUnit *an_instrStateUnit);

//Refresh the fault masking states 0 -> 1, if all contaminated variables are masked.
void refresh_the_fm_state(instrStateUnit *an_instrStateUnit, int sz1)
{
	int foo = 0;
	if (!an_instrStateUnit->subTarData1.empty())
	{
		int s = an_instrStateUnit->subTarData1.size();	
		for (int j = 0; j < sz1; j++)
		{
			foo = 0;
			for (int i = 0; i < s; i++)
			{
				foo+=an_instrStateUnit->subTarData1[i]->tempSts[j];
			}
			if (foo == 0)
			{
				an_instrStateUnit->subTarData1[0]->tempSts[j] = 1;
			}
		}
	}
	if (!an_instrStateUnit->subTarData2.empty())
	{
		int s = an_instrStateUnit->subTarData2.size();
		for (int j = 0; j < sz1; j++)
		{
			foo = 0;
			for (int i = 0; i < s; i++)
			{
				foo+=an_instrStateUnit->subTarData2[i]->tempSts[j];
			}
			if (foo == 0)
			{
				an_instrStateUnit->subTarData2[0]->tempSts[j] = 1;
			}
		}
	}
	if (!an_instrStateUnit->subTarData3.empty())
	{
		int s = an_instrStateUnit->subTarData3.size();
		for (int j = 0; j < sz1; j++)
		{
			foo = 0;
			for (int i = 0; i < s; i++)
			{
				foo+=an_instrStateUnit->subTarData3[i]->tempSts[j];
			}
			if (foo == 0)
			{
				an_instrStateUnit->subTarData3[0]->tempSts[j] = 1;
			}
		}
	}
}

void analysis_on_operand(instrStateUnit *an_instrStateUnit, vector<an_intrStUni *> subTarData, vector<instrInfo*> app_trace, int sum, int sz, string sign, int k, string signSubTaData, int opcodeId, arguConfigSpace *an_arguConfig, globalStateUnit *an_globalStateUnit, fmCounter *fmc, ifstream &isfile, ofstream &isfile1, ifstream &tracefile)
{
	sum = 0;
	int i;

	refresh_the_fm_state(an_instrStateUnit, sz);//bitwise starts refreshing
	for(i=0;i<sz;)
	{
		sum += subTarData[0]->tempSts[i];
		i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
	}
	/*fmcVector.push_back(fCounterList);*/
	//stringstream sss;
#ifdef LESS_DETAILS_VERSION
	double tmp_ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
#else
	struct sglCounter *tp = new sglCounter();
	tp->dynId = app_trace[k]->line0_dynInstId;
	tp->numOfMaskBits = sum;
	//sss << app_trace[k]->line0_opcodeId;
	//sss >> tp->opId;
	tp->opId = app_trace[k]->line0_opcodeId;
	tp->ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
	tp->regnam = subTarData[0]->name;
#endif

	//fm_ratio_sum_statement_tier counter
#ifdef LESS_DETAILS_VERSION
	fmc->fm_ratio_sum_statement_tier = fmc->fm_ratio_sum_statement_tier + tmp_ratio;
#else
	fmc->fm_ratio_sum_statement_tier = fmc->fm_ratio_sum_statement_tier + tp->ratio;
#endif

	//error propagation started
	struct inFaInject an_inFaInject;
	int size = app_trace.size()-1;
	int nOfSteps = 1;
#ifdef LESS_DETAILS_VERSION
	if((tmp_ratio < 1)&&(!tracefile.eof()))  //Dong's comment: ratio > 1 is illegal;
#else
	if((tp->ratio <1)&&(!tracefile.eof()))
#endif
	{
		//fmc->error_prop_times++;
		sign = "err";
		do{
			opcodeId = app_trace[k+nOfSteps]->line0_opcodeId;
			if (opcodeId < 0)
			{
				printf("Exception: disaster found %d!", k+nOfSteps);
			}
			opcodeProFunction* an_opcodeProFunction = new opcodeProFunction(opcodeId, app_trace[k+nOfSteps],fmc,an_arguConfig);
			an_opcodeProFunction->opcodeProcess(an_instrStateUnit, an_globalStateUnit,sign,signSubTaData,fmc);//problems
			refresh_the_fm_state(an_instrStateUnit, sz);//bitwise states refreshing
			switch(atoi(signSubTaData.c_str())){
			case 1:
				subTarData = an_instrStateUnit->subTarData1;
				break;
			case 2:
				subTarData = an_instrStateUnit->subTarData2;
				break;
			case 3:
				subTarData = an_instrStateUnit->subTarData3;
				break;
			}
			sum = 0;
			for(i=0;i<sz;)
			{
				sum += subTarData[0]->tempSts[i];
				i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
			}
#ifndef LESS_DETAILS_VERSION
			tp->numOfMaskBits = sum;
			tp->ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
#else
			tmp_ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
#endif	
			nOfSteps++;
			if ((k+nOfSteps)>=size)
			{
				fmc->bottom_hit_counter++;
				cout<<"EXCEPTION: the error propagation tracing hits the boundary of the file!"<<endl;
				break;
			}
		}
#ifdef LESS_DETAILS_VERSION
		while((nOfSteps < an_arguConfig->errPropStepThred)&&(tmp_ratio < 1));
#else 
		while((nOfSteps < an_arguConfig->errPropStepThred)&&(tp->ratio < 1));
#endif
	}
	sum = 0;
	refresh_the_fm_state(an_instrStateUnit, sz);//bitwise starts refreshing
	for(i=0;i<sz;)
	{
		sum += subTarData[0]->tempSts[i];
		i = i+an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
	}
#ifndef LESS_DETAILS_VERSION
		tp->numOfMaskBits = sum;
		tp->ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
#else
		tmp_ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
#endif

//fm_ratio_sum_error_prop_tier counter
#ifdef LESS_DETAILS_VERSION
	fmc->fm_ratio_sum_error_prop_tier = fmc->fm_ratio_sum_error_prop_tier + tmp_ratio;
#else
	fmc->fm_ratio_sum_error_prop_tier = fmc->fm_ratio_sum_error_prop_tier + tp->ratio;
#endif

	//If we reach the error propagation threshold and cannot make a decision on fault masking, 
	//we output the instr info for fault injection
#ifdef LESS_DETAILS_VERSION
	if((tmp_ratio < 1)&&(!tracefile.eof()))  //Dong's comment: ratio > 1 is illegal;
#else
	if((tp->ratio < 1)&&(!tracefile.eof()))
#endif
		{
			if (isfile.is_open()){
				//read the fault injection result and refresh the value of fault masking ratio
				//isfile.open();
				string ly;
				while(!isfile.eof())
				{
					getline( isfile, ly );
					istringstream ss(ly);
					ss>>an_inFaInject.subTarData >>an_inFaInject.elePositId >>an_inFaInject.dynId >>an_inFaInject.lyId>>an_inFaInject.opId >>an_inFaInject.isFmBitwise >>an_inFaInject.regName;
					if((an_inFaInject.subTarData == signSubTaData)&&(an_inFaInject.dynId == app_trace[k]->line0_dynInstId)&&(an_inFaInject.lyId == app_trace[k]->line0_lineId))
					{
						if((an_inFaInject.opId == app_trace[k]->line0_opcodeId)||(an_inFaInject.regName == subTarData[0]->name)) 
                                                //Anzheng's note: loosen the condition, as some register names are not correct by some reason.
						{
							subTarData[0]->tempSts[an_inFaInject.elePositId] = an_inFaInject.isFmBitwise;
						}
					}
				}
   				isfile.clear();
				isfile.seekg(0, isfile.beg);
			}else
			{
				int length = an_globalStateUnit->mulStUni.size();
				for (int y = 0; y < sz;)
				{
					if (subTarData[0]->tempSts[y] == 0)
					{
						isfile1<<signSubTaData<<" "<<y<<" "<<app_trace[k]->line0_dynInstId<<" " << app_trace[k]->line0_lineId <<" "<<app_trace[k]->line0_opcodeId<<" "<<"0"<<" "<<subTarData[0]->name;
						//printing all the registers sharing the same memory address with the "tp->regnam" into the fault_injection file.
						for (int i = 0; i < length; i++)
						{
							bool b1 = (an_globalStateUnit->mulStUni[i]->regName == subTarData[0]->name);
							if (b1)
							{
								string corr_Addr = an_globalStateUnit->mulStUni[i]->corrAddr;
								for (int j = 0; j < length; j++)
								{
									bool b2 = (corr_Addr == an_globalStateUnit->mulStUni[j]->corrAddr);
									if (b2)
									{
										if (j!=i)
										{
											isfile1<<an_globalStateUnit->mulStUni[j]->regName;
										}
									}
								}
							}
						}
                    			isfile1<<endl;
					}
					y = y + an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
				}
				//isfile1<<endl;
			}
			//fmc->fault_injection_file_rw_times++;
		}
		sum = 0;
		for(i=0;i<sz;)
		{
			sum += subTarData[0]->tempSts[i];
			i = i + an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS;
		}
#ifndef LESS_DETAILS_VERSION
		tp->numOfMaskBits = sum;
		tp->ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
#else
		tmp_ratio = (double)sum/((double)sz/(double)an_arguConfig->STRIDE_LEN_FOR_TRAVERSING_MUL_BITS);
#endif


//fm_ratio_sum_fault_injection_tier counter
#ifdef LESS_DETAILS_VERSION
	fmc->fm_ratio_sum_fault_injection_tier = fmc->fm_ratio_sum_fault_injection_tier + tmp_ratio;
#else
	fmc->fm_ratio_sum_fault_injection_tier = fmc->fm_ratio_sum_fault_injection_tier + tp->ratio;
#endif

#ifndef LESS_DETAILS_VERSION
	fmc->mulCounter.push_back(tp);
#else
	fmc->space_sum++;
	fmc->ratio_sum += tmp_ratio;
#endif
}

int main()
{
	clock_t start,finish;
	double totaltime1, totaltime2, totaltime3;
	start=clock();	
	/*create an fault masking counter vector to reserve the fault masking
	ratio on each instruction, and then calculate the averange value*/
	fmCounter *fmc = new fmCounter();

	//create an object of argu_config
	arguConfigSpace *an_arguConfig = new arguConfigSpace();

	//Global states storage units
	/* the global vector to store the registers and memory addresses 
	related to the target data object*/
	globalStateUnit *an_globalStateUnit = new globalStateUnit();
	// Get the reserved global-state-unit back 
	ifstream infile("../midd_file/globalStateUnit");
	if (infile.is_open())
	{
		ifstream infile("../midd_file/globalStateUnit",ifstream::in);
		string inf;
		while(!infile.eof())
		{
			struct sglStUni *temp = new sglStUni();
			getline(infile, inf);
			istringstream ss(inf);
			ss >> (*temp).corrAddr >> (*temp).regName;
			if ((temp->corrAddr!="")||(temp->regName!=""))
			{
				an_globalStateUnit->mulStUni.push_back(temp);
			}
		}
		infile.close();

		struct sglStUni *temp = new sglStUni();
		(*temp).regName = an_arguConfig->targetData1;
		(*temp).corrAddr = an_arguConfig->targetData1_addr;
		an_globalStateUnit->mulStUni.push_back(temp);

	}else
	{
		struct sglStUni *temp = new sglStUni();
		(*temp).regName = an_arguConfig->targetData1;
		(*temp).corrAddr = an_arguConfig->targetData1_addr;
		an_globalStateUnit->mulStUni.push_back(temp);
	}

	//vector<string> targetData1Relat;//the related data
	//vector<string> targetAddr1Relat;//the related addr
	//targetData1Relat.push_back(an_arguConfig->targetData1);//intialization
	//targetAddr1Relat.push_back(an_arguConfig->targetData1_addr);//initialization
	
	//Get the index of tracefile form the environment varialbe
	char* serial_num = getenv("SERIAL_NUM");
	string suffix(serial_num);
    string fiDir(getenv("FAULT_INJECTION_RESULT_DIR"));
	//open the fault injection and fault injection result file
	//ifstream isfile;
	ofstream isfile1;
	string file_name1 = fiDir+"fault_injection_"+suffix;
        ifstream isfile(file_name1.c_str());//Anzheng's comment: add index here
	if (!isfile.is_open())
	{
      		string file_name2 = "../midd_file/fault_injection_"+suffix;
        	isfile1.open(file_name2.c_str(),ofstream::out);//Anzheng's comment: add index here
	}
	//ofstream isfile1;
	//string file_name2 = "../midd_file/fault_injection_"+suffix;
	//isfile1.open(file_name2.c_str(),ofstream::out);//Anzheng's comment: add index here

	//temperary information for fault injection using
	//inforFaultInjection *an_inforFaultInjection =  new inforFaultInjection();

	/*Open the trace file*/
	ifstream in; //creat an object for ifstream
	string filename_tmp = "../tracefile/dynamic_trace";
	//for over-large size files, we separated them into multiple files, and analyzed one by one.
	//string filename_tmp = "../tracefile/sub_trace_"+suffix;	//Anzheng's comment; add index here
	/*for (char i = 97; i < 123; i++)
	{
	for (char j = 97; j < 123; j++)
	{
	stringstream s1s, s2s;
	filename_tmp = "dynamic_trace_";
	string ii, jj;
	s1s<<(char)i;
	s1s>>ii;
	s2s<<(char)j;
	s2s>>jj;
	filename_tmp = filename_tmp+ii+jj;
	}
	}*/
	//const char *filename = filename_tmp.c_str();
	in.open(filename_tmp.c_str(), ifstream::in); //open the tracefile
	/*Creation of the trace*/
	vector<instrInfo*>  app_trace;
	if(!in)
	{
		cout<<"ERROR IN OPENNING THE TRACEFILE!"<<endl;
		return 1;
	}

	/*Read the trace*/
	string line;
	int i=0;
	int j=0;
	int n=0;
        //int n0 = 0;
	int len;
	//create an instr record 
	//instrInfo* an_instr_info = new instrInfo();//(instrInfo *)malloc(sizeof(instrInfo));//

	printf("Begin reading the instruction trace...\n");
	while(true)
	{
		//read some info from the trace file
		getline(in, line);
		size_t yes_no, NumOfComma1, NumOfComma2;
		yes_no = line.find(",",0);
		if (yes_no == string::npos)
		{
			if(i>0)
			{
				/*j = app_trace.size();
				for (int k=0;k<j;k++)
				{
				cout<<app_trace[k].line0_blockId<<" "<<app_trace[k].line0_lineId<<" "<<app_trace[k].line0_funcName<<" "<<
				app_trace[k].line0_basicBlockId<<" "<<app_trace[k].line0_staticInstId<<" "<<app_trace[k].line0_opcodeId<<" "<<
				app_trace[k].line0_dynInstId<<endl;
				}*/
				++n;
			}
			if ((n>=an_arguConfig->NUMBER_OF_BLOCKS_PROCESS_PER_BATCH)||in.eof())
			{
                int k;
				//Stopping read of the trace, and starting trace analysis
				/*Trace analysis*/
				len = app_trace.size();
				for(k=0;k<len;k++)
				{
					//instruction level states storage units
					instrStateUnit *an_instrStateUnit = new instrStateUnit();

					//create a object of faultMaskCounter each iteration for each block

					//read the trace into the opcodeProFunction to process and extract information 
					int opcodeId = app_trace[k]->line0_opcodeId;
					if (opcodeId < 0)
					{
						printf("Exception: disaster found %d!", atoi(app_trace[k]->line0_dynInstId.c_str()));
					}
					opcodeProFunction* an_opcodeProFunction = new opcodeProFunction(opcodeId, app_trace[k], fmc, an_arguConfig);

					//initializing a sign to judge whether it is in the step while error propagation or not
					string sign = "ini";//initialization state
					string signSubTaData;//for error propagation to decide which subtardata to take the error propagation

					an_opcodeProFunction->opcodeProcess(an_instrStateUnit, an_globalStateUnit,sign, signSubTaData,fmc);

					//Calculate the fault masking ratio, to decide the error propagation
					int sz1 = atoi(app_trace[k]->line1_sizeOfArgu.c_str());
					int sum = 0;
					//To process the operands
					//Dong's comment: TODO
					if(!an_instrStateUnit->subTarData1.empty())
					{
						signSubTaData = "1";
						analysis_on_operand(an_instrStateUnit, an_instrStateUnit->subTarData1, app_trace, sum, sz1, sign, k, signSubTaData, opcodeId, an_arguConfig, an_globalStateUnit, fmc, isfile, isfile1, in);
					}
					if(!an_instrStateUnit->subTarData2.empty())
					{
						signSubTaData = "2";
						analysis_on_operand(an_instrStateUnit, an_instrStateUnit->subTarData2, app_trace, sum, sz1, sign, k, signSubTaData, opcodeId, an_arguConfig, an_globalStateUnit, fmc, isfile, isfile1, in);
					}
					if(!an_instrStateUnit->subTarData3.empty())
					{
						signSubTaData = "3";
						analysis_on_operand(an_instrStateUnit, an_instrStateUnit->subTarData3, app_trace, sum, sz1, sign, k, signSubTaData, opcodeId, an_arguConfig, an_globalStateUnit, fmc, isfile, isfile1, in);
					}

					//print out the execution states
					if(atoi(app_trace[k]->line0_dynInstId.c_str())%500 == 0)
						printf("The traceAnalysisTool has completed the %d instructions...\n", atoi(app_trace[k]->line0_dynInstId.c_str()));
                    
                    			if (atoi(app_trace[k]->line0_dynInstId.c_str())  > 77957627)
						printf("The traceAnalysisTool has completed the %d instructions...\n", atoi(app_trace[k]->line0_dynInstId.c_str()));

					if (app_trace[k]->line0_opcodeId == 0)
					{
						printf("The traceAnalysisTool has completed the %d instructions...\n", atoi(app_trace[k]->line0_dynInstId.c_str()));
					}
					//free the memory space
					an_instrStateUnit->~instrStateUnit();
					if (an_instrStateUnit!=NULL)
					{
						an_instrStateUnit = NULL;
						delete an_instrStateUnit;
					}
					an_opcodeProFunction->~opcodeProFunction();
					if (an_opcodeProFunction!=NULL)
					{
						an_opcodeProFunction = NULL;
						delete an_opcodeProFunction;
					}
					if (k>=0.8*an_arguConfig->NUMBER_OF_BLOCKS_PROCESS_PER_BATCH)
					{
						app_trace.erase(app_trace.begin(), (app_trace.begin()+k));
						n = app_trace.size();
						instrInfo* an_instr_info = new instrInfo();
						app_trace.push_back(an_instr_info);
						break;
					}
				}
				//Jump out of the loop while hitting the bottom of the file
				if (in.eof())
				{
			                int n0 = app_trace.size();
					if (k >= n0-1)
					{
						break;
					}
				}

				//While 80% trace finished its analysis, stopping the analysis, and starting free the completed trace 
			}else
			{
				i = 0;
				instrInfo* an_instr_info = new instrInfo();
				app_trace.push_back(an_instr_info);
				continue;
			}

		}
		else
		{
			//NumOfComma1 = 1;

			//NumOfComma2 = line.find(",", NumOfComma1 + 1);
			//signed int lineId_abnom = atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());
			//if(lineId_abnom >= 0) // delete the "-1" traces
			{
				NumOfComma1 = 0;
				NumOfComma2 = line.find(",", NumOfComma1);
				string blockId_abnom = line.substr(NumOfComma1, NumOfComma2).c_str();
				// assign to line-0/1/2/r
				if(blockId_abnom == "0") // assign to line 0
				{
					app_trace[n]->line0_blockId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line0_lineId = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line0_funcName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line0_basicBlockId = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line0_staticInstId = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line0_opcodeId = atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line0_dynInstId = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}
				else if(blockId_abnom == "1") //assign to line 1
				{
					app_trace[n]->line1_arguId = line.substr(NumOfComma1, NumOfComma2).c_str();

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line1_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line1_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line1_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line1_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line1_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}
				else if(blockId_abnom == "2") //assign to line 2
				{
					app_trace[n]->line2_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line2_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line2_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line2_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line2_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line2_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}
				else if(blockId_abnom == "r") //assign to line 3/r
				{
					app_trace[n]->liner_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->liner_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->liner_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->liner_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->liner_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->liner_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}
				else if(blockId_abnom == "3") //assign to line 3
				{
					app_trace[n]->line3_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line3_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line3_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line3_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line3_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line3_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}else if(blockId_abnom == "4")
				{
					app_trace[n]->line4_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line4_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line4_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line4_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line4_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line4_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}else if (blockId_abnom == "5")
				{
					app_trace[n]->line5_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line5_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line5_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line5_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line5_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line5_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}else if (blockId_abnom == "6")
				{
					app_trace[n]->line6_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line6_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line6_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line6_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line6_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line6_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}else if (blockId_abnom == "7")
				{
					app_trace[n]->line7_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line7_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line7_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line7_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line7_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line7_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}else if (blockId_abnom == "8")
				{
					app_trace[n]->line8_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line8_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line8_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line8_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line8_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line8_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}else if (blockId_abnom == "9")
				{
					app_trace[n]->line9_arguId = line.substr(NumOfComma1, NumOfComma2);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line9_sizeOfArgu = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line9_dynValue = atof(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str());					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line9_regORnot = (atoi(line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1).c_str()) ==1);					

					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line9_regName = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					// for '-1' trace blocks, there is a predecesser block id here; for other blocks, here is empty
					NumOfComma1 = NumOfComma2;
					NumOfComma2 = line.find(",", NumOfComma1 + 1);
					app_trace[n]->line9_pre_block_id = line.substr(NumOfComma1+1, NumOfComma2-NumOfComma1-1);

					i++;
					continue;
				}
			}
			/*
			else // while "-1" blocks
			{
			//continue;
			do{
			//continue;
			getline(in, line);
			yes_no = line.find(",",0);

			}while(yes_no != string::npos);
			}
			*/
		}
		
	}
	/*if ((app_trace[n]->line0_staticInstId == "")&&(app_trace[n]->line0_dynInstId == ""))
	{
		app_trace.erase(app_trace.begin()+n);
	}*/
	in.close();
	/*intermidiate states for tier-1 analysis are stored in a temp vector
	with each element presented by tempStateUnit class. We only store the 
	states of instructions that there is possibility of fault masking*/
	//vector<tempStateUnitTier1 *> statVector;
	//printf("Finish reading the instruction trace...\n");

	/*Trace analysis*/
	//j = app_trace.size();
	//for(int k=0;k<j;k++)
	isfile.close();
	isfile1.close();
	printf("The traceAnalysisTool has almost finished the trace analysis...\n\n");
	finish = clock();
	totaltime1 = (double)(finish - start)/CLOCKS_PER_SEC;
	cout<<"The running time of the program is (s):"<<totaltime1<<endl;
	totaltime2 = totaltime1/60;
	cout<<"The running time of the program is (min):"<<totaltime2<<endl;
	totaltime3 = totaltime2/60;
	cout<<"The running time of the program is (h):"<<totaltime3<<endl;
	//calculate the DVF value of the target data
	double aDVF = 0;
#ifndef LESS_DETAILS_VERSION
	double ratio_sum = 0;
	int s = fmc->mulCounter.size();
	for (i = 0; i < s; i++)
	{
		ratio_sum += fmc->mulCounter[i]->ratio;
	}
	aDVF = ratio_sum/(double)s;
#else
	aDVF = fmc->ratio_sum/fmc->space_sum;
#endif
	cout<<"The DVF value of the target data is: "<< aDVF <<endl;

	//Output detailed fault-masking info into a file
#ifndef LESS_DETAILS_VERSION
	ofstream filean;
	string file_name3 = "../analysis_result/detailed_fm_events_info_" +suffix;
	filean.open(file_name3.c_str(), ofstream::out);
	filean << "target_operand_id; " << "corr_dyn_instr_id; " << "corr_reg_name; " << "corr_opcode_id; " << "fm_ratio_on_it" <<endl;
	for (i = 0; i < s; i++)
	{
		filean << (i+1) <<" "<< fmc->mulCounter[i]->dynId <<" "<<fmc->mulCounter[i]->regnam<<" "<<fmc->mulCounter[i]->opId<<" "<<fmc->mulCounter[i]->ratio<<endl;
		fmc->opcode_counter_on_td[fmc->mulCounter[i]->opId]++;
	}
	filean.close();
#endif
	//print out the DVF values and the counters into a temp file
	ofstream anfile;
	string file_name4 = "../analysis_result/dvf_counters_" +suffix;
	anfile.open(file_name4.c_str(), ofstream::out); //Anzheng's comment: add index here
#ifdef LESS_DETAILS_VERSION
	anfile<<"dvf_sum:"<<" "<< fmc->ratio_sum <<" "<<"dvf_num:"<<" "<< fmc->space_sum <<" "<<"dvf_ratio:"<<" "<< aDVF <<endl;
#else
	anfile<<"dvf_sum:"<<" "<< ratio_sum <<" "<<"dvf_num:"<<" "<< s <<" "<<"dvf_ratio:"<<" "<< aDVF <<endl;
#endif
	for (int i = 0; i < 150; i++)
		//for (int j = 0; j < 2; j++)
		//{
		if (fmc->opcode_count[i][0]!=0)
		{
			if (fmc->opcode_count[i][1] == 1)
			{
				anfile<<"num_of_opcode("<<i<<"):"<<fmc->opcode_count[i][0]<<" "<<"is_processed:"<<"yes"<<endl;
			}else
			{
				anfile<<"num_of_opcode("<<i<<"):"<<fmc->opcode_count[i][0]<<" "<<"is_processed:"<<"no"<<endl;
			}
		}
		//}
#ifndef LESS_DETAILS_VERSION
		anfile<<"num_of_operands_relate_to_target_data:"<< s <<endl;
#else
		anfile<<"num_of_operands_relate_to_target_data:"<< fmc->space_sum <<endl;
#endif
		anfile<<"fm_ratio_sum_on_statement_tier:"<< fmc->fm_ratio_sum_statement_tier<<endl;
		anfile<<"fm_ratio_sum_on_error_prop_tier:"<< fmc->fm_ratio_sum_error_prop_tier<<endl;
		anfile<<"fm_ratio_sum_on_fault_injection_tier:"<<fmc->fm_ratio_sum_fault_injection_tier<<endl;
		anfile<<"num_of_phi_exception:"<<fmc->phi_exception_counter<<endl;
		anfile<<"num_of_bottom_hit:"<<fmc->bottom_hit_counter<<endl;
		anfile<<endl;
		anfile<<"opcode distribution on fault masking of target data:"<<endl;
		for (int i = 0; i < 150; i++)
		{
			if (fmc->opcode_counter_on_td[i]!=0)
			{
				anfile<<"num_of_opcode("<<i<<"):"<<fmc->opcode_counter_on_td[i]<<endl;
			}
		}
		anfile<<endl;
		anfile<<"Number of the three fault masking types on statement level:"<<endl;
		anfile<<"sl_num_of_value_overwriting_times:"<<fmc->three_sorts_fm_statement_level[0]<<endl;
		anfile<<"sl_num_of_logic_operation_times:"<<fmc->three_sorts_fm_statement_level[1]<<endl;
		anfile<<"sl_num_of_value_overshadowing_times:"<<fmc->three_sorts_fm_statement_level[2]<<endl; 
		anfile<<endl;
		anfile<<"Number of the three fault masking types on error prop level:"<<endl;
		anfile<<"ep_num_of_value_overwriting_times:"<<fmc->three_sorts_fm_err_propagtion_level[0]<<endl;
		anfile<<"ep_num_of_logic_operation_times:"<<fmc->three_sorts_fm_err_propagtion_level[1]<<endl;
		anfile<<"ep_num_of_value_overshadowing_times:"<<fmc->three_sorts_fm_err_propagtion_level[2]<<endl;
		anfile<<endl;
		anfile<<"The running time of the program is (s):"<<totaltime1<<endl;
	    	anfile<<"The running time of the program is (min):"<<totaltime2<<endl;
    		anfile<<"The running time of the program is (h):"<<totaltime3<<endl;

		anfile.close();

		//RELEASE ARGUCONFIG
		if (an_arguConfig!=NULL)
		{
			an_arguConfig = NULL;	
			delete an_arguConfig;
		}
		fmc->~fmCounter();
		if (fmc!=NULL)
		{
			fmc = NULL;
			delete fmc;
		}

		// Output the global-state-unit into a temp file for next round using.
		int size1 = an_globalStateUnit->mulStUni.size();
		ofstream file ("../midd_file/globalStateUnit", ofstream::out);
		for (int i = 0; i < size1; i++)
		{
			file << an_globalStateUnit->mulStUni[i]->corrAddr <<" "<< an_globalStateUnit->mulStUni[i]->regName<<endl;
		}
		file.close();

		an_globalStateUnit->~globalStateUnit();
		if (an_globalStateUnit!=NULL)
		{
			an_globalStateUnit = NULL;
			delete an_globalStateUnit;
		}

		// DESTROY THE MEMORY

		j = app_trace.size();
		for (int k=0;k<j;k++)
		{
			if (app_trace[k]!=NULL)
			{
				app_trace[k] = NULL;
				delete app_trace[k];
			}

		}
		return 0;
}

//deteted codes from line 331
//#if 0
//			for(i=0;i<sz1;i++)
//			{
//				sum += an_instrStateUnit->subTarData1[0]->tempSts[i];
//			}
//			/*fmcVector.push_back(fCounterList);*/
//			struct sglCounter *tp1 = new sglCounter();
//			tp1->dynId = app_trace[k]->line0_dynInstId;
//			tp1->numOfMaskBits = sum;
//			tp1->opId = app_trace[k]->line0_opcodeId;
//			tp1->ratio = sum/sz1;
//			tp1->regnam = an_instrStateUnit->subTarData1[0]->name;
//
//			//error propagation started
//			struct inFaInject an_inFaInject;
//
//			int nOfSteps = 1;
//			if(tp1->ratio < 1)  //Dong's comment: ratio > 1 is illegal;
//			{
//				sign = "err";
//				signSubTaData = 1;
//				do{
//					opcodeId = app_trace[k+nOfSteps]->line0_opcodeId;
//					opcodeProFunction* an_opcodeProFunction = new opcodeProFunction(opcodeId, app_trace[k+nOfSteps]);
//					an_opcodeProFunction->opcodeProcess(an_instrStateUnit, an_globalStateUnit,sign,signSubTaData);//problems
//					sum = 0;
//					for(i=0;i<sz1;i++)
//					{
//						sum += an_instrStateUnit->subTarData1[0]->tempSts[i];
//					}
//					tp1->numOfMaskBits = sum;
//					tp1->ratio = sum/sz1;
//					nOfSteps++;
//				}while((nOfSteps < an_arguConfig->errPropStepThred)||(tp1->ratio < 1));
//
//				//If we reach the error propagation threshold and cannot make a decision on fault masking, 
//				//we output the instr info for fault injection
//				if (tp1->ratio < 1) //Dong's comment: ratio > 1 is illegal;
//				{
//					ifstream isfile("fault_injection_rel");
//					if (isfile.is_open()) {
//						isfile.open("fault_injection_rel");
//						//read the fault injection result and refresh the value of fault masking ratio
//						string ly;
//						while(!isfile.eof())
//						{
//							getline( isfile, ly );
//							istringstream ss(ly);
//							ss>>an_inFaInject.subTarData >>an_inFaInject.elePositId >>an_inFaInject.dynId >>an_inFaInject.opId >>an_inFaInject.regName >>an_inFaInject.isFmBitwise;
//							if((an_inFaInject.subTarData == "1")&&(an_inFaInject.dynId == tp1->dynId))
//							{
//								if((an_inFaInject.opId == tp1->opId)&&(an_inFaInject.regName == tp1->regnam))
//								{
//									an_instrStateUnit->subTarData1[0]->tempSts[an_inFaInject.elePositId] = an_inFaInject.isFmBitwise;
//								}
//							}
//						}
//						isfile.close();
//					}else
//					{
//						ofstream isfile1;
//						isfile1.open("fault_injection");
//						isfile1<<signSubTaData<<" "<<i<<" "<<tp1->dynId<<" "<<tp1->opId<<" "<<tp1->regnam<<" "<<"0"<<endl;
//						isfile1.close();
//					}
//				}
//				for(i=0;i<sz1;i++)
//				{
//					sum += an_instrStateUnit->subTarData1[0]->tempSts[i];
//				}
//				tp1->numOfMaskBits = sum;
//				tp1->ratio = sum/sz1;
//			}
//			fmc->mulCounter.push_back(tp1);
//		}
//		//for the second operand
//		if(!an_instrStateUnit->subTarData2.empty())
//		{
//			sum = 0;
//			//fmCounter *fmc2 = new fmCounter();
//			for(i=0;i<sz1;i++)
//			{
//				sum += an_instrStateUnit->subTarData2[0]->tempSts[i];
//			}
//			/*fmcVector.push_back(fCounterList);*/
//			struct sglCounter *tp2 = new sglCounter();
//			tp2->dynId = app_trace[k]->line0_dynInstId;
//			tp2->numOfMaskBits = sum;
//			tp2->opId = app_trace[k]->line0_opcodeId;
//			tp2->ratio = sum/sz1;
//			tp2->regnam = an_instrStateUnit->subTarData2[0]->name;
//
//			//error propagation started
//			struct inFaInject an_inFaInject;
//
//			int nOfSteps = 1;
//			if(tp2->ratio < 1)
//			{
//				sign = "err";
//				signSubTaData = 2;
//				do{
//					opcodeId = app_trace[k+nOfSteps]->line0_opcodeId;
//					opcodeProFunction* an_opcodeProFunction = new opcodeProFunction(opcodeId, app_trace[k+nOfSteps]);
//					an_opcodeProFunction->opcodeProcess(an_instrStateUnit, an_globalStateUnit,sign,signSubTaData);//problems
//					sum = 0;
//					for(i=0;i<sz1;i++)
//					{
//						sum += an_instrStateUnit->subTarData2[0]->tempSts[i];
//					}
//					tp2->numOfMaskBits = sum;
//					tp2->ratio = sum/sz1;
//					nOfSteps++;
//				}while((nOfSteps == 10)||(tp2->ratio == 1));
//
//				if (tp2->ratio<1)
//				{
//					ifstream isfile("fault_injection_rel");
//					if (isfile.is_open()) {
//						isfile.open("fault_injection_rel");
//						//read the fault injection result and refresh the value of fault masking ratio
//						string ly;
//						while(!isfile.eof())
//						{
//							getline( isfile, ly );
//							istringstream ss(ly);
//							ss>>an_inFaInject.subTarData >>an_inFaInject.elePositId >>an_inFaInject.dynId >>an_inFaInject.opId >>an_inFaInject.regName >>an_inFaInject.isFmBitwise;
//							if((an_inFaInject.subTarData == "2")&&(an_inFaInject.dynId == tp2->dynId))
//							{
//								if((an_inFaInject.opId == tp2->opId)&&(an_inFaInject.regName == tp2->regnam))
//								{
//									an_instrStateUnit->subTarData2[0]->tempSts[an_inFaInject.elePositId] = an_inFaInject.isFmBitwise;
//								}
//							}
//						}
//						isfile.close();
//					}else
//					{
//						ofstream isfile1;
//						isfile1.open("fault_injection");
//						isfile1<<signSubTaData<<" "<<i<<" "<<tp2->dynId<<" "<<tp2->opId<<" "<<tp2->regnam<<" "<<"0"<<endl;
//						isfile1.close();
//					}
//				}
//				for(i=0;i<sz1;i++)
//				{
//					sum += an_instrStateUnit->subTarData2[0]->tempSts[i];
//				}
//				tp2->numOfMaskBits = sum;
//				tp2->ratio = sum/sz1;
//			}
//			fmc->mulCounter.push_back(tp2);
//		}
//		//for the third operand
//		if(!an_instrStateUnit->subTarData3.empty())
//		{
//			sum = 0;
//			//fmCounter *fmc3 = new fmCounter();
//			for(i=0;i<sz1;i++)
//			{
//				sum += an_instrStateUnit->subTarData3[0]->tempSts[i];
//			}
//			/*fmcVector.push_back(fCounterList);*/
//			struct sglCounter *tp3 = new sglCounter();
//			tp3->dynId = app_trace[k]->line0_dynInstId;
//			tp3->numOfMaskBits = sum;
//			tp3->opId = app_trace[k]->line0_opcodeId;
//			tp3->ratio = sum/sz1;
//			tp3->regnam = an_instrStateUnit->subTarData3[0]->name;
//
//			//error propagation started
//			struct inFaInject an_inFaInject;
//
//			int nOfSteps = 1;
//			if(tp3->ratio < 1)
//			{
//				sign = "err";
//				signSubTaData = 3;
//				do{
//					opcodeId = app_trace[k+nOfSteps]->line0_opcodeId;
//					opcodeProFunction* an_opcodeProFunction = new opcodeProFunction(opcodeId, app_trace[k+nOfSteps]);
//					an_opcodeProFunction->opcodeProcess(an_instrStateUnit, an_globalStateUnit,sign,signSubTaData);//problems
//					sum = 0;
//					for(i=0;i<sz1;i++)
//					{
//						sum += an_instrStateUnit->subTarData3[0]->tempSts[i];
//					}
//					tp3->numOfMaskBits = sum;
//					tp3->ratio = sum/sz1;
//					nOfSteps++;
//				}while((nOfSteps == 10)||(tp3->ratio == 1));
//
//				if (tp3->ratio<1)
//				{
//					ifstream isfile("fault_injection_rel");
//					if (isfile.is_open()) {
//						isfile.open("fault_injection_rel");
//						//read the fault injection result and refresh the value of fault masking ratio
//						string ly;
//						while(!isfile.eof())
//						{
//							getline( isfile, ly );
//							istringstream ss(ly);
//							ss>>an_inFaInject.subTarData >>an_inFaInject.elePositId >>an_inFaInject.dynId >>an_inFaInject.opId >>an_inFaInject.regName >>an_inFaInject.isFmBitwise;
//							if((an_inFaInject.subTarData == "3")&&(an_inFaInject.dynId == tp3->dynId))
//							{
//								if((an_inFaInject.opId == tp3->opId)&&(an_inFaInject.regName == tp3->regnam))
//								{
//									an_instrStateUnit->subTarData3[0]->tempSts[an_inFaInject.elePositId] = an_inFaInject.isFmBitwise;
//								}
//							}
//						}
//						isfile.close();
//					}else
//					{
//						ofstream isfile1;
//						isfile1.open("fault_injection");
//						isfile1<<signSubTaData<<" "<<i<<" "<<tp3->dynId<<" "<<tp3->opId<<" "<<tp3->regnam<<" "<<"0"<<endl;
//						isfile1.close();
//					}
//				}
//				for(i=0;i<sz1;i++)
//				{
//					sum += an_instrStateUnit->subTarData3[0]->tempSts[i];
//				}
//				tp3->numOfMaskBits = sum;
//				tp3->ratio = sum/sz1;
//			}
//			fmc->mulCounter.push_back(tp3);
//		}
//#endif
