#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    // Input validation
    int debug = 0;
    if(argc == 1 || argc > 3) {
        printf("Invalid number of arguments! (%s, %s::%d)\n", __FILE__, __func__, __LINE__);
        return 0;
    }
    if(argc == 3) {
        if (strcmp(argv[2], "-v") == 0) {
            debug = 1; 
        } else {
            printf("Invalid arguments! (%s, %s::%d)\n", __FILE__, __func__, __LINE__);
        }
    }
    FILE* fp = fopen(argv[1], "rb");
    // ROM Validation:
    if(fgetc(fp) != 'N' && fgetc(fp) != 'E' && fgetc(fp) != 'S' && fgetc(fp) != '\32') {
        printf("Invalid ROM file, header does not match (%s, %s::%d) -> %s\n", __FILE__, __func__, __LINE__, argv[1]);
    }

    // Get header file information: https://wiki.nesdev.com/w/index.php/INES
    unsigned char prg_rom_size = fgetc(fp);
    unsigned char chr_rom_size = fgetc(fp);
    unsigned char flag_six     = fgetc(fp);
    unsigned char flag_seven   = fgetc(fp);
    if(debug) {
        printf("PRG ROM Size: %d\n", prg_rom_size);
        printf("CHR ROM Size: %d\n", chr_rom_size);
        printf("Flag 6: 0x%02X\n", flag_six);
        printf("Flag 7: 0x%02X\n", flag_seven);
    }

    int i;

    // Advance file pointer by 8 spaces
   for (i = 0; i < 8; i++){
        fgetc(fp);
    }

    fclose(fp);
}
