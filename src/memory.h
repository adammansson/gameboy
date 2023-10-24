#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>

#define MEMORY_SIZE 65536

typedef struct memory {
	uint8_t data[MEMORY_SIZE];
} memory_t;

void memory_init(memory_t *memory);

uint8_t memory_read(memory_t *memory, uint16_t address);

void memory_write(memory_t *memory, uint16_t address, uint8_t data);

#endif
