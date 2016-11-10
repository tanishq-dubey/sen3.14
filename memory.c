#include "memory.h"

void init_memory() {
    // TODO: Maybe change to calloc for faster access?
    // Opinions steven?
    memory.memory_location = (uint8_t*)malloc(0x10000);

    // Get rom file and copy it over to the RAM
    // Memory map from: http://fms.komkon.org/EMUL8/NES.html
    uint8_t* rom_file = get_rom_file();
    memcpy(&memory.memory_location[0x8000], rom_file+0x3800, 16384);
    memcpy(&memory.memory_location[0xC000], rom_file+0x3C00, 16384);
    if (debug) {
        printf("RAM instantiation results:\n");
        int i;
        printf("0x8000: ");
        for(i = 0; i < 4; i++) {
            printf("0x%02x ", memory.memory_location[0x8000+i]);
        }
        printf("\n0x8004: ");
        for(i = 4; i < 8; i++) {
            printf("0x%02x ", memory.memory_location[0x8004+i]);
        }
        printf("\n0x8008: ");
        for(i = 8; i < 12; i++) {
            printf("0x%02x ", memory.memory_location[0x8008+i]);
        }
        printf("\n0x800C: ");
        for(i = 12; i < 16; i++) {
            printf("0x%02x ", memory.memory_location[0x800C+i]);
        }
        printf("\n\n0xC000: ");
        for(i = 0; i < 4; i++) {
            printf("0x%02x ", memory.memory_location[0xC000+i]);
        }
        printf("\n0xC004: ");
        for(i = 4; i < 8; i++) {
            printf("0x%02x ", memory.memory_location[0xC004+i]);
        }
        printf("\n0xC008: ");
        for(i = 8; i < 12; i++) {
            printf("0x%02x ", memory.memory_location[0xC008+i]);
        }
        printf("\n0xC00C: ");
        for(i = 12; i < 16; i++) {
            printf("0x%02x ", memory.memory_location[0xC00C+i]);
        }

        printf("\nPC Initial value: 0x%02X%02X", memory.memory_location[0xFFFC], memory.memory_location[0xFFFD]);
    }
}

static uint8_t read(uint16_t address) {
    if (address == 0x2002) {
        // TODO: Return PPU Status
        return 0x80;
    }
    return memory.memory_location[address];
}
