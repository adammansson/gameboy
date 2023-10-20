#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>

typedef struct memory {
	uint8_t data[65536];
} memory_t;

void memory_init(memory_t *memory);

uint8_t memory_read(memory_t *memory, uint16_t address);

#endif
