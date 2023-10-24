#include "memory.h"

#include <stdint.h>
#include <string.h>

void memory_init(memory_t *memory)
{
	memset(&(memory->data), 0, MEMORY_SIZE);
	memory->data[0] = 0x78;

	memory->data[1] = 0x0E;
	memory->data[2] = 0x69;

	memory->data[0xFF00] = 0x12;
	memory->data[3] = 0b00101010;

	memory->data[4] = 0b00001000;
	memory->data[5] = 0xC1;
	memory->data[6] = 0x00;
}

uint8_t memory_read(memory_t *memory, uint16_t address)
{
	return memory->data[address];
}

void memory_write(memory_t *memory, uint16_t address, uint8_t data)
{
	memory->data[address] = data;
}
