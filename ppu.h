#ifndef PPU_H
#define PPU_H

unsigned char PPUCTRL;
unsigned char PPUMASK;
unsigned char PPUSTATUS;
unsigned char OAMADDR;
unsigned char OAMDATA;
unsigned short PPUSCROLL;
unsigned short PPUADDR;
unsigned char PPUDATA;

//power up state found at https://wiki.nesdev.com/w/index.php/PPU_power_up_state#Best_practice
void init_ppu();
void reset_ppu();

#endif
