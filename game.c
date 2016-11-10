#include "game.h"

void init_game(unsigned char* rom) {
    // ROM Validation:
    if( rom[0] != 'N' && rom[1] != 'E' && rom[2] != 'S' && rom[3] != '\32') {
        printf("Invalid ROM file, header does not match (%s, %s::%d)\n", __FILE__, __func__, __LINE__);
        free(rom);
        exit(0);
    }
    // Get header file information: https://wiki.nesdev.com/w/index.php/INES
    gamepack.prg_rom_size = rom[4];
    gamepack.chr_rom_size = rom[5];
    gamepack.flags_six     = rom[6];
    gamepack.flags_seven   = rom[8];
    gamepack.mapper_mode = (gamepack.flags_seven & 0xF) |  ((gamepack.flags_six & 0xF0) >> 4);
    gamepack.rom_data = rom;
    if (debug) {
        printf("PRG ROM Size: 0x%02X\n", gamepack.prg_rom_size);
        printf("CHR ROM Size: 0x%02X\n", gamepack.chr_rom_size);
        printf("Flag 6:       0x%02X\n", gamepack.flags_six);
        printf("Flag 7:       0x%02X\n", gamepack.flags_seven);
        printf("Mapper Mode:  0x%02X\n", gamepack.mapper_mode);
    }
}

unsigned char* get_rom_file() {
    return gamepack.rom_data;
}
