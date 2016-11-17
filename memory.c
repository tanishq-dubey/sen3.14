#include "memory.h"
#include "mmc.h"

void init_memory() {
    memory.memory_location = (uint8_t*)malloc(0x10000);

    // Get rom file and copy it over to the RAM
    // Memory map from: http://fms.komkon.org/EMUL8/NES.html
    uint8_t* rom_file = get_rom_file();
    memcpy(&memory.memory_location[0x8000], rom_file + 16384, 16384);
    memcpy(&memory.memory_location[0xC000], rom_file, 16384);
    memory.ppu_register_six_write  = 0;
    memory.ppu_register_five_write = 0;
    debug_print("%s", "\033[32;1mMemory init info:\033[0m\n");
    prg_rom_page *prg_pages = malloc(get_prg_banks() * sizeof(prg_rom_page));
    chr_rom_page *chr_pages = malloc(get_chr_banks() * sizeof(chr_rom_page));
    int i, j;
    int offset = 0;
    debug_print("%s %d\n", "PRG ROM BANKS", gamepack.prg_rom_banks);
    for (i = 0; i < get_prg_banks(); i++) {
        for (j = 0; j < 0x8000; j++) {
            prg_pages[i].data[j] = rom_file[offset];
            offset++;
        }
    }
    for (i = 0; i < get_chr_banks(); i++) {
        for (j = 0; j < 0x2000; j++) {
            chr_pages[i].data[j] = rom_file[offset];
            offset++;
        }
    }
    memory.prg_page = prg_pages;
    memory.chr_page = chr_pages;
    init_mmc();
    if(debug) {
        int i;
        for (i = 0; i < 4; i++) {
            debug_print("0x%02X: 0x%02X 0x%02X 0x%02X 0x%02X\n", 0x8000+(i*4), read(0x8000+(i*4)), read(0x8001+(i*4)), read(0x8002+(i*4)), read(0x8003+(i*4)));
        }
        printf("\n");
        for (i = 0; i < 4; i++) {
            debug_print("0x%02X: 0x%02X 0x%02X 0x%02X 0x%02X\n", 0xB930+(i*4), read(0xB930+(i*4)), read(0xB931+(i*4)), read(0xB932+(i*4)), read(0xB933+(i*4)));
        }
        printf("\n");
        for (i = 0; i < 4; i++) {
            debug_print("0x%02X: 0x%02X 0x%02X 0x%02X 0x%02X\n", 0xC000+(i*4), read(0xC000+(i*4)), read(0xC001+(i*4)), read(0xC002+(i*4)), read(0xC003+(i*4)));
        }
        printf("\n");
        for (i = 0; i < 4; i++) {
            debug_print("0x%02X: 0x%02X 0x%02X 0x%02X 0x%02X\n", 0xF930+(i*4), read(0xF930+(i*4)), read(0xF931+(i*4)), read(0xF932+(i*4)), read(0xF933+(i*4)));
        }
    }
}

prg_rom_page get_prg_page(int page) {
    return memory.prg_page[page];
}

chr_rom_page get_chr_page(int page) {
    return memory.chr_page[page];
}

uint16_t normalizeAddress(uint16_t address) {
    address &= 0xFFFF;
    if (address >= 0x0000 && address <= 0x1FFF) {
        return address & 0x07FF;
    }
    else if (address >= 0x2000 && address <= 0x3FFF) {
        return address & 0x2007;
    }
    return address;
}

uint8_t read(uint16_t address) {
    // Check address range
    // Normalize
    // return direct memory
    if(address >= 0x8000 && address <= 0xFFFF) {
        return mmc_read(address);
    } 
    return memory.memory_location[address];
}

uint16_t read_short(uint16_t address) {
    return (uint16_t)((read(address + 1) << 8) | read(address));
}

uint16_t read_short_bad(uint16_t address) {
    uint16_t a = address;
    uint16_t b = (a & 0xFF00) | (uint16_t)((uint8_t)(a+1));
    uint8_t low = read(a);
    uint8_t high = read(b);
    return (uint16_t)(high << 8) | (uint16_t)low;
}

void write(uint16_t address, uint8_t value) {
    if(address >= 0x8000 && address <= 0xFFFF) {
        mmc_write(address, value);
        return;
    } 
    uint16_t n_addr = normalizeAddress(address);
    if (n_addr >= 0x2000 && n_addr <= 0x2007) {
        ppu_write(address, value);
    }
    memory.memory_location[address] = value;
}
