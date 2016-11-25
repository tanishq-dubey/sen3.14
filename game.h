#ifndef GAME_C
#define GAME_C

#include "main.h"
#include "memory.h"

typedef struct game {
    uint32_t prg_rom_size;
    uint32_t chr_rom_size;
    uint8_t prg_rom_banks;
    uint8_t chr_rom_banks;
    uint8_t flags_six;
    uint8_t flags_seven;
    uint8_t *rom_data;
    uint8_t mapper_mode;
    uint8_t mirror_mode;
} game;

enum { 
    Horizontal,
    Vertical,
    SingleScreen,
    SingleScreenLowerBank,
    SingleScreenUpperBank,
    FourScreen
} mirroring;

static struct game gamepack;

void init_game(uint8_t *rom);
uint8_t* get_rom_file();
uint8_t get_prg_banks();
uint8_t get_chr_banks();
uint8_t get_mapper();
void set_mirror_mode(uint8_t value);
uint8_t get_mirror_mode();

#endif /* GAME_C */
