#ifndef PPU_H
#define PPU_H

#include "cpu.h"
#include "memory.h"
#include "main.h"

typedef struct ppu {
    uint8_t PPUCTRL;
    uint8_t PPUMASK;
    uint8_t PPUSTATUS;
    uint8_t OAMADDR;
    uint8_t OAMDATA;
    uint16_t PPUSCROLL;
    uint16_t PPUADDR;
    uint8_t PPUDATA;
    char * PPU_MEMORY;
    uint8_t PPUSCROLL_WRITE_NUM;
    uint8_t PPUADDR_WRITE_NUM;
}ppu;

static struct ppu ppupack;

void init_ppu();
void reset_ppu();
void ppu_write(uint16_t address, uint8_t value);
#endif
