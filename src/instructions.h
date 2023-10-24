#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include "cpu.h"
#include "memory.h"

#include <stdint.h>

void push_register_pair(cpu_t *cpu, memory_t *memory, uint8_t higher, uint8_t lower);

void pop_register_pair(cpu_t *cpu, memory_t *memory, uint8_t *higher, uint8_t *lower);

#endif
