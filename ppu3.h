#ifndef PPU_H3
#define PPU_H3

#include "cpu.h"
#include "memory.h"
#include "main.h"
#include <stdbool.h>

typedef struct ppu_t {

	int cycle;
	int scanline;
	uint64_t frame;

	//ppu registers gotten from http://wiki.nesdev.com/w/index.php/PPU_scrolling
	uint16_t v; //current vram address ($2006)
	uint16_t t; //temp vram address
	uint8_t  x; //fine x scroll 3 bits
	uint8_t  w; //first or second write 0: first write 1: second write

	uint8_t prevWrite; //value written previously into a PPU register

	bool nmiOccurred;

	//background variables
	uint8_t nameTableByte;
	uint8_t attributeTableByte;
	uint8_t lowTileByte;
	uint8_t highTileByte;
	uint64_t tileData;

	uint32_t second_OAM[8];

	//taken from https://wiki.nesdev.com/w/index.php/PPU_registers
	// $2000 PPUCTRL
	uint8_t flagNameTable       ;  // 0: $2000; 1: $2400; 2: $2800; 3: $2C00
	uint8_t flagIncrement       ;  // 0: add 1; 1: add 32
	uint8_t flagSpriteTable     ;  // 0: $0000; 1: $1000; ignored in 8x16 mode
	uint8_t flagBackgroundTable ;  // 0: $0000; 1: $1000
	uint8_t flagSpriteSize      ;  // 0: 8x8; 1: 8x16
	uint8_t flagMasterSlave     ;  // 0: read EXT; 1: write EXT
	uint8_t flagNmiAllowed      ;  // 0: off; 1: on

	// $2001 PPUMASK
	uint8_t flagGrayscale          ; // 0: color; 1: grayscale
	uint8_t flagShowLeftBackground ; // 0: hide; 1: show
	uint8_t flagShowLeftSprites    ; // 0: hide; 1: show
	uint8_t flagShowBackground     ; // 0: hide; 1: show
	uint8_t flagShowSprites        ; // 0: hide; 1: show
	uint8_t flagRedTint            ; // 0: normal; 1: emphasized
	uint8_t flagGreenTint          ; // 0: normal; 1: emphasized
	uint8_t flagBlueTint           ; // 0: normal; 1: emphasized

	// $2002 PPUSTATUS
	uint8_t flagSpriteZeroHit  ;
	uint8_t flagSpriteOverflow ;

	// $2003 OAMADDR
	uint8_t oamAddress;

	// $2007 PPUDATA
	uint8_t bufferedData; // for buffered reads
} ppu_t;

uint8_t * paletteData;
uint8_t * PPU_VRAM_MEMORY;
uint8_t * PPU_OAM_MEMORY;


static struct ppu_t ppu;

void init_ppu();
void reset();
uint8_t read_registers(uint16_t address);
void write_registers(uint16_t address, uint8_t value);
uint8_t read_palette(uint16_t address);
void write_palette(uint16_t address, uint8_t value);

//getting all the read write info on https://wiki.nesdev.com/w/index.php/PPU_registers and http://wiki.nesdev.com/w/index.php/PPU_scrolling

//learning how to read
uint8_t read_STATUS();
uint8_t read_OAMDATA();
uint8_t read_VRAMDATA();

//beep boop writing stuff
void write_CTRL(uint8_t value);
void write_MASK(uint8_t value);
void write_OAMADDR(uint8_t addr);
void write_OAMDATA(uint8_t value);
void write_SCROLL(uint8_t value);
void write_VRAMADDR(uint8_t value);
void write_VRAMDATA(uint8_t value);
void write_OAMDMA(uint8_t value);

void incLoopyVVert();
void incLoopyVHoriz();
void copyX();
void copyY();

#endif
