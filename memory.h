#ifndef MEMORY_H
#define MEMORY_H
#include "game.h"

typedef struct memory_t {
   uint8_t *memory_location; 
} memory_t;

static struct memory_t memory;

void init_memory();
static uint8_t read(uint16_t);
void write(uint16_t address, uint8_t value);

#endif /* MEMORY_H */
