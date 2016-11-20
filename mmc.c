#include "mmc.h"

void init_mmc() {
    switch(get_mapper()) {
        case 0:
            debug_print("%s", "Mapper 0 Found\n");
            mapper_two_init();
            break;
        case 1:
            debug_print("%s", "Mapper 1 Found\n");
            mapper_one_init();
        case 2:
            debug_print("%s", "Mapper 2 Found\n");
            mapper_two_init();
            break;
        default:
            debug_print("%s", "Invalid or unsupported mapper type!\n");
            exit(0);
    }
}

void mmc_write(uint16_t address, uint8_t value) {
    switch(get_mapper()) {
        case 0:
            mapper_two_write(address, value);
            break;
        case 1:
            mapper_one_write(address, value);
            break;
        case 2:
            mapper_two_write(address, value);
            break;
    }
}

uint8_t mmc_read(uint16_t address) {
    switch(get_mapper()) {
        case 0:
            return mapper_two_read(address);
        case 1:
            return mapper_one_read(address);
        case 2:
            return mapper_two_read(address);
    }
    return 0;
}
