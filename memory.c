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
    memory.ppu_register_six_write  = 0;
    memory.ppu_register_five_write = 0;
    debug_print("%s", "\033[32;1mMemory init info:\033[0m\n");
    if(debug) {
        int i;
        for (i = 0; i < 4; i++) {
            debug_print("0x%02X: 0x%02X 0x%02X 0x%02X 0x%02X\n", 0x8000+(i*4), read(0x8000+(i*4)), read(0x8001+(i*4)), read(0x8002+(i*4)), read(0x8003+(i*4)));
        }
        for (i = 0; i < 4; i++) {
            debug_print("0x%02X: 0x%02X 0x%02X 0x%02X 0x%02X\n", 0xC000+(i*4), read(0xC000+(i*4)), read(0xC001+(i*4)), read(0xC002+(i*4)), read(0xC003+(i*4)));
        }
    }
}

uint8_t read(uint16_t address) {
    return memory.memory_location[address];
}

uint16_t read_short(uint16_t address) {
    return (uint16_t)((read(address) << 8) | read(address));
}

void write(uint16_t address, uint8_t value) {
    if (address >= 0x2000 && address <= 0x2007) {
        ppu_write(address, value);
    }
    memory.memory_location[address] = value;
}
