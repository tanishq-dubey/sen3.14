#ifndef CPU_H
#define CPU_H

#include "main.h"
#include "memory.h"

typedef struct cpu_t {
    unsigned char A;    // Accumulator
    unsigned char X;    // Iteration registers
    unsigned char Y;
    unsigned char S;    // Stack Pointer

    unsigned short PC; // Program Counter
    // Status flags
    unsigned char carry;
    unsigned char zero;
    unsigned char interrupt;
    unsigned char decimal;
    unsigned char overflow;
    unsigned char negative;
} cpu_t;

static struct cpu_t cpu;





void init_cpu();
void reset_cpu();

#endif
