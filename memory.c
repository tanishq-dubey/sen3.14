#include "memory.h"
#include "mmc.h"

void init_memory() {
    // Initalize the 3 types of memory
    memory.sys_ram = (uint8_t*)malloc(sizeof(uint8_t) * 2048);
    memory.prg_mem = (uint8_t*)malloc(sizeof(uint8_t) * get_prg_banks() * 16384);
    int chr_size = 0;
    if (get_chr_banks() == 0) {
        memory.chr_mem = (uint8_t*)malloc(sizeof(uint8_t) * 8192);
        chr_size = 8192;
    } else {
        memory.chr_mem = (uint8_t*)malloc(sizeof(uint8_t) * get_chr_banks() * 8192);
        chr_size = get_chr_banks() * 8192;
    }
    // Copy information into the memory
    int i;
    int offset = 0;
    uint8_t* rom = get_rom_file();
    // Load PRG
    for (i = 0; i < get_prg_banks() * 16384; i++) {
        memory.prg_mem[i] = rom[i];
        offset++;
    }
    // Load CHR
    for(i = 0; i < chr_size; i++){
        memory.chr_mem[i] = rom[offset + i];
    }
    memory.save_ram = (uint8_t*)malloc(sizeof(uint8_t) * 0x2000);
}


uint8_t* get_prg_mem() {
    return memory.prg_mem;
}

uint8_t* get_chr_mem() {
    return memory.chr_mem;
}

uint8_t* get_sys_ram() {
    return memory.sys_ram;
}

uint8_t* get_save_ram() {
    return memory.save_ram;
}

uint8_t read(uint16_t address) {
    if(address < 0x2000) {
        return memory.sys_ram[address%0x0800];
    } else if (address < 0x4000) {
        return ppu_read(address); // READ PPU REGISTERS
    } else if (address >= 0x6000) {
        return mmc_read(address); // READ MAPPER STUFF!!
    }
    return 0;
}

uint16_t read_short(uint16_t address) {
    return (uint16_t)((read(address + 1) << 8) | read(address));
}

// Emulates a bug in the 6502 addressing
uint16_t read_short_bad(uint16_t address) {
    uint16_t a = address;
    uint16_t b = (a & 0xFF00) | (uint16_t)((uint8_t)(a+1));
    uint8_t low = read(a);
    uint8_t high = read(b);
    return (uint16_t)(high << 8) | (uint16_t)low;
}

void write(uint16_t address, uint8_t value) {
    if (address < 0x2000) {
        memory.sys_ram[address%0x0800] = value;
    } else if (address < 0x4000) {
        ppu_write(0x2000 + address%8, value);
    } else if (address == 0x4014) {
        ppu_write(address, value);
    } else if (address >= 0x6000) {
        mmc_write(address, value);
    }
}

void memory_dump() {
    FILE* file = fopen( "mem_dump.bin", "wb" );
    fwrite( memory.sys_ram, sizeof(uint8_t), 2048, file);
    file = freopen("mem_dump.bin", "ab", file);
    fwrite( memory.save_ram, sizeof(uint8_t), 0x2000, file);
    fclose(file);
}
