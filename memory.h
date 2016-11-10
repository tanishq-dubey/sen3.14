#ifndef MEMORY_H
#define MEMORY_H

#include "game.h"
#include "ppu.h"

typedef struct memory_t {
   uint8_t *memory_location;
   uint8_t ppu_register_six_write;
   uint8_t ppu_register_five_write;
} memory_t;

static struct memory_t memory;

void init_memory();
uint8_t read(uint16_t address);
void write(uint16_t address, uint8_t value);

#endif /* MEMORY_H */
