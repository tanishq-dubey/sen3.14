#include "cpu.h"

void init_cpu() {
    A = 0;
    X = 0;
    Y = 0;
    PC = 0xFFFC;
    S = 0xFD;
    MEMORY = (char*)malloc(sizeof(char)*0x10000);
    int i;
    for (i = 0; i <= 0x2000; i++) {
        MEMORY[i] = 0xFF;
    }
    for (i = 0x2000; i <= 0x8000; i++) {
        MEMORY[i] = 0;
    }
    carry = 0;
    zero = 0;
    interrupt = 0;
    decimal = 0;
    overflow = 0;
    negative = 0;
}

void reset_cpu() {
    S = S -3;
    interrupt = 1;
}


