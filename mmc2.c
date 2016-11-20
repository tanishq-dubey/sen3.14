#include "mmc2.h"

void mapper_two_init() {
	mapper_two.prg_banks_total = get_prg_banks();
	mapper_two.prg_bank_one = 0;
	mapper_two.prg_bank_two = mapper_two.prg_banks_total - 1;
}

uint8_t mapper_two_read(uint16_t address) {
	if (address < 0x2000) {
		return get_chr_mem()[address];
	} else if (address >= 0xC000) {
		int index = mapper_two.prg_bank_two * 0x4000 + (int)(address-0xC000);
		return get_prg_mem()[index];
	} else if (address >= 0x8000) {
		int index = mapper_two.prg_bank_one * 0x4000 + (int)(address-0x8000);
		return get_prg_mem()[index];
	} else if (address >= 0x6000) {
		int index = (int)address - 0x6000;
		return get_save_ram()[index];
	}
	return 0;
}

void mapper_two_write(uint16_t address, uint8_t value) {
	if (address < 0x2000) {
		get_chr_mem()[address] = value;
	} else if (address >= 0x8000) {
		mapper_two.prg_bank_one = (int)(value) % mapper_two.prg_banks_total;
	} else if (address >= 0x6000) {
		int index = (int)(address) - 0x6000;
		get_save_ram()[index] = value;
	}
}