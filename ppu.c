#include "ppu.h"
#include "memory.h"

void init_ppu()
{
	//powerup state found at https://wiki.nesdev.com/w/index.php/PPU_power_up_state#Best_practice
	write(0x2000, 0x00);
	write(0x2001, 0x00);
	write(0x2003, 0x00);
	write(0x2004, 0x00);
	write(0x2005, 0x00);
	write(0x2005, 0x00);
	write(0x2006, 0x00);
	write(0x2006, 0x00);
	write(0x2007, 0x00);

	uint8_t PPUSTATUS = read(0x2002);
	PPUSTATUS = PPUSTATUS & 0xA0;
	write(0x2002, PPUSTATUS);

	PPU_MEMORY = (char*)malloc(sizeof(char)*0x10000);
} 

void reset_ppu()
{
	write(0x2000, 0x00);
	write(0x2001, 0x00);
	write(0x2005, 0x00);
	write(0x2005, 0x00);
	write(0x2007, 0x00);
	uint8_t PPUSTATUS = read(0x2002);
	PPUSTATUS = PPUSTATUS & 0x80;
	write(0x2002, PPUSTATUS);
}