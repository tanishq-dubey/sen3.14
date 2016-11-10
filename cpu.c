#include "cpu.h"

void init_cpu() {
    cpu.A = 0;
    cpu.X = 0;
    cpu.Y = 0;
    // http://forum.6502.org/viewtopic.php?t=1708
    cpu.PC = 0;
    cpu.PC = (read(0xFFFC) << 8) | read(0xFFFD);
    cpu.S = 0xFF;
    cpu.carry = 0;
    cpu.zero = 0;
    cpu.interrupt = 0;
    cpu.decimal = 0;
    cpu.overflow = 0;
    cpu.negative = 0;
    if (debug) {
        printf("\nRegisters:\n");
        printf("A:  0x%02X\n", cpu.A);
        printf("X:  0x%02X\n", cpu.X);
        printf("Y:  0x%02X\n", cpu.Y);
        printf("PC: 0x%02X\n", cpu.PC);
        printf("S:  0x%02X\n", cpu.S);
    }
}

void reset_cpu() {
    cpu.S = cpu.S -3;
    cpu.interrupt = 1;
}


