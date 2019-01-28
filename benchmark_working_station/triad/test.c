#include <stdio.h>
#include <iostream>

using namespace std;

#include "floating_point_Binary_32_64_convertor.h"

int main(){
  double a = 5.5;
  std::cout << "the value of a: " << a << std::endl;
  double b = unpack754_64(pack754_64(a)^(0xL<<61));
  std::cout << "the value of a-b: " << a-b << std::endl;
  return 0;
}
