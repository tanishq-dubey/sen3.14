#ifndef GAME_C
#define GAME_C

#include "main.h"

typedef struct game {
    uint8_t prg_rom_size;
    uint8_t chr_rom_size;
    uint8_t flags_six;
    uint8_t flags_seven;
    uint8_t *rom_data;
    uint8_t mapper_mode;
} game;

static struct game gamepack;

void init_game(uint8_t *rom);
uint8_t* get_rom_file();

#endif /* GAME_C */
