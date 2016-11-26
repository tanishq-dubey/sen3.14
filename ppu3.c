#include "ppu3.h"
#include "memory.h"

static uint8_t nes_palette[64][3] =
{
   {0x80,0x80,0x80}, {0x00,0x00,0xBB}, {0x37,0x00,0xBF}, {0x84,0x00,0xA6},
   {0xBB,0x00,0x6A}, {0xB7,0x00,0x1E}, {0xB3,0x00,0x00}, {0x91,0x26,0x00},
   {0x7B,0x2B,0x00}, {0x00,0x3E,0x00}, {0x00,0x48,0x0D}, {0x00,0x3C,0x22},
   {0x00,0x2F,0x66}, {0x00,0x00,0x00}, {0x05,0x05,0x05}, {0x05,0x05,0x05},

   {0xC8,0xC8,0xC8}, {0x00,0x59,0xFF}, {0x44,0x3C,0xFF}, {0xB7,0x33,0xCC},
   {0xFF,0x33,0xAA}, {0xFF,0x37,0x5E}, {0xFF,0x37,0x1A}, {0xD5,0x4B,0x00},
   {0xC4,0x62,0x00}, {0x3C,0x7B,0x00}, {0x1E,0x84,0x15}, {0x00,0x95,0x66},
   {0x00,0x84,0xC4}, {0x11,0x11,0x11}, {0x09,0x09,0x09}, {0x09,0x09,0x09},

   {0xFF,0xFF,0xFF}, {0x00,0x95,0xFF}, {0x6F,0x84,0xFF}, {0xD5,0x6F,0xFF},
   {0xFF,0x77,0xCC}, {0xFF,0x6F,0x99}, {0xFF,0x7B,0x59}, {0xFF,0x91,0x5F},
   {0xFF,0xA2,0x33}, {0xA6,0xBF,0x00}, {0x51,0xD9,0x6A}, {0x4D,0xD5,0xAE},
   {0x00,0xD9,0xFF}, {0x66,0x66,0x66}, {0x0D,0x0D,0x0D}, {0x0D,0x0D,0x0D},

   {0xFF,0xFF,0xFF}, {0x84,0xBF,0xFF}, {0xBB,0xBB,0xFF}, {0xD0,0xBB,0xFF},
   {0xFF,0xBF,0xEA}, {0xFF,0xBF,0xCC}, {0xFF,0xC4,0xB7}, {0xFF,0xCC,0xAE},
   {0xFF,0xD9,0xA2}, {0xCC,0xE1,0x99}, {0xAE,0xEE,0xB7}, {0xAA,0xF7,0xEE},
   {0xB3,0xEE,0xFF}, {0xDD,0xDD,0xDD}, {0x11,0x11,0x11}, {0x11,0x11,0x11}
};

void init_ppu()
{
	//powerup state taken from https://wiki.nesdev.com/w/index.php/PPU_power_up_state
	reset();

	ppu.flagSpriteZeroHit = 0;
	ppu.oamAddress = 0;
	ppu.v = 0;
	ppu.evenOddFrame = 0;

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
	ppu.scanline = VISIBLE_LINE;
	ppu.frame = 0;
}

uint8_t ppu_read(uint16_t address)
{
	if(address < 0x2000)
		return read(address);
	else if (address < 0x3F00)
		return PPU_VRAM_MEMORY[normalize_address(address)];
	else
		return read_palette(address % 32);
}

void ppu_write(uint16_t address, uint8_t value)
{
	if(address < 0x2000)
		write(address, value);
	else if (address < 0x3F00)
		PPU_VRAM_MEMORY[normalize_address(address)] = value;
	else
		read_palette(address % 32, value);
}

uint16_t normalize_address(uint16_t address)
{
	address &= 0x3FFF; //any address above 0x3FFF wraps around
	address = mirror_nameTable(address);
	//address 0x3000 to 0x3EFF are mirrors of 0x2000 to 0x2EFF
	if(address >= 0x3000 && address <= 0x3EFF)
	{
		address -= 0x1000;
	}
	
	//addresses 0x3F20 to 0x3FFF are all mirrors of 0x3F00 to 0x3F1F
	if(address >= 0x3F20 && address <= 0x3F3F)
	{
		address -= 0x020;
	}
	else if(address >= 0x3F40 && address <= 0x3F5F)
	{
		address -= 0x040;
	}
	else if(address >= 0x3F60 && address <= 0x3F7F)
	{
		address -= 0x060;
	}
	else if(address >= 0x3F80 && address <= 0x3F9F)
	{
		address -= 0x080;
	}
	else if(address >= 0x3FA0 && address <= 0x3FBF)
	{
		address -= 0x0A0;
	}
	else if(address >= 0x3FC0 && address <= 0x3FDF)
	{
		address -= 0x0C0;
	}
	else if(address >= 0x3FE0 && address <= 0x3FFF)
	{
		address -= 0x0E0;
	}

	return address;
}

uint16_t mirror_nameTable(uint16_t address)
{
	switch(mmc_mirror()) //TODO: finish code here
	{
		case horizontal:
			if(address >= 0x2400 && address <= 0x27FF)
			{
				return address - 0x0400;
			}
			else if (address >= 0x2C00 && address <= 0x2FFF)
		    {
		        return address - 0x0400;
		    }
		break;
		case vertical:
			if(address >= 0x2800 && address <= 0x2FFF)
			{
				return address - 0x0800;
			}
		break;
		case single_screen:
			if (address >= 0x2000 && address <= 0x2FFF)
      		{
        		return (address & 0x03FF) | 0x2000;
      		}
      	break;
		case four_screen:
		break;
	}

	return address;
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

void setVBlank()
{
	ppu.nmiOccurred = true;
}

void clearVBlank()
{
	ppu.nmiOccurred = false;
	reset_nmi();
}

void fetchNTByte()
{
	uint16_t address = 0x2000 | (ppu.v & 0x0FFF);
	ppu.nameTableByte = ppu_read(address);
}

void fetchATByte()
{
	uint16_t address = 0x23C0 | (ppu.v & 0x0C00) | ((ppu.v >> 4) & 0x38) | ((ppu.v >> 2) & 0x07);
	uint16_t shift = ((ppu.v >> 4) & 4) | (ppu.v & 2);
	ppu.attributeTableByte = ((ppu_read(address) >> shift) & 3) << 2;
}

void fetchLTByte()
{
	uint16_t address = 0x1000 * (uint16_t) ppu.flagBackgroundTable + (uint16_t) ppu.nameTableByte * 16 + (ppu.v >> 12) & 7;
	ppu.lowTileByte = ppu_read(address);
}

void fetchHTByte()
{
	uint16_t address = 0x1000 * (uint16_t) ppu.flagBackgroundTable + (uint16_t) ppu.nameTableByte * 16 + (ppu.v >> 12) & 7;
	ppu.highTileByte = ppu_read(address + 8);
}

void storeTileData()
{
	uint32_t data;
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		data <<= 4;
		data |= ppu.attributeTableByte | ((ppu.lowTileByte & 0x80) >> 7) | ((ppu.highTileByte & 0x80) >> 6);
		ppu.lowTileByte <<= 1;
		ppu.highTileByte <<= 1;
	}
	//stored where most sig 4 bits = pixel 0, next 4 = pixel 1, etc
	ppu.tileData |= (uint64_t) data;
}

void fetchTileData()
{
	return ppu.tileData >> 32;
}

uint8_t getBackgroundPixel()
{
	if(ppu.flagShowBackground == 0)
		return 0;

	uint8_t data = ppu.fetchTileData() >> ((7 - ppu.x) * 4);
	return data & 0x0F;
}

uint8_t getSpriteIndex()
{
	if(ppu.flagShowSprites == 0)
		return 0;

	int i = 0;
	for(i = 0; i < ppu.spriteCount; i++)
	{
		int offset = (ppu.cycle - 1) - ppu.spritePositions[i];
		if(offset < 0 || offset > 7) //out of bounds
		{
			continue;
		}
		offset = 7 - offset;
		uint8_t color = ((ppu.second_OAM[i] >> (offset * 4)) & 0x0F;
		if(color % 4 == 0)
		{
			continue;
		}
		return i;
	}

	return 0;
}

uint8_t getSpriteColor()
{
	if(ppu.flagShowSprites == 0)
		return 0;

	int i = 0;
	for(i = 0; i < ppu.spriteCount; i++)
	{
		int offset = (ppu.cycle - 1) - ppu.spritePositions[i];
		if(offset < 0 || offset > 7) //out of bounds
		{
			continue;
		}
		offset = 7 - offset;
		uint8_t color = ((ppu.second_OAM[i] >> (offset * 4)) & 0x0F;
		if(color % 4 == 0)
		{
			continue;
		}
		return color;
	}

	return 0;
}

void renderPixel()
{
	int x_pos = ppu.cycle - 1;
	int y_pos = ppu.scanline;
	uint8_t background = getBackgroundPixel();
	uint8_t sprite_index = getSpriteIndex();
	uint8_t sprite_color = getSpriteColor();

	if(x < 8 && ppu.flagShowLeftBackground == 0)
		background = 0;
	if(x < 8 && ppu.flagShowLeftSprites == 0)
		sprite_color = 0;

	/*Backdrop color (palette index 0) uses
	During forced blanking, when neither background nor sprites are enabled in PPUMASK ($2001), the picture will show the backdrop color. 
	If only the background or sprites are disabled, or if the left 8 pixels are clipped off, the PPU continues its normal video memory access pattern but uses the backdrop color for anything disabled.
	*/
	uint8_t color_index;
	if(background % 4 == 0 && sprite_color & 4 == 0)
		color_index = 0;
	else if (background % 4 == 0 && sprite_color != 0)
		color_index = sprite_color | 0x10;
	else if (background % 4 != 0 && sprite_color == 0)
		color_index = background;
	else
	{
		if(ppu.spriteIndexes[i] == 0 && x < 255)
			ppu.flagSpriteZeroHit = 1;

		if(ppu.spritePriorities[i] == 0)
			color_index = sprite_color | 0x10;
		else
			color_index = background;
	}

	uint8_t red = nes_palette[color_index % 64][0];
	uint8_t green = nes_palette[color_index % 64][1];
	uint8_t blue = nes_palette[color_index % 64][2];
	//TODO: set up pixel position from x_pos y_pos to rgb colors
}

//OAM layout found at https://wiki.nesdev.com/w/index.php/PPU_OAM
uint32_t fetchSpritePattern(int index, int row)
{
	uint8_t tile = PPU_OAM_MEMORY[index * 4 + 1];
	uint8_t attributes = PPU_OAM_MEMORY[index * 4 + 2];
	uint16_t address;
	if(ppu.flagSpriteSize == 0) //8 by 8 sprite
	{
		if(attributes & 0x80 == 0x80)//check vertical flip
			row = 7 - row;
		address = 0x1000 * ppu.flagSpriteTable + tile * 16 + row;
	}
	else //8 by 16 sprite
	{
		if(attributes & 0x80 == 0x80)//check vertical flip
			row = 15 - row;
		uint8_t table = tile & 1;
		tile &= 0xFE

		if(row > 7)
		{
			tile++;
			row -= 8;
		}

		address = 0x1000 * table + tile * 16 + row;
	}
	uint32_t a = (attributes & 3) << 2;
	uint8_t LTByte = ppu_read(address);
	uint8_t HTByte = ppu_read(address + 8);
	uint32_t data;
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		uint8_t p1;
		uint8_t p2;
		if(attributes & 0x40 == 0x40)//check horizontal flip
		{
			p1 = LTByte & 1;
			p2 = (HTByte & 1) << 1;
			LTByte >>= 1;
			HTByte >>= 1;
		}
		else
		{
			p1 = (LTByte & 0x80) >> 7;
			p2 = (HTByte & 0x80) >> 6;
			LTByte <<= 1;
			HTByte <<= 1;
		}

		data <<= 4;
		data |= (a | p1 | p2);
	}

	return data;
}

void evalualteSprites()
{
	int height;
	if(ppu.flagSpriteSize == 0)
		height = 8;
	else
		height = 16;

	int count = 0;
	int i = 0;
	for(i = 0; i < 64; i++)
	{
		uint8_t y = PPU_OAM_MEMORY[i * 4];
		uint8_t attributes = PPU_OAM_MEMORY[i * 4 + 2];
		uint8_t x = PPU_OAM_MEMORY[i * 4 + 3];
		int row = ppu.scanline - (int) y;
		//out of bounds
		if(row < 0 || row >= height)
			continue;
		if(count < 8)
		{
			ppu.second_OAM[count] = fetchSpritePattern(i, row);
			ppu.spritePositions[count] = x;
			ppu.spritePriorities[count] = (attributes >> 5) & 0x01;
			ppu.spriteIndexes[count] = (uint8_t) i;
		}
		count++;
	}

	if(count > 8) //greater than 8 = overflow!
	{
		count = 0;
		ppu.flagSpriteOverflow = 1;
	}

	ppu.spriteCount = count;
}

//rendering cycle found at https://wiki.nesdev.com/w/index.php/PPU_rendering
void step() //updates ppu variables like cycle, scanline, etc
{
	if(ppu.nmiOccurred && ppu.flagNmiAllowed)
		set_nmi();

	if(ppu.flagShowBackground || ppu.flagShowSprites)
	{
		if(ppu.evenOddFrame == 1 && ppu.scanline == PRE_RENDER_LINE && ppu.cycle == 339) //end of frame
		{
			ppu.cycle = 0;
			ppu.scanline = 0;
			ppu.frame++;
			ppu.evenOddFrame = 0;
			return
		}
	}

	ppu.cycle++;
	if(ppu.cycle > 340)
	{
		ppu.cycle = 0;
		ppu.scanline++;
		if(ppu.scanline > PRE_RENDER_LINE)
		{
			ppu.scanline = 0;
			ppu.frame++;
			ppu.evenOddFrame = 1;
		}
	}
}

void tick()
{
	step();

	//background rendering cycle
	if(ppu.flagShowBackground || ppu.flagShowSprites)
	{
		if(ppu.scanline < VISIBLE_LINE && ppu.cycle >= 1 && ppu.cycle <= 256) //visible cycle and scanline
		{
			renderPixel();
		}
		if((ppu.scanline == PRE_RENDER_LINE || ppu.scanline < VISIBLE_LINE) && ((ppu.cycle >= 1 && ppu.cycle <= 256) || (ppu.cycle >= 321 && ppu.cycle <= 336) )) //rendering time
		{
			ppu.tileData <<= 4;

			//timing based on https://wiki.nesdev.com/w/images/d/d1/Ntsc_timing.png
			switch(ppu.cycle % 8)
			{
				case 1:
					fetchNTByte();
					break;
				case 3:
					fetchATByte();
					break;
				case 5:
					fetchLTByte();
					break;
				case 7:
					fetchHTByte();
					break;
				case 0:
					storeTileData();
			}
		}

		if(ppu.scanline == PRE_RENDER_LINE && ppu.cycle >= 280 && ppu.cycle <= 304)
			copyY();

		if((ppu.scanline == PRE_RENDER_LINE || ppu.scanline < VISIBLE_LINE))
		{
			if(((ppu.cycle >= 1 && ppu.cycle <= 256) || (ppu.cycle >= 321 && ppu.cycle <= 336)) && ppu.cycle % 8 == 0)
				incLoopyVHoriz();
			if(ppu.cycle == 256)
				incLoopyVVert();
			if(ppu.cycle == 257)
				copyX();
		}
	}

	//sprite logic
	if(ppu.flagShowBackground || ppu.flagShowSprites)
	{
		if(ppu.cycle == 257)
		{
			if(ppu.scanline < VISIBLE_LINE)
				evalualteSprites();
			else
				ppu.spriteCount = 0;
		}
	}

	//vblank logic
	if(ppu.scanline == 241 && ppu.cycle == 1)
		setVBlank();

	if(ppu.scanline == PRE_RENDER_LINE && ppu.cycle == 1)
	{
		clearVBlank();
		ppu.flagSpriteOverflow = 0;
		ppu.flagSpriteZeroHit = 0;
	}
}