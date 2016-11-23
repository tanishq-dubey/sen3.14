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
    // 7  bit  0
    // ---- ----
    // NVss DIZC
    // |||| ||||
    // |||| |||+- Carry: 1 if last addition or shift resulted in a carry, or if
    // |||| |||     last subtraction resulted in no borrow
    // |||| ||+-- Zero: 1 if last operation resulted in a 0 value
    // |||| |+--- Interrupt: Interrupt inhibit
    // |||| |       (0: /IRQ and /NMI get through; 1: only /NMI gets through)
    // |||| +---- Decimal: 1 to make ADC and SBC use binary-coded decimal arithmetic
    // ||||         (ignored on second-source 6502 like that in the NES)
    // ||++------ s: No effect, used by the stack copy, see note below
    // |+-------- Overflow: 1 if last ADC or SBC resulted in signed overflow,
    // |            or D6 from last BIT
    // +--------- Negative: Set to bit 7 of the last operation
    unsigned char carry;
    unsigned char zero;
    unsigned char interrupt;
    unsigned char decimal;
    unsigned char breakf;
    unsigned char unused;
    unsigned char overflow;
    unsigned char negative;
    unsigned long cycles;
} cpu_t;

typedef struct tick_data_t {
    uint16_t address;
    uint16_t pc;
    uint8_t mode;
    uint8_t opcode;
} tick_data_t;

enum {
    pacle_intr,
    none_interrupt,
    nmi_interrupt,
    irq_interrupt,
} interrupt_mode;

enum {
    test,
    modeAbsolute,
    modeAbsoluteX,
    modeAbsoluteY,
    modeAccumulator,
    modeImmediate,
    modeImplied,
    modeIndexedIndirect,
    modeIndirect,
    modeIndirectIndexed,
    modeRelative,
    modeZeroPage,
    modeZeroPageX,
    modeZeroPageY
} addressing_mode;

static struct cpu_t cpu;
void init_cpu();
void reset_cpu();
int cpu_tick();
uint16_t get_pc();

void set_nmi();
void reset_nmi();

#endif
