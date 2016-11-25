#ifndef MMC_TWO_H
#define MMC_TWO_H

#include "main.h"
#include "memory.h"
#include "game.h"

typedef struct mapper_two_t {
	int prg_banks_total;
	int prg_bank_one;
	int prg_bank_two;
} mapper_two_t;

static mapper_two_t mapper_two;

void mapper_two_init();
void mapper_two_step();
uint8_t mapper_two_read(uint16_t address);
void mapper_two_write(uint16_t address, uint8_t value);
uint8_t mapper_two_mirror();


#endif /* MMC_TWO_H */
