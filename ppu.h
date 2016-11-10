#ifndef PPU_H
#define PPU_H

#include "cpu.h"

char * PPU_MEMORY;
void init_ppu();
void reset_ppu();

typedef struct ppu {
	uint8_t PPUCTRL;
	uint8_t PPUMASK;
	uint8_t PPUSTATUS;
	uint8_t OAMADDR;
	uint8_t OAMDATA;
	uint16_t PPUSCROLL;
	uint16_t PPUADDR;
	uint8_t PPUDATA;
}ppu;

static struct ppu ppupack;
#endif
