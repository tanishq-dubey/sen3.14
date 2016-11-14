#include "mmc.h"

void init_mmc() {
    bzero(prg_map, sizeof(prg_map)); 
    bzero(chr_map, sizeof(chr_map)); 
    uint8_t mapper = gamepack.mapper_mode;
    if (mapper == 0) {
        debug_print("%s", "initalizing mapper 0\n");
        switch(get_prg_banks()) {
            case 2:
                map_prg_16(0x8000, 0);
                map_prg_16(0xC000, 0);
                break;
            case 4:
                map_prg_32(0);
                break;
        }
        switch(get_chr_banks()) {
            case 0:
            case 8:
                map_chr_8(0);
                break;
        }
    }
}

void mmc_write(uint16_t address, uint8_t value) {
    uint8_t mapper = get_mapper();
    if (mapper == 0) {
        int index = (address >> 13) & 0x03;
        get_prg_page(prg_map[index]).data[address & 0x1FFF] = value; 
    }
}

uint8_t mmc_read(uint16_t address) {
    uint8_t mapper = get_mapper();
    if (mapper == 0) {
        int index = (address >> 13) & 0x03;
        return get_prg_page(prg_map[index]).data[address & 0x1FFF]; 
    }
   return 0; 
}

void map_prg(uint16_t address, uint8_t target, uint8_t to_map) {
    size_t index = (address >> 13) & 0x03;
    int i;
    for(i = 0; i < to_map; i++) {
        prg_map[index + i] = target + i;
    }
}

void map_prg_32(uint8_t target) {
    map_prg(0x8000, target * 4, 4);
}

void map_prg_16(uint16_t address, uint8_t target) {
    map_prg(address, target * 2, 2);
}

void map_prg_8(uint16_t address, uint8_t target) {
    map_prg(address, target, 1);
}

void map_chr(uint16_t address, uint8_t target, uint8_t to_map) {
    size_t index = (address >> 10) & 0x0F;
    int i;
    for(i = 0; i < to_map; i++) {
        chr_map[index + i] = target + i;
    }
}

void map_chr_8(uint8_t target) {
    map_chr(0x0000, target * 8, 8);
}

void map_chr_4(uint16_t address, uint8_t target) {
    map_chr(address, target * 4, 4);
}

void map_chr_2(uint16_t address, uint8_t target) {
    map_chr(address, target * 2, 2);
}

void map_chr_1(uint16_t address, uint8_t target) {
    map_chr(address, target * 1, 1);
}
