#ifndef GAME_C
#define GAME_C

#include "main.h"

typedef struct game {
    unsigned char prg_rom_size;
    unsigned char chr_rom_size;
    unsigned char flags_six;
    unsigned char flags_seven;
    unsigned char *rom_data;
    unsigned char mapper_mode;
} game;

static struct game gamepack;

void init_game(unsigned char* rom);
unsigned char* get_rom_file();

#endif /* GAME_C */
