#include "ppu.h"
#include "cpu.h"

void init_ppu()
{
	PPUCTRL = 0x00;
	PPUMASK = 0x00;
	PPUSTATUS = MEMORY[0x2002] & 0xA0;
	OAMADDR = 0x00;
	OAMDATA = 0x00;
	PPUSCROLL = 0x0000;
	PPUADDR = 0x0000;
	PPUDATA = 0x00;
}

void reset_ppu()
{
	PPUCTRL = 0x00;
	PPUMASK = 0x00;
	OAMDATA = 0x00;
	PPUSCROLL = 0x0000;
	PPUDATA = 0x00;
}