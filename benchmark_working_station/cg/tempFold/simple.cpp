#include <stdio.h>

//#include "print.h"

int main(int argc, char **argv)
{
  unsigned int i, j;
  int array[50], sum=0;
  for (i = 0; i < 50; ++i)
    {
	array[i] = 0;
        array[i] += 2;
    }
  for (j = 0; j < 50; ++j)
    {
        sum += array[j];
    }
  printf("Sum %d\n", sum);
  return 0;
}
