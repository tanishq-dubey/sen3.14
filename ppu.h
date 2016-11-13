#ifndef PPU_H
#define PPU_H

#include "cpu.h"

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

bool x_or_y_scroll;
uint8_t x_offset;
uint8_t y_offset;

bool addr_write;

void init_ppu();
void reset_ppu();

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

#endif
