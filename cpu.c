#include "cpu.h"


// Names of all ops
static const char *instruction_names[256] = {
    "BRK", "ORA", "KIL", "SLO", "NOP", "ORA", "ASL", "SLO",
    "PHP", "ORA", "ASL", "ANC", "NOP", "ORA", "ASL", "SLO",
    "BPL", "ORA", "KIL", "SLO", "NOP", "ORA", "ASL", "SLO",
    "CLC", "ORA", "NOP", "SLO", "NOP", "ORA", "ASL", "SLO",
    "JSR", "AND", "KIL", "RLA", "BIT", "AND", "ROL", "RLA",
    "PLP", "AND", "ROL", "ANC", "BIT", "AND", "ROL", "RLA",
    "BMI", "AND", "KIL", "RLA", "NOP", "AND", "ROL", "RLA",
    "SEC", "AND", "NOP", "RLA", "NOP", "AND", "ROL", "RLA",
    "RTI", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
    "PHA", "EOR", "LSR", "ALR", "JMP", "EOR", "LSR", "SRE",
    "BVC", "EOR", "KIL", "SRE", "NOP", "EOR", "LSR", "SRE",
    "CLI", "EOR", "NOP", "SRE", "NOP", "EOR", "LSR", "SRE",
    "RTS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
    "PLA", "ADC", "ROR", "ARR", "JMP", "ADC", "ROR", "RRA",
    "BVS", "ADC", "KIL", "RRA", "NOP", "ADC", "ROR", "RRA",
    "SEI", "ADC", "NOP", "RRA", "NOP", "ADC", "ROR", "RRA",
    "NOP", "STA", "NOP", "SAX", "STY", "STA", "STX", "SAX",
    "DEY", "NOP", "TXA", "XAA", "STY", "STA", "STX", "SAX",
    "BCC", "STA", "KIL", "AHX", "STY", "STA", "STX", "SAX",
    "TYA", "STA", "TXS", "TAS", "SHY", "STA", "SHX", "AHX",
    "LDY", "LDA", "LDX", "LAX", "LDY", "LDA", "LDX", "LAX",
    "TAY", "LDA", "TAX", "LAX", "LDY", "LDA", "LDX", "LAX",
    "BCS", "LDA", "KIL", "LAX", "LDY", "LDA", "LDX", "LAX",
    "CLV", "LDA", "TSX", "LAS", "LDY", "LDA", "LDX", "LAX",
    "CPY", "CMP", "NOP", "DCP", "CPY", "CMP", "DEC", "DCP",
    "INY", "CMP", "DEX", "AXS", "CPY", "CMP", "DEC", "DCP",
    "BNE", "CMP", "KIL", "DCP", "NOP", "CMP", "DEC", "DCP",
    "CLD", "CMP", "NOP", "DCP", "NOP", "CMP", "DEC", "DCP",
    "CPX", "SBC", "NOP", "ISC", "CPX", "SBC", "INC", "ISC",
    "INX", "SBC", "NOP", "SBC", "CPX", "SBC", "INC", "ISC",
    "BEQ", "SBC", "KIL", "ISC", "NOP", "SBC", "INC", "ISC",
    "SED", "SBC", "NOP", "ISC", "NOP", "SBC", "INC", "ISC",
};
// Number of bytes based on the instruction:
static const uint8_t instruction_sizes[256] = {
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    3, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 0, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 0, 3, 0, 0,
    2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
};

// Cycles per instruction
static const uint8_t instruction_cycles[256] = {
    7, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    6, 6, 2, 8, 3, 3, 5, 5, 3, 2, 2, 2, 3, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    6, 6, 2, 8, 3, 3, 5, 5, 4, 2, 2, 2, 5, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
    2, 6, 2, 6, 4, 4, 4, 4, 2, 5, 2, 5, 5, 5, 5, 5,
    2, 6, 2, 6, 3, 3, 3, 3, 2, 2, 2, 2, 4, 4, 4, 4,
    2, 5, 2, 5, 4, 4, 4, 4, 2, 4, 2, 4, 4, 4, 4, 4,
    2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
    2, 6, 2, 8, 3, 3, 5, 5, 2, 2, 2, 2, 4, 4, 6, 6,
    2, 5, 2, 8, 4, 4, 6, 6, 2, 4, 2, 7, 4, 4, 7, 7,
};

// If page switch, number of extra cycles
static const uint8_t instruction_page_cycles[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
};

static const uint8_t instruction_modes[256] = {
    6, 7, 6, 7, 11, 11, 11, 11, 6, 5, 4, 5, 1, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 12, 12, 6, 3, 6, 3, 2, 2, 2, 2,
    1, 7, 6, 7, 11, 11, 11, 11, 6, 5, 4, 5, 1, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 12, 12, 6, 3, 6, 3, 2, 2, 2, 2,
    6, 7, 6, 7, 11, 11, 11, 11, 6, 5, 4, 5, 1, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 12, 12, 6, 3, 6, 3, 2, 2, 2, 2,
    6, 7, 6, 7, 11, 11, 11, 11, 6, 5, 4, 5, 8, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 12, 12, 6, 3, 6, 3, 2, 2, 2, 2,
    5, 7, 5, 7, 11, 11, 11, 11, 6, 5, 6, 5, 1, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 13, 13, 6, 3, 6, 3, 2, 2, 3, 3,
    5, 7, 5, 7, 11, 11, 11, 11, 6, 5, 6, 5, 1, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 13, 13, 6, 3, 6, 3, 2, 2, 3, 3,
    5, 7, 5, 7, 11, 11, 11, 11, 6, 5, 6, 5, 1, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 12, 12, 6, 3, 6, 3, 2, 2, 2, 2,
    5, 7, 5, 7, 11, 11, 11, 11, 6, 5, 6, 5, 1, 1, 1, 1,
    10, 9, 6, 9, 12, 12, 12, 12, 6, 3, 6, 3, 2, 2, 2, 2,
};

void init_cpu() {
    cpu.A = 0;
    cpu.X = 0;
    cpu.Y = 0;

    // http://forum.6502.org/viewtopic.php?t=1708
    cpu.PC = 0;
    cpu.PC = read_short(0xFFFC);

    cpu.S = 0xFD;
    cpu.carry = 0;
    cpu.zero = 0;
    cpu.interrupt = 0;
    cpu.decimal = 0;
    cpu.overflow = 0;
    cpu.negative = 0;

    debug_print("%s","\033[32;1mRegisters:\033[0m\n");
    debug_print("A:  0x%02X\n", cpu.A);
    debug_print("X:  0x%02X\n", cpu.X);
    debug_print("Y:  0x%02X\n", cpu.Y);
    debug_print("PC: 0x%02X\n", cpu.PC);
    debug_print("S:  0x%02X\n", cpu.S);
}

void push(uint8_t value) {
    write(0x100|(uint16_t)(cpu.S), value);
    cpu.S--;
}

void push_short(uint16_t value) {
    push((uint8_t)(value >> 8));
    push((uint8_t)(value & 0xFF));
}

uint8_t pop() {
    cpu.S++;
    return read(0x100 | (uint16_t)(cpu.S));
}

uint8_t generate_flags() {
    uint8_t flags = 0;
    flags |= cpu.carry << 0;
    flags |= cpu.zero << 1;
    flags |= cpu.interrupt << 2;
    flags |= cpu.decimal << 3;
    flags |= cpu.overflow << 6;
    flags |= cpu.negative << 7;
    return flags;
}

void set_flags(uint8_t value) {
    cpu.carry = (value >> 0) & 1;
    cpu.zero = (value >> 1) & 1;
    cpu.interrupt = (value >> 2) & 1;
    cpu.decimal = (value >> 3) & 1;
    cpu.overflow = (value >> 6) & 1;
    cpu.negative = (value >> 7) & 1;
}

void reset_cpu() {
    cpu.PC = read_short(0xFFFC);
    cpu.S = 0xFD;
    set_flags(0x24);
}

void set_z_flag(uint8_t value) {
    if (value == 0) {
        cpu.zero = 1;
    } else {
        cpu.zero = 0;
    }
}

void set_n_flag(uint8_t value) {
    if ((value & 0x80) != 0) {
        cpu.negative = 1;
    } else {
        cpu.negative = 0;
    }
}

void set_zn_flags(uint8_t value) {
    set_z_flag(value);
    set_n_flag(value);
}

uint8_t page_crossed(uint16_t address_a, uint16_t address_b) {
    return (address_a & 0xFF00) != (address_b & 0xFF00);
}

void check_branch_cycles(tick_data_t* step) {
    cpu.cycles++;
    if (page_crossed(step->pc, step->address)) {
        cpu.cycles++;
    }
}

void compare_set_flags(uint8_t val_a, uint8_t val_b) {
    set_zn_flags(val_a - val_b);
    if (val_a >= val_b) {
        cpu.carry = 1;
    } else {
        cpu.carry = 0;
    }
}

void set_nmi() {
    cpu.interrupt = nmi_interrupt;
}

void set_irq() {
    cpu.interrupt = irq_interrupt;
}

void do_nmi() {
    push_short(cpu.PC);
    push(generate_flags() | 0x10);
    cpu.PC = read_short(0xFFFA);
    cpu.interrupt = 1;
    cpu.cycles += 7;
}

void do_irq() {
    push_short(cpu.PC);
    push(generate_flags() | 0x10);
    cpu.PC = read_short(0xFFFE);
    cpu.interrupt = 1;
    cpu.cycles += 7;
}

int tick() {
    unsigned long cycles = cpu.cycles;
    switch(cpu.interrupt){
        case nmi_interrupt:
            do_nmi();
            break;
        case irq_interrupt:
            do_irq();
            break;
    }
    cpu.interrupt = none_interrupt;
    uint8_t opcode = read(cpu.PC);
    uint8_t mode = instruction_modes[opcode];

    uint16_t address;
    uint8_t page_cross = 0;
    uint16_t offset;    
    switch(mode) {
        case modeAbsolute:
            address = read_short(cpu.PC + 1);
            break;
        case modeAbsoluteX:
            address = read_short(cpu.PC + 1) + (uint16_t)cpu.X;
            page_cross = page_crossed(address - (uint16_t)cpu.X, address);
            break;
        case modeAbsoluteY:
            address = read_short(cpu.PC + 1) + (uint16_t)cpu.Y;
            page_cross = page_crossed(address - (uint16_t)cpu.Y, address);
            break;
        case modeAccumulator:
            address = 0;
            break;
        case modeImmediate:
            address = cpu.PC + 1;
            break;
        case modeImplied:
            address = 0;
            break;
        case modeIndexedIndirect:
            address = read_short_bad((uint16_t)(read(cpu.PC + 1) + cpu.X));
            break;
        case modeIndirect:
            address = read_short_bad(read_short(cpu.PC + 1));
            break;
        case modeIndirectIndexed:
            address = read_short_bad((uint16_t)(read(cpu.PC + 1)) + (uint16_t)(cpu.Y));
            page_cross = page_crossed(address - (uint16_t)(cpu.Y), address);
            break;
        case modeRelative:
            offset = (uint16_t)(read(cpu.PC + 1));
            if (offset < 0x80) {
                address = cpu.PC + 2 + offset;
            } else {
                address = cpu.PC + 2 + offset - 0x100;
            }
            break;
        case modeZeroPage:
            address = (uint16_t)(read(cpu.PC + 1));
            break;
        case modeZeroPageX:
            address = (uint16_t)(read(cpu.PC + 1) + cpu.X);
            break;
        case modeZeroPageY:
            address = (uint16_t)(read(cpu.PC + 1) + cpu.Y);
            break;
    }

    cpu.PC += (uint16_t)(instruction_sizes[opcode]);
    cpu.cycles += (unsigned long)(instruction_cycles[opcode]);
    if (page_cross) {
        cpu.cycles += (unsigned long)(instruction_page_cycles[opcode]);
    }
    
    tick_data_t* step_data = (tick_data_t*)malloc(sizeof(tick_data_t));
    step_data->pc = cpu.PC;
    step_data->address = address;
    step_data->mode = mode;
    // Call function pointer
    free(step_data);
    return cpu.cycles - cycles;
}
