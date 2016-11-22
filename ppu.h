#ifndef PPU_H
#define PPU_H

#include "cpu.h"
#include "memory.h"
#include "main.h"
#include <stdbool.h>

uint8_t * PPU_VRAM_MEMORY;
uint8_t * PPU_OAM_MEMORY;

uint8_t PPUCTRL;
uint8_t PPUMASK;
uint8_t PPUSTATUS;
uint8_t OAMADDR;
uint8_t OAMDATA;
uint16_t PPUSCROLL;
uint16_t PPUADDR;
uint8_t PPUDATA;
uint8_t OAMDMA;

bool x_or_y_scroll;
uint8_t x_offset;
uint8_t y_offset;

bool addr_write;
bool even_frame;

unsigned long ppu_cycles;
int scanline;
int end_scanline;
int col;
bool VBlank; 
bool spriteOn;
bool bgOn;

//https://wiki.nesdev.com/w/images/d/d1/Ntsc_timing.png
int loopyV;

enum {
    horizontal,
    vertical,
    single_screen,
    four_screen
} mirroring;

void init_ppu();
void reset_ppu();
void ppu_write(uint16_t address, uint8_t value);
uint8_t ppu_read(uint16_t address);
void normalize_address(uint16_t address);
uint16_t mirror_nameTable(uint16_t address);

//getting all the read write info on https://wiki.nesdev.com/w/index.php/PPU_registers#OAMADDR

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

void tick();
void render();
void render_sprites();
void render_pixels();
bool rendering_on();
#endif
