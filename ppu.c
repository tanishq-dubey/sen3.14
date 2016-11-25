#include "ppu.h"
#include "memory.h"

static unsigned char default_palette [32] = {
    0x09, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x02, 0x0D,
    0x08, 0x10, 0x08, 0x24,
    0x00, 0x00, 0x04, 0x2C,
    0x09, 0x01, 0x34, 0x03,
    0x00, 0x04, 0x00, 0x14,
    0x08, 0x3A, 0x00, 0x02,
    0x00, 0x20, 0x2C, 0x08,
};
static unsigned char nes_palette[64][3] =
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
    //powerup state found at https://wiki.nesdev.com/w/index.php/PPU_power_up_state#Best_practice
    PPUCTRL = 0;
    PPUMASK = 0;
    PPUSTATUS = 0x80;
    OAMADDR = 0;
    OAMDATA = 0;
    PPUSCROLL = 0;
    PPUADDR = 0;
    PPUDATA = 0;

    x_or_y_scroll = true;
    x_offset = 0;
    y_offset = 0;

    addr_write = true;
    even_frame = true;

    ppu_cycles = 0;
    scanline = -1;
    end_scanline = 341; //note scanline is one cycle shorter if it's rendering an odd frame
    col = 0;
    VBlank = true;

    nameTable_start = 0x2000;
    attributeTable_start = 0x23C0;
    patternTable_start = 0x0000;

    PPU_VRAM_MEMORY = (uint8_t*)malloc(sizeof(uint8_t)*0x4000);
    PPU_OAM_MEMORY = (uint8_t*)malloc(sizeof(uint8_t)*256);

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

uint8_t ppu_read(uint16_t address)
{
	if(address < 0x2000)
	{
		return get_chr_mem()[address];
	}
	if(address == 0x2002) {
		return read_STATUS();
	}
	else if(address == 0x2004) {
		return read_OAMDATA();
	}
	else if(address == 0x2007) {
		return read_VRAMDATA();
	}

	return PPU_VRAM_MEMORY[normalize_address(address)];
}

void ppu_write(uint16_t address, uint8_t value) {
    if(address < 0x2000) {
        get_chr_mem()[address] = value;
    } else if(address == 0x2000) {
        write_CTRL(value);
    } else if(address == 0x2001) {
        write_MASK(value);
    } else if (address == 0x2003) {
        write_OAMADDR(value);
    } else if (address == 0x2004) {
        write_OAMDATA(value);
    } else if (address == 0x2005) {         
    	write_SCROLL(value);
    } else if (address == 0x2006) {
        write_VRAMADDR(value);
    } else if (address == 0x2007) {
        write_VRAMDATA(value);
    } else if (address == 0x4014) {
    	write_OAMDMA(value);
    } else {
    	PPU_VRAM_MEMORY[normalize_address(address)] = value;
    }
}

uint8_t read(uint16_t address) {
	if(address < 0x2000) {
            return get_chr_mem()[address];
	}
	return PPU_VRAM_MEMORY[normalize_address(address)];
}

void write(uint16_t address, uint8_t value) {
    if(address < 0x2000) {
        get_chr_mem()[address] = value;
    } else {
    	PPU_VRAM_MEMORY[normalize_address(address)] = value;
    }
}

void reset_ppu()
{
	PPUCTRL = 0;
	PPUMASK = 0;
	PPUSCROLL = 0;
	PPUDATA = 0;

	PPUSTATUS = PPUSTATUS & 0x80;
	ppu_cycles = 0;
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
		return address -= 0x020;
	}
	else if(address >= 0x3F40 && address <= 0x3F5F)
	{
		return address -= 0x040;
	}
	else if(address >= 0x3F60 && address <= 0x3F7F)
	{
		return address -= 0x060;
	}
	else if(address >= 0x3F80 && address <= 0x3F9F)
	{
		return address -= 0x080;
	}
	else if(address >= 0x3FA0 && address <= 0x3FBF)
	{
		return address -= 0x0A0;
	}
	else if(address >= 0x3FC0 && address <= 0x3FDF)
	{
		return address -= 0x0C0;
	}
	else if(address >= 0x3FE0 && address <= 0x3FFF)
	{
		return address -= 0x0E0;
	}

	//for img and sprite palette
	if(address == 0x3F04 || address == 0x3F08 || address == 0x3F0C || address == 0x3F10 || address == 0x3F14 || address == 0x3F18 || address == 0x3F1C)
	{
		return address = 0x3F00;
	}
        debug_print("Uncaught memory location: 0x%02x", address);
        return 0;
}

uint16_t mirror_nameTable(uint16_t address)
{
	switch(WAY TO GET NAMETABLE MIRRORING) //TODO: finish code here
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
	if((value >> 3) & 0x01)
	{
		bgOn = true;
	}
	else
		bgOn = false;

	if((value >> 4) & 0x01)
	{
		spriteOn = true;
	}
	else spriteOn = false;

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

void write_OAMDMA(uint8_t value) {
	OAMDMA = value;
}

bool rendering_on()
{
	return spriteOn || bgOn;
}

//https://wiki.nesdev.com/w/index.php/PPU_rendering
void tick()
{
	if(VBlank && (PPUCTRL >> 7) & 0x01)
		set_nmi();
	else
		reset_nmi(); //TODO: Way to reset the nmi interrupt flag

	if(scanline >= 0 && scanline < 240 && rendering_on())
	{
		render();
	}

	col++;

	//new scanline! 
	if(col == end_scanline)
	{
		if(even_frame)
			end_scanline = 341;
		else
			end_scanline = 340;

		col = 0;
		scanline++;

		switch(scanline)
		{
			case 261:
				scanline = -1;
				even_frame = !even_frame;
				VBlank = false;
				PPUSTATUS &= 0x70; //set vblank flag as 0
			break;

			case 241:
				VBlank = true;
				PPUSTATUS |= 0x80; //set vblank flag as 1
			break;
		}
	}
}

void render()
{
	//https://wiki.nesdev.com/w/index.php/PPU_rendering
	//idle cycle
	if(col == 0)
	{

	}
	//data for each tile fetched
	else if(col >= 1 && col <= 256 && rendering_on())
	{
		fetchbg();
	}
	//data for sprites on next scanline fetched
	else if(col >= 257 && col <= 320)
	{

	}
	//first two tiles for next scanline fetched
	else if(col >= 321 && col <= 336 && rendering_on())
	{
		fetchbg();
	}
	//two bytes fetched but unknown??
	else if(col >= 337 && col <= 340)
	{

	}
}

void fetchbg()
{
	/*Conceptually, the PPU does this 33 times for each scanline:
Fetch a nametable entry from $2000-$2FBF.
Fetch the corresponding attribute table entry from $23C0-$2FFF and increment the current VRAM address within the same row.
Fetch the low-order byte of an 8x1 pixel sliver of pattern table from $0000-$0FF7 or $1000-$1FF7.
Fetch the high-order byte of this sliver from an address 8 bytes higher.
Turn the attribute data and the pattern table data into palette indices, and combine them with data from sprite data using priority.
https://wiki.nesdev.com/w/images/d/d1/Ntsc_timing.png
*/
	switch(col % 8)
	{
		case 0:
			if(col == 256)
				incLoopyVVert();
			else
				incLoopyVHoriz();
			break;
		case 1:
			//fetch ntbyte
			nameTable = read(nameTable_start + (loopyV & 0x03FF));
			break;
		case 2:
			break;
		case 3:
			//fetch attribute byte
			attributeTable = read(attributeTable_start + (loopyV & 0x03FF));
			break;
		case 4:
			break;
		case 5:
			//fetch low bg byte
			lowByte = read(patternTable_start + nameTable + ((loopyV & 0x7000) >> 12));
			break;
		case 6:
			break;
		case 7:
			//fetch high bg byte
			highByte = read(patternTable_start + nameTable + 8 + ((loopyV & 0x7000) >> 12));
			break;
	}
}

//horizontal and vertical taken from http://wiki.nesdev.com/w/index.php/PPU_scrolling#Wrapping_around
void incLoopyVVert()
{
	if((loopyV & 0x7000) != 0x7000)
	{
		loopyV += 0x1000;
	}
	else
	{
		loopyV &= ~0x7000;
		int y = (loopyV & 0x03E0) >> 5;
		if(y == 29)
		{
			y = 0;
			loopyV ^= 0x0800;
		}
		else if(y == 31)
		{
			y = 0;
		}
		else
		{
			y++;
		}
		loopy = (loopy & ~0x03E0) | (y << 5);
	}
}

void incLoopyVHoriz()
{
	if((loopyV & 0x001F) == 31)
	{
		loopyV &= 0x001F;
		loopyV ^= 0x0400;
	}
	else
		loopyV++;
}

void render_sprite()
{
	//https://wiki.nesdev.com/w/index.php/PPU_sprite_evaluation
	if((PPUCTRL >> 5) & 0x01)
	{
		//render_8by16
	}
}

void render_pixel()
{

}

