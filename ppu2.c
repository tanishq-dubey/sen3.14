#include "ppu2.h"

static uint8_t default_palette [32] = {
    0x09, 0x01, 0x00, 0x01,
    0x00, 0x02, 0x02, 0x0D,
    0x08, 0x10, 0x08, 0x24,
    0x00, 0x00, 0x04, 0x2C,
    0x09, 0x01, 0x34, 0x03,
    0x00, 0x04, 0x00, 0x14,
    0x08, 0x3A, 0x00, 0x02,
    0x00, 0x20, 0x2C, 0x08,
};

static uint8_t nes_palette[64][3] =
{
   {0x80,0x80,0x80}, {0x00,0x00,0xBB}, {0x37,0x00,0xBF}, {0x84,0x00,0xA6},
   {0xBB,0x00,0x6A}, {0xB7,0x00,0x1E}, {0xB3,0x00,0x00}, {0x91,0x26,0x00},
   {0x7B,0x2B,0x00}, {0x00,0x3E,0x00}, {0x00,0x48,0x0D}, {0x00,0x3C,0x22},
   {0x00,0x2F,0x66}, {0x00,0x00,0x00}, {0x05,0x05,0x05}, {0x05,0x05,0x05},

   {0xC8,0xC8,0xC8}, {0x00,0x59,0xFF}, {0x44,0x3C,0xFF}, {0xB7,0x33,0xCC},
   {0xFF,0x33,0xAA}, {0xFF,0x37,0x5E}, {0xFF,0x37,0x1A}, {0xD5,0x4B,0x00},
   {0xC4,0x62,0x00}, {0x3C,0x7B,0x00}, {0x1E,0x84,0x15}, {0x00,0x95,0x66},
   {0x00,0x84,0xC4}, {0x11,0x11,0x11}, {0x09,0x09,0x09}, {0x09,0x09,0x09},

   {0xFF,0xFF,0xFF}, {0x00,0x95,0xFF}, {0x6F,0x84,0xFF}, {0xD5,0x6F,0xFF},
   {0xFF,0x77,0xCC}, {0xFF,0x6F,0x99}, {0xFF,0x7B,0x59}, {0xFF,0x91,0x5F},
   {0xFF,0xA2,0x33}, {0xA6,0xBF,0x00}, {0x51,0xD9,0x6A}, {0x4D,0xD5,0xAE},
   {0x00,0xD9,0xFF}, {0x66,0x66,0x66}, {0x0D,0x0D,0x0D}, {0x0D,0x0D,0x0D},

   {0xFF,0xFF,0xFF}, {0x84,0xBF,0xFF}, {0xBB,0xBB,0xFF}, {0xD0,0xBB,0xFF},
   {0xFF,0xBF,0xEA}, {0xFF,0xBF,0xCC}, {0xFF,0xC4,0xB7}, {0xFF,0xCC,0xAE},
   {0xFF,0xD9,0xA2}, {0xCC,0xE1,0x99}, {0xAE,0xEE,0xB7}, {0xAA,0xF7,0xEE},
   {0xB3,0xEE,0xFF}, {0xDD,0xDD,0xDD}, {0x11,0x11,0x11}, {0x11,0x11,0x11}
};

void init_ppu() {
    ppu.VBlank  = false;
    ppu.nmi     = false;

    // Initalize memory
    ppu.vram    = (uint8_t*)malloc(sizeof(uint8_t) * PPU_MAIN_RAM_SIZE);
    ppu.spram   = (uint8_t*)malloc(sizeof(uint8_t) * PPU_SPRT_RAM_SIZE);

    // Set memory to zero (Should probably be doing this everywhere
    memset(ppu.vram, 0, PPU_MAIN_RAM_SIZE);
    memset(ppu.spram, 0, PPU_SPRT_RAM_SIZE);
    ppu.vram_addr = 0;

    ppu.PPUCTRL     = 0;
    ppu.PPUMASK     = 0;
    ppu.PPUSTATUS   = 0;
    ppu.OAMADDR     = 0;
    ppu.OAMDATA     = 0;
    ppu.PPUSCROLL   = 0;
    ppu.PPUADDR     = 0;
    ppu.OAMDMA      = 0;

    ppu.scanline  = ppu.prev_scanline = SCANLINE_INIT;
    ppu.ppu_cycle = 0;

    // TODO: initalize any GL/SDL renderer here
    int i;
    for(i = 0; i < 32; i++) {
        //ppu_write(PALETTE_BACK_ADDR + i++, default_palette[i]);
    }
}

void reset_ppu() {
    ppu.scanline  = SCANLINE_INIT;
    ppu.ppu_cycle = 0;
}

uint8_t ppu_p_read() {
    if (ppu.vram_addr < 0x2000) {
        // Should write to CHR mem
        return read(ppu.vram_addr);
    }
    return ppu.vram[normalize_address(ppu.vram_addr)];
}

uint8_t ppu_read(uint16_t address) {
    uint16_t tmp = ppu.vram_addr;
    ppu.vram_addr = address;
    uint8_t val = ppu_p_read();
    ppu.vram_addr = address;
    return val;
}

void ppu_p_write(uint8_t value) {
    if (ppu.vram_addr < 0x2000) {
        // Should write to CHR mem
        write(ppu.vram_addr, value);
    }
    ppu.vram[normalize_address(ppu.vram_addr)] = value;
}

void ppu_write(uint16_t address, uint8_t value) {
    uint16_t tmp = ppu.vram_addr;
    ppu.vram_addr = address;
    ppu_p_write(value);
    ppu.vram_addr = tmp;
}

uint16_t normalize_address(uint16_t address) {
    address &= 0x3FFF;
    // address = mirror_nameTable(address);
    if (address >= 0x2000 && address <= 0x3EFF) {
        address &= ~0x1000;
    } else if (address >= 0x3F00 && address <= 0x3FFF) {
        address &= ~0x00E0;
    }

    if (address == 0x3F10 || address == 0x3F14 || address == 0x3F18 || address == 0x3F1C) {
        address &= ~0xF0;
    }
    return address;
}

uint16_t mirror_nameTable(uint16_t address) {
    switch(mmc_mirror()){
        case Horizontal:
            if(address >= 0x2400 && address <= 0x27FF) {
                return address - 0x0400;
            } else if (address >= 0x2800 && address <= 0x2BFF) {
                return address - 0x0400;
            } else if (address >= 0x2C00 && address <= 0x2FFF) {
                return address - 0x0800;
            }
            break;
        case Vertical:
            if (address >= 0x2800 && address <= 0x2FFF) {
                return address - 0x0800;
            }
            break;
        case SingleScreen:
        case SingleScreenLowerBank:
            if (address >= 0x2000 && address <= 0x2FFF) {
                return (address & 0x03FF) | 0x2000;
            }
            break;
        case SingleScreenUpperBank:
            if (address >= 0x2000 && address <= 0x2FFF) {
                return (address & 0x03FF) | 0x2400;
            }
            break;
        case FourScreen:
            break;
    }
    return address;
}

uint8_t ppu_read_register(uint16_t address) {
    if(address == 0x2002) {
	return read_STATUS();
    } else if(address == 0x2004) {
        return read_OAMDATA();
    } else if(address == 0x2007) {
        return read_VRAMDATA();
    }
    return 0;
}

void ppu_write_register(uint16_t address, uint8_t value) {
    if(address == 0x2000) {
        write_CTRL(value);
    } else if(address == 0x2001) {
        write_MASK(value);
    } else if (address == 0x2003) {
        write_OAMADDR(value);
    } else if (address == 0x2004) {
        write_OAMDATA(value);
    } else if (address == 0x2005) {
        write_SCROLL(value);
    } else if (address == 0x2006) {
        write_VRAMADDR(value);
    } else if (address == 0x2007) {
        write_VRAMDATA(value);
    } else if (address == 0x4014) {
        write_OAMDMA(value);
    }
}

uint8_t read_STATUS() {
    uint8_t val = ppu.PPUSTATUS;
    ppu.vram_access_flip = false;
    ppu.PPUSTATUS &= ~(0x80);
    return val;
}

uint8_t read_OAMDATA() {
    return ppu.spram[ppu.sprite_addr];
}

uint8_t read_VRAMDATA() {
    uint8_t val = 0;
    if ( ppu.vram_addr >= 0x0000 && ppu.vram_addr <= 0x3EFF) {
        val = ppu.vram_data_latch;
        ppu.vram_data_latch = ppu_p_read();
    } else {
        ppu.vram_data_latch = ppu_read(normalize_address(ppu.vram_addr & (~0x1000)));
        val = ppu_p_read();
    }
    ppu.vram_addr += (ppu.PPUCTRL & 0x04 ? 32 :1);
    return val;
}

void write_CTRL(uint8_t value) {
    ppu.vram_latch = (ppu.vram_latch & ~(3 << 10)) | ((value & 3) << 10);
    ppu.PPUCTRL = value;
}

void write_MASK(uint8_t value) {
    ppu.PPUMASK = value;
}

void write_OAMADDR(uint8_t value) {
    ppu.sprite_addr = value;
}

void write_OAMDATA(uint8_t value) {
    ppu.spram[ppu.sprite_addr] = value;
    ppu.sprite_addr++;
}

void write_SCROLL(uint8_t value) {
    if (!ppu.vram_access_flip) {
        ppu.PPUSCROLL = value << 8;
        ppu.scroll_x = value & 0x07;
        ppu.vram_latch = (ppu.vram_latch & ~0x1F) | ((value >> 3) & 0x1F);
    } else {
        ppu.PPUSCROLL |= value;
        ppu.scroll_y = value;
        ppu.vram_latch = (ppu.vram_latch & ~(0x1F <<5)) | (((value >> 3) & 0x1F) << 5);
        ppu.vram_latch = (ppu.vram_latch & ~(0x07 << 12)) | ((value & 0x07) << 12);
    }
    ppu.vram_access_flip = !ppu.vram_data_latch;
}

void write_VRAMADDR(uint8_t value) {
    if(!ppu.vram_access_flip) {
        ppu.vram_addr = value << 8;
        ppu.vram_latch = (ppu.vram_latch & 0xFF) | ((value & 0x3F) << 8);
    } else {
        ppu.vram_latch = (ppu.vram_latch & ~0xFF) | value;
        ppu.vram_addr = ppu.vram_latch;
    }
    ppu.vram_access_flip = !ppu.vram_data_latch;
}

void write_VRAMDATA(uint8_t value) {
    ppu_p_write(value);
    ppu.vram_addr += (ppu.PPUCTRL & 0x04 ? 32 : 1);
}

void write_OAMDMA(uint8_t value) {
    uint16_t base_addr = value * PPU_SPRT_RAM_SIZE;
    int i = 0;

    while(i < PPU_SPRT_RAM_SIZE) {
        ppu.spram[(ppu.sprite_addr + i) % PPU_SPRT_RAM_SIZE] = read(base_addr + i);
        i++;
    }
    ppu.ppu_cycle += PPU_DMA_CYCLES * PER_CPU_CYCLE;
}
