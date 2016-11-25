#ifndef MMC_H
#define MMC_H

#include "main.h"
#include "game.h"
#include "memory.h"
#include "mmc2.h"
#include "mmc1.h"

void init_mmc();
void mmc_write(uint16_t address, uint8_t value);
uint8_t mmc_read(uint16_t address);
uint8_t get_mmc_mapper();

#endif /* MMC_H */
