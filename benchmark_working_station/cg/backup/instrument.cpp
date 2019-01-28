#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// the envir variable is used to decide the corruption of the passed data
// when the envir variable is equal to the dynamic instruciton counter
char* dynInstrID = getenv("DYN_INSTR_ID");// the input value
int _dynInstrID = atoi(dynInstrID);

int dynInstCounter = 0;// the incremental value

int functionDynInstCounter(int counter, char* OpcodeName)
{
  dynInstCounter++;
  counter = dynInstCounter;
  printf("\nthe current number of dyn instruction counter: %d \n", counter);
  cout << "the related Opcode name of current instruction:" << OpcodeName <<endl;
  return counter;
}
