#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <inttypes.h>

#include "floating_point_Binary_32_64_convertor.h"

using namespace std;

// the envir variable is used to decide the corruption of the passed data
// when the envir variable is equal to the dynamic instruciton counter
//char* dynInstrID = getenv("DYN_INSTR_ID");// already pass into the corrupt function!!
//int _dynInstrID = atoi(dynInstrID);
uint64_t w = 1;

int dynInstCounter = 0;// the incremental value

int functionDynInstCounter(int counter, char* OpcodeName)
{
  dynInstCounter++;
  counter = dynInstCounter;
  //printf("\nthe current number of dyn instruction counter: %d \n", counter);
  //cout << "the related Opcode name of current instruction:" << OpcodeName <<endl;
  return counter;
}

int intFaultInjection(int c_value, int dynInstrID,int bitPosition){
  cout << "stepping into the -intFaultInjection- function ..." << endl;
  w = 1;
  if (abs(dynInstrID-dynInstCounter)<10){
    w<<=bitPosition;
	c_value = c_value^w;
	return c_value;
  }else{
    return c_value;
  }
    
}

double doubleFaultInjection(double c_value, int dynInstrID,int bitPosition){
  cout << "stepping into the -doubleFaultInjection- function ..." << endl;
  printf("\nthe current number of dyn instruction counter: %d \n", dynInstCounter);
  w = 1;
  if (abs(dynInstrID-dynInstCounter)<10){
    w<<=bitPosition;
    c_value = unpack754_64(pack754_64(c_value)^w);
    return c_value;
  }else{
    return c_value;
  }
}
