#include "main.h"

int main (int argc, char** argv) {
    // Input validation
    if (argc == 1 || argc > 3) {
        printf("Invalid number of arguments! (%s, %s::%d)\n", __FILE__, __func__, __LINE__);
        return 0;
    }
    if (argc == 3) {
        if (strcmp(argv[2], "-v") == 0) {
            //debug = 1; 
        } else {
            printf("Invalid arguments! (%s, %s::%d)\n", __FILE__, __func__, __LINE__);
        }
    }
    FILE* fp = fopen(argv[1], "rb");
    // Load ROM into dynamic memory:
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);
    uint8_t *ROM = (uint8_t *)malloc(fsize +1);
    fread(ROM, fsize, 1, fp);
    fclose(fp);
    
    int i;
    if (debug) {
        for(i = 0; i < 8; i++){
            printf("0x%02X ", ROM[i]);
        }
        printf("\n");
    }


    init_game(ROM);
    init_memory();
    init_ppu();

   free(ROM);
}
