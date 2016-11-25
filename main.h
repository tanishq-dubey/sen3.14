#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "game.h"
#include "memory.h"
#include "ppu.h"
#include "cpu.h"
#include "mmc.h"

#define debug 1
#define true 1
#define false 0


#define debug_print(fmt, ...) \
    do { if (debug) fprintf(stderr, "\033[33m%s:%d:%s()\033[0m: " fmt, __FILE__, \
            __LINE__, __func__, __VA_ARGS__); } while (0)

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
    
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

int main();

#endif /* MAIN_H */
