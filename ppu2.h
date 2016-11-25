#ifndef PPU_TWO_H
#define PPU_TWO_H

#include "main.h"
#include "game.h"
#include "cpu.h"
#include "memory.h"
#include "mmc.h"
#include <stdbool.h>

// Defines for screen 
#define SCREEN_W    256
#define SCREEN_H    240
#define SCREEN_C    32  // Screen color depth

// Memory defines: https://wiki.nesdev.com/w/index.php/PPU_memory_map
#define PPU_MAIN_RAM_SIZE   0x4000
#define PPU_SPRT_RAM_SIZE   0x100
#define PPU_DMA_CYCLES      512

// Nametable defines: https://wiki.nesdev.com/w/index.php/PPU_nametables
#define NAMETABLE_SIZE      0x3C0
#define NAMETABLE_WIDTH     0x20
#define NAMETABLE_HEIGHT    0x1E

// Pattern table defines: https://wiki.nesdev.com/w/index.php/PPU_pattern_tables
#define PATTERNTABLE_ADDR_0 0x0000
#define PATTERNTABLE_ADDR_1 0x1000

// Palette table defines: https://wiki.nesdev.com/w/index.php/PPU_palettes
#define PALETTE_BACK_ADDR   0x3F00
#define PALETTE_SPRT_ADDR   0x3F10

// Sprite defines: https://wiki.nesdev.com/w/index.php/PPU_OAM
#define SPRITE_MEM_FIRST    252
#define SPRITE_ZERO_VAL     0
#define SPRITE_MEM_SIZE     4
#define SPRITE_OVERFLOW     8

// http://nesdev.com/2C02%20technical%20reference.TXT
#define PER_CPU_CYCLE       3
#define PPU_PER_SCANL       341

// Scanline defines: https://wiki.nesdev.com/w/index.php/PPU_rendering
#define SCANLINE_R_START    0
#define SCANLINE_R_END      239
#define SCANLINE_VB_START   240
#define SCANLINE_VB_END     259
#define SCANLINE_F_END      261
#define SCANLINE_INIT       241

typedef struct ppu_t {
    uint8_t PPUCTRL;
    uint8_t PPUMASK;
    uint8_t PPUSTATUS;
    uint8_t OAMADDR;
    uint8_t OAMDATA;
    uint16_t PPUSCROLL;
    uint16_t PPUADDR;
    uint8_t PPUDATA;
    uint8_t OAMDMA;

    uint8_t * vram;
    uint8_t * spram;
    uint16_t vram_addr;
    uint8_t vram_data_latch;
    uint16_t vram_latch;
    uint8_t sprite_addr;

    uint8_t scroll_x;
    uint8_t scroll_y;

    bool VBlank;
    bool vram_access_flip;
    bool nmi;
    bool ppu_selection;
    bool background_pattern;
    bool sprite_pattern;
    bool sprite_size;
    
    uint8_t sprite_scanline;
    unsigned long ppu_cycle;
    uint16_t scanline;
    uint16_t prev_scanline;
} ppu_t;

// Static PPU declared
static ppu_t ppu;

// Memory Operations
uint8_t ppu_read(uint16_t address);
void ppu_write(uint16_t address, uint8_t value);
uint16_t normalize_address(uint16_t address);
uint16_t mirror_nameTables(uint16_t address);

// Register write operations
void write_CTRL(uint8_t value);
void write_MASK(uint8_t value);
void write_OAMADDR(uint8_t addr);
void write_OAMDATA(uint8_t value);
void write_SCROLL(uint8_t value);
void write_VRAMADDR(uint8_t value);
void write_VRAMDATA(uint8_t value);
void write_OAMDMA(uint8_t value);

// Register read functions
uint8_t read_STATUS();
uint8_t read_OAMDATA();
uint8_t read_VRAMDATA();

// PPU initalization and runtime
void ppu_init();
void reset_ppu();
void ppu_tick(uint8_t cycles);

// TODO: Rendering functions

#endif
