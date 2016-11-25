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
   uint8_t ppu_register_six_write;
   uint8_t ppu_register_five_write;
   uint8_t* prg_mem;
   uint8_t* chr_mem;
   uint8_t* sys_ram;
   uint8_t* save_ram;
} memory_t;


static struct memory_t memory;

void init_memory();
uint8_t read(uint16_t address);
uint16_t read_short(uint16_t address);
uint16_t read_short_bad(uint16_t address);
void write(uint16_t address, uint8_t value);

uint8_t get_mirror_mode_memory();

uint8_t* get_prg_mem();
uint8_t* get_chr_mem();
uint8_t* get_sys_ram();
uint8_t* get_save_ram();

void memory_dump();

#endif /* MEMORY_H */
