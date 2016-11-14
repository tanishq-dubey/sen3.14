#include "game.h"

void init_game(uint8_t* rom) {
    // ROM Validation:
    if( rom[0] != 'N' && rom[1] != 'E' && rom[2] != 'S' && rom[3] != '\32') {
        debug_print("%s","Invalid ROM file, header does not match");
        free(rom);
        exit(0);
    }
    // Get header file information: https://wiki.nesdev.com/w/index.php/INES
    gamepack.prg_rom_banks = rom[4];
    gamepack.chr_rom_banks = rom[5];
    gamepack.prg_rom_size  = rom[4] * 0x4000;
    gamepack.chr_rom_size  = rom[5] * 0x2000;
    gamepack.flags_six     = rom[6];
    gamepack.flags_seven   = rom[7];
    gamepack.mapper_mode = (gamepack.flags_seven & 0xF0) |  ((gamepack.flags_six & 0xF0) >> 4);
    gamepack.rom_data = 0x10 + rom;
    int i;
    debug_print("%s", "\033[32;1mGame init info\033[0m\n");
    for(i = 0; i < 8; i++){
        debug_print("0x%02X \n", gamepack.rom_data[i]);
    }
    debug_print("PRG ROM Size: 0x%02X\n", gamepack.prg_rom_size);
    debug_print("PRG ROM Bank: 0x%02X\n", gamepack.prg_rom_banks);
    debug_print("CHR ROM Size: 0x%02X\n", gamepack.chr_rom_size);
    debug_print("CHR ROM Bank: 0x%02X\n", gamepack.chr_rom_banks);
    debug_print("Flag 6:       0x%02X\n", gamepack.flags_six);
    debug_print("Flag 7:       0x%02X\n", gamepack.flags_seven);
    debug_print("Mapper Mode:  0x%02X\n", gamepack.mapper_mode);
}

uint8_t* get_rom_file() {
    return gamepack.rom_data;
}

uint8_t get_prg_banks() {
    return gamepack.prg_rom_banks;
}

uint8_t get_chr_banks() {
    return gamepack.chr_rom_banks;
}

uint8_t get_mapper() {
    return gamepack.mapper_mode;
}
