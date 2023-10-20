#include "memory.h"
#include <stdint.h>

void memory_init(memory_t *memory)
{
	memory->data[0] = 0x78;
	memory->data[1] = 0x0E;
	memory->data[2] = 0x69;
}

uint8_t memory_read(memory_t *memory, uint16_t address)
{
	return memory->data[address];
}
