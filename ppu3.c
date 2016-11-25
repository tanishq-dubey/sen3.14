#include "ppu3.h"
#include "memory.h"

void init_ppu()
{
	//powerup state taken from https://wiki.nesdev.com/w/index.php/PPU_power_up_state
	reset();

	ppu.flagSpriteZeroHit = 0;
	ppu.oamAddress = 0;
	ppu.v = 0;

	paletteData = (uint8_t*)malloc(sizeof(uint8_t)*32);
	PPU_VRAM_MEMORY = (uint8_t*)malloc(sizeof(uint8_t)*0x4000);
    PPU_OAM_MEMORY = (uint8_t*)malloc(sizeof(uint8_t)*256);
}

void reset()
{
	write_CTRL(0);
	write_MASK(0);
	write_OAMADDR(0);
	ppu.cycle = 340;
	ppu.scanline = 240;
	ppu.frame = 0;
}

uint8_t read_palette(uint16_t address)
{
	if(address % 4 == 0)
	{
		address = 0;
	}
	return paletteData[address];
}

void write_palette(uint16_t address, uint8_t value)
{
	if(address % 4 == 0)
	{
		address = 0;
	}
	paletteData[address] = value;
}

uint8_t read_registers(uint16_t address)
{
	if(address == 0x2002) {
		return read_STATUS();
	}
	else if(address == 0x2004) {
		return read_OAMDATA();
	}
	else if(address == 0x2007) {
		return read_VRAMDATA();
	}
}

void write_registers(uint16_t address, uint8_t value)
{
	ppu.prevWrite = value;
	if(address == 0x2000) {
		write_CTRL(value);
	}
	else if(address == 0x2001) {
		write_MASK(value);
	}
	else if (address == 0x2003) {
        write_OAMADDR(value);
    } 
    else if (address == 0x2004) {
        write_OAMDATA(value);
    } 
    else if (address == 0x2005) {         
    	write_SCROLL(value);
    } 
    else if (address == 0x2006) {
        write_VRAMADDR(value);
    } 
    else if (address == 0x2007) {
        write_VRAMDATA(value);
    } else if (address == 0x4014) {
    	write_OAMDMA(value);
    }
}

uint8_t read_STATUS()
{
	uint8_t data = ppu.prevWrite & 0x1F;
	data |= ppu.flagSpriteOverflow << 5;
	data |= ppu.flagSpriteZeroHit << 6;
	if(ppu.nmiOccurred)
	{
		data |= 1 << 7;
	}
	ppu.nmiOccurred = false;
	ppu.w = 0;
	return data;
}

uint8_t read_OAMDATA()
{
	return PPU_OAM_MEMORY[ppu.oamAddress];
}

uint8_t read_VRAMDATA()
{
	uint8_t data = ppu_read(ppu.v)
	if(ppu.v % 0x4000 < 0x3F00)
	{
		uint8_t buffered = ppu.bufferedData;
		ppu.bufferedData = data;
		data = buffered;
	}
	else
		ppu.bufferedData = ppu_read(ppu.v - 0x1000);

	//incrementing the address after a read
	if(ppu.flagIncrement)
	{
		ppu.v += 32;
	}
	else
	{
		ppu.v += 1;
	}

	return data;
}

void write_CTRL(uint8_t value)
{
	ppu.flagNameTable = value & 0x03;
	ppu.flagIncrement = (value >> 2) & 0x01;
	ppu.flagSpriteTable = (value >> 3) & 0x01;
	ppu.flagBackgroundTable = (value >> 4) & 0x01;
	ppu.flagSpriteSize = (value >> 5) & 0x01;
	ppu.flagMasterSlave = (value >> 6) & 0x01;
	ppu.flagNmiAllowed = (value >> 7) & 0x01;

	ppu.t = (ppu.t & 0xF3FF) | ((value & 0x03) << 10);
}

void write_MASK(uint8_t value)
{
	ppu.flagGrayScale = value & 0x01;
	ppu.flagShowLeftBackground =  (value >> 1) & 0x01;
	ppu.flagShowLeftSprites = (value >> 2) & 0x01;
	ppu.flagShowBackground = (value >> 3) & 0x01;
	ppu.flagShowSprites = (value >> 4) & 0x01;
	ppu.flagRedTint = (value >> 5) & 0x01;
	ppu.flagGreenTint = (value >> 6) & 0x01;
	ppu.flagBlueTint = (value >> 7) & 0x01;
}

void write_OAMADDR(uint8_t addr)
{
	ppu.oamAddress = value;
}

void write_OAMDATA(uint8_t value)
{
	PPU_OAM_MEMORY[ppu.oamAddress] = value;
	ppu.oamAddress++;
}

void write_SCROLL(uint8_t value)
{
	if(ppu.w == 0)
	{
		//first write
		ppu.t = (ppu.t & 0xFFE0) | (value >> 3);
		ppu.x = value & 0x07;
		ppu.w = 1;
	}
	else
	{
		ppu.t = (ppu.t & 0x8FFF) | (( (uint16_t) value & 0x07) << 12)
		ppu.t = (ppu.t & 0xFC1F) | (( (uint16_t) value & 0xF8) << 2)
		ppu.w = 0
	}
}

void write_VRAMADDR(uint8_t value)
{
	if(ppu.w == 0)
	{
		ppu.t = (ppu.t & 0x80FF) | (((uint16_t) value & 0x3F) << 8);
		ppu.w = 1;
	}
	else
	{
		ppu.t = (ppu.t * 0xFF00) | (uint16_t) value;
		ppu.v = ppu.t;
		ppu.w = 0;
	}
}

void write_VRAMDATA(uint8_t value)
{
	ppu_write(ppu.v, value);
	if(ppu.flagIncrement)
	{
		ppu.v += 32;
	}
	else
	{
		ppu.v += 1;
	}
}

void write_OAMDMA(uint8_t value) {
	uint16_t address = value << 8;
	int i = 0;
	for(i = 0; i < 256; i++)
	{
		PPU_OAM_MEMORY[ppu.oamAddress] = read(address);
		ppu.oamAddress++;
		address++;
	}

	//TODO: Way to stall the CPU for 513 or 514 cycles.
	//The CPU is suspended during the transfer, which will take 513 or 514 cycles after the $4014 write tick. (1 dummy read cycle while waiting for writes to complete, +1 if on an odd CPU cycle, then 256 alternating read/write cycles.)
}

//horizontal and vertical taken from http://wiki.nesdev.com/w/index.php/PPU_scrolling#Wrapping_around
void incLoopyVVert()
{
	if((ppu.v & 0x7000) != 0x7000)
	{
		ppu.v += 0x1000;
	}
	else
	{
		ppu.v &= ~0x7000;
		int y = (ppu.v & 0x03E0) >> 5;
		if(y == 29)
		{
			y = 0;
			ppu.v ^= 0x0800;
		}
		else if(y == 31)
		{
			y = 0;
		}
		else
		{
			y++;
		}
		ppu.v = (ppu.v & ~0x03E0) | (y << 5);
	}
}

void incLoopyVHoriz()
{
	if((ppu.v & 0x001F) == 31)
	{
		ppu.v &= ~0x001F;
		ppu.v ^= 0x0400;
	}
	else
		ppu.v++;
}

void copyX()
{
	ppu.v = (ppu.v & 0xFBE0) | (ppu.t & 0x041F);
}

void copyY()
{
	ppu.v = (ppu.v & 0x841F) | (ppu.t & 0x7BE0);
}