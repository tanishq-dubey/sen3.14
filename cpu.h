#ifndef CPU_H
#define CPU_H

#include <stdlib.h>

unsigned char A;    // Accumulator
unsigned char X;    // Iteration registers
unsigned char Y;
unsigned char S;    // Stack Pointer

unsigned short PC; // Program Counter

char * MEMORY;



// Status flags
unsigned char carry;
unsigned char zero;
unsigned char interrupt;
unsigned char decimal;
unsigned char overflow;
unsigned char negative;

void init_cpu();
void reset_cpu();

#endif
