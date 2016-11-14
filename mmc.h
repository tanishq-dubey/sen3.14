#ifndef MMC_H
#define MMC_H

#include "main.h"
#include "game.h"
#include "memory.h"

uint8_t prg_map[4];
uint8_t chr_map[8];

void init_mmc();
void mmc_write(uint16_t address, uint8_t value);
uint8_t mmc_read(uint16_t address);

void map_prg(uint16_t address, uint8_t target, uint8_t to_map);
void map_prg_8(uint16_t address, uint8_t target);
void map_prg_16(uint16_t address, uint8_t target);
void map_prg_32(uint8_t target);

void map_chr(uint16_t address, uint8_t target, uint8_t to_map);
void map_chr_1(uint16_t address, uint8_t target);
void map_chr_2(uint16_t address, uint8_t target);
void map_chr_4(uint16_t address, uint8_t target);
void map_chr_8(uint8_t target);
#endif /* MMC_H */
