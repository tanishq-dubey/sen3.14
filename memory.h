#ifndef MEMORY_H
#define MEMORY_H

#include <strings.h>
#include "game.h"
#include "ppu.h"

typedef struct {
    uint8_t data[0x8000];
} prg_rom_page;

typedef struct {
    uint8_t data[0x2000];
} chr_rom_page;

typedef struct memory_t {
   uint8_t *memory_location;
   uint8_t ppu_register_six_write;
   uint8_t ppu_register_five_write;
   prg_rom_page* prg_page;
   chr_rom_page* chr_page;
} memory_t;


static struct memory_t memory;

void init_memory();
uint8_t read(uint16_t address);
uint16_t read_short(uint16_t address);
uint16_t read_short_bad(uint16_t address);
void write(uint16_t address, uint8_t value);
prg_rom_page get_prg_page(int page);
chr_rom_page get_chr_page(int page);

#endif /* MEMORY_H */
