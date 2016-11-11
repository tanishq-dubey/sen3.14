#include "ppu.h"

void init_ppu()
{
    ppupack.PPUSCROLL_WRITE_NUM = 0;
    ppupack.PPUADDR_WRITE_NUM   = 0;
    //powerup state found at https://wiki.nesdev.com/w/index.php/PPU_power_up_state#Best_practice
    write(0x2000, 0x00);
    write(0x2001, 0x00);
    write(0x2003, 0x00);
    write(0x2004, 0x00);
    write(0x2005, 0x00);
    write(0x2005, 0x00);
    write(0x2006, 0x00);
    write(0x2006, 0x00);
    write(0x2007, 0x00);

    uint8_t PPUSTATUS = read(0x2002);
    ppupack.PPUSTATUS = PPUSTATUS & 0xA0;
    write(0x2002, ppupack.PPUSTATUS);

    ppupack.PPU_MEMORY = (char*)malloc(sizeof(char)*0x10000);
    if(debug) {
        debug_print("%s","\033[32;1mPPU Register Data:\033[0m\n");
        int i;
        for(i = 0; i < 8; i++) {
            debug_print("0x200%d: 0x%02x\n", i, read(0x2000+i));
        }
    }
} 

void reset_ppu()
{
    write(0x2000, 0x00);
    write(0x2001, 0x00);
    write(0x2005, 0x00);
    write(0x2005, 0x00);
    write(0x2007, 0x00);
    uint8_t PPUSTATUS = read(0x2002);
    PPUSTATUS = PPUSTATUS & 0x80;
    write(0x2002, PPUSTATUS);
}

void ppu_write(uint16_t address, uint8_t value) {
    if (address == 0x2000) {
        ppupack.PPUCTRL = value;
    } else if (address == 0x2001) {
        ppupack.PPUMASK = value;
    } else if (address == 0x2003) {
        ppupack.OAMADDR = value;
    } else if (address == 0x2004) {
        ppupack.OAMDATA = value;
        ppupack.OAMADDR++;
    } else if (address == 0x2005) {
        if (ppupack.PPUSCROLL_WRITE_NUM == 0) {
            uint16_t temp = value;
            ppupack.PPUSCROLL |= temp << 8;
            ppupack.PPUSCROLL_WRITE_NUM = 1;
        } else {
            ppupack.PPUSCROLL |= value;
            ppupack.PPUSCROLL_WRITE_NUM = 0;
        }
    } else if (address == 0x2006) {
        if (ppupack.PPUADDR_WRITE_NUM == 0) {
            uint16_t temp = value;
            ppupack.PPUADDR |= temp << 8;
            ppupack.PPUADDR_WRITE_NUM = 1;
        } else {
            ppupack.PPUADDR |= value;
            ppupack.PPUADDR_WRITE_NUM = 0;
        }
    } else if (address == 0x2007) {
        ppupack.PPUDATA = value;
    }
}
