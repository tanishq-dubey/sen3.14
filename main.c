#include "main.h"

int main (int argc, char** argv) {
    // Input validation
    if (argc == 1 || argc > 2) {
        debug_print("%s", "Invalid number of arguments!");
        return 0;
    }
    FILE* fp = fopen(argv[1], "rb");
    // Load ROM into dynamic memory:
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);
    uint8_t *ROM = (uint8_t *)malloc(fsize +1);
    fread(ROM, fsize, 1, fp);
    fclose(fp);

    init_game(ROM);
    init_memory();
    init_ppu();
    init_cpu();

   free(ROM);
}
