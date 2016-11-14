#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game.h"
#include "memory.h"
#include "ppu.h"
#include "cpu.h"
#include "mmc.h"

#define debug 1


#define debug_print(fmt, ...) \
    do { if (debug) fprintf(stderr, "\033[33m%s:%d:%s()\033[0m: " fmt, __FILE__, \
            __LINE__, __func__, __VA_ARGS__); } while (0)

int main();

#endif /* MAIN_H */
