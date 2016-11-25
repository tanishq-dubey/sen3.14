#include "mmc1.h"

int calc_prg_offset(int index) {
	if (index >= 0x80) {
		index -= 0x100;
	}
	index %= get_prg_banks();
	int offset = index * 0x1000;
	if (offset < 0) {
		offset += get_prg_banks() * 16384;
	}
	return offset;
}

int calc_chr_offset(int index) {
	if (index >= 0x80) {
		index -= 0x100;
	}
	index %= get_chr_banks();
	int offset = index * 0x1000;
	if (offset < 0) {
		offset += get_chr_banks() * 8192;
	}
	return offset;
}

void calc_all_offsets() {
	switch(mapper_one.prg_mode) {
		case 0:
			mapper_one.prg_bank_offset[0] = calc_prg_offset((int)(mapper_one.prg_bank & 0xFE));
			mapper_one.prg_bank_offset[1] = calc_prg_offset((int)(mapper_one.prg_bank | 0x01));
			break;
		case 1:
			mapper_one.prg_bank_offset[0] = calc_prg_offset((int)(mapper_one.prg_bank & 0xFE));
			mapper_one.prg_bank_offset[1] = calc_prg_offset((int)(mapper_one.prg_bank | 0x01));
			break;
		case 2:
			mapper_one.prg_bank_offset[0] = 0;
			mapper_one.prg_bank_offset[1] = calc_prg_offset((int)mapper_one.prg_bank);
			break;
		case 3:
			mapper_one.prg_bank_offset[0] = calc_prg_offset((int)mapper_one.prg_bank);
			mapper_one.prg_bank_offset[1] =	calc_prg_offset(-1);
			break;
	}

	switch(mapper_one.chr_mode) {
		case 0:
			mapper_one.chr_bank_offset[0] = calc_chr_offset((int)(mapper_one.chr_bank_0 & 0xFE));
			mapper_one.chr_bank_offset[1] = calc_chr_offset((int)(mapper_one.chr_bank_0 | 0x01));
			break;
		case 1:
			mapper_one.chr_bank_offset[0] = calc_chr_offset((int)mapper_one.chr_bank_0);
			mapper_one.chr_bank_offset[1] = calc_chr_offset((int)mapper_one.chr_bank_1);
			break;
	}
}

void write_control(uint8_t value) {
	mapper_one.control_register = value;
	mapper_one.chr_mode = (value >> 4) & 1;
	mapper_one.prg_mode = (value >> 2) & 3;
	uint8_t mirror_mode = value & 3;
	switch(mirror_mode) {
		case 0:
			mapper_one.mirror_mode_internal = SingleScreenLowerBank;
			break;
		case 1:
			mapper_one.mirror_mode_internal = SingleScreenUpperBank;
			break;
		case 2:
			mapper_one.mirror_mode_internal = Vertical;
			break;
		case 4:
                        mapper_one.mirror_mode_internal = Horizontal;
			break;
	}
	calc_all_offsets();
}

void set_chr_bank_0(uint8_t value) {
	mapper_one.chr_bank_0 = value;
	calc_all_offsets();
}

void set_chr_bank_1(uint8_t value) {
	mapper_one.chr_bank_1 = value;
	calc_all_offsets();
}

void set_prg_bank(uint8_t value) {
	mapper_one.prg_bank = value & 0x0F;
	calc_all_offsets();
}

void write_registers(uint16_t address, uint8_t value) {
	if (address <= 0x9FFF) {
		write_control(value);
	} else if (address <= 0xBFFF) {
		set_chr_bank_0(value);
	} else if (address <= 0xDFFF) {
		set_chr_bank_1(value);
	} else if (address <= 0xFFFF) {
		set_prg_bank(value);
	}
}

void load_register(uint16_t address, uint8_t value) {
	if ((value&0x80) == 0x80) {
		mapper_one.shift_register = 0x10;
		write_control(mapper_one.control_register | 0x0C);
	} else {
		uint8_t c = ((mapper_one.shift_register & 1) == 1);
		mapper_one.shift_register >>= 1;
		mapper_one.shift_register |= (value & 1) << 4;
		if (c) {
			write_registers(address, mapper_one.shift_register);
			mapper_one.shift_register = 0x10;
		}
	}
}

void mapper_one_init() {
	mapper_one.shift_register = 0x10;
	mapper_one.prg_bank_offset[1] = calc_prg_offset(-1);
}

void mapper_one_step() {
}

uint8_t mapper_one_read(uint16_t address) {
	if(address < 0x2000) {
		uint16_t bank = address /0x1000;
		uint16_t offset = address % 0x1000;
		return get_chr_mem()[mapper_one.chr_bank_offset[bank] + (int)(offset)];
	} else if (address >= 0x8000) {
		address = address - 0x8000;
		uint16_t bank = address/0x4000;
		uint16_t offset = address % 0x4000;
		return get_prg_mem()[mapper_one.prg_bank_offset[bank] + (int)offset];
	} else if (address >= 0x6000) {
		return get_save_ram()[((int)address) - 0x6000];
	}
	return 0;
}

void mapper_one_write(uint16_t address, uint8_t value) {
	if (address < 0x2000) {
		uint16_t bank = address /0x1000;
		uint16_t offset = address % 0x1000;
		get_chr_mem()[mapper_one.chr_bank_offset[bank] + (int)(offset)] = value;
	} else if (address >= 0x8000) {
		load_register(address, value);
	} else if (address >= 0x6000) {
		get_save_ram()[(int)(address) - 0x6000] = value;
	}
}

uint8_t mapper_one_mirror() {
   return mapper_one.mirror_mode_internal; 
}
