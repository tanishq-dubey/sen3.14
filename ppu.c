#include "ppu.h"
#include "memory.h"

void init_ppu()
{
	//powerup state found at https://wiki.nesdev.com/w/index.php/PPU_power_up_state#Best_practice
	PPUCTRL = 0;
	PPUMASK = 0;
	PPUSTATUS = 0;
	OAMADDR = 0;
	OAMDATA = 0;
	PPUSCROLL = 0;
	PPUADDR = 0;
	PPUDATA = 0;

	x_or_y_scroll = true;
	x_offset = 0;
	y_offset = 0;

	addr_write = true;

	PPU_VRAM_MEMORY = (uint8_t*)malloc(sizeof(uint8_t)*0x10000);
	PPU_OAM_MEMORY = (uint8_t*)malloc(sizeof(uint8_t)*256);

	if(debug)
	{
		debug_print("%s","\033[32;1mPPU Register Data:\033[0m\n");
        debug_print("0x2000: 0x%02x\n", PPUCTRL);
        debug_print("0x2001: 0x%02x\n", PPUMASK);
        debug_print("0x2002: 0x%02x\n", PPUSTATUS);
        debug_print("0x2003: 0x%02x\n", OAMADDR);
        debug_print("0x2004: 0x%02x\n", OAMDATA);
        debug_print("0x2005: 0x%02x\n", PPUSCROLL);
        debug_print("0x2006: 0x%02x\n", PPUADDR);
        debug_print("0x2007: 0x%02x\n", PPUDATA);
	}
} 

void reset_ppu()
{
	PPUCTRL = 0;
	PPUMASK = 0;
	PPUSCROLL = 0;
	PPUDATA = 0;

	PPUSTATUS = PPUSTATUS & 0x80;
}

uint8_t read_STATUS()
{
	uint8_t data = PPUSTATUS;
	PPUSTATUS = PPUSTATUS & 0x7F;
	PPUADDR = 0;
	PPUDATA = 0;
	return data;
}

uint8_t read_OAMDATA()
{
	return PPU_OAM_MEMORY[OAMADDR];
}

uint8_t read_VRAMDATA()
{
	uint8_t data = PPU_VRAM_MEMORY[PPUADDR];
	if(PPUCTRL & 0x04)
	{
		PPUADDR += 32;
	}
	else
	{
		PPUADDR += 1;
	}

	return data;
}

void write_CTRL(uint8_t value)
{
	PPUCTRL = value;
}

void write_MASK(uint8_t value)
{
	PPUMASK = value;
}

void write_OAMADDR(uint8_t addr)
{
	OAMADDR = addr;
}

void write_OAMDATA(uint8_t value)
{
	PPU_OAM_MEMORY[OAMADDR] = value;
	OAMADDR++;
}

void write_SCROLL(uint8_t value)
{
	if(x_or_y_scroll)
	{
		//first write
		x_offset = value & 0x07;
	}
	else
	{
		y_offset = value;
	}

	x_or_y_scroll = !x_or_y_scroll;
}

void write_VRAMADDR(uint8_t value)
{
	if(addr_write)
	{
		PPUADDR = value << 8;
	}
	else
	{
		PPUADDR = (PPUADDR & 0xF0) | value;
	}

	addr_write = !addr_write;
}

void write_VRAMDATA(uint8_t value)
{
	PPU_VRAM_MEMORY[PPUADDR] = value;
	if(PPUCTRL & 0x04)
	{
		PPUADDR += 32;
	}
	else
	{
		PPUADDR += 1;
	}
}