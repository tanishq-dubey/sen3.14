#ifndef MMC_ONE_H
#define MMC_ONE_H

#include "main.h"
#include "memory.h"
#include "game.h"

typedef struct mapper_one_t {
	uint8_t shift_register;
	uint8_t control_register;
	uint8_t prg_mode;
	uint8_t chr_mode;
	uint8_t prg_bank;
	uint8_t chr_bank_0;
	uint8_t chr_bank_1;
	int prg_bank_offset[2];
	int chr_bank_offset[2];
} mapper_one_t;

static mapper_one_t mapper_one;

void mapper_one_init();
void mapper_one_step();
uint8_t mapper_one_read(uint16_t address);
void mapper_one_write(uint16_t address, uint8_t value);


#endif /* MMC_ONE_H */