#ifndef _FLOATING_POINT_BINARY_32_64_CONVERTOR_H_
#define _FLOATING_POINT_BINARY_32_64_CONVERTOR_H_

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <sstream>
#include <iostream>

//typedef __int64 int64_t;  
//typedef unsigned __int64 uint64_t;  
//typedef unsigned __int32 uint32_t;  
//typedef unsigned __int16 uint16_t;  
//typedef unsigned __int8 uint8_t;  

//#define pack754_32(f) (pack754((f), 32, 8))
//#define pack754_64(f) (pack754((f), 64, 11))
//#define unpack754_32(i) (unpack754((i), 32, 8))
//#define unpack754_64(i) (unpack754((i), 64, 11))

using namespace std;

uint64_t pack754(long double f, unsigned bits, unsigned expbits);
long double unpack754(uint64_t i, unsigned bits, unsigned expbits);
uint64_t pack754_32(long double f);
uint64_t pack754_64(long double f);
long double unpack754_32(uint64_t i);
long double unpack754_64(uint64_t i);

#endif
