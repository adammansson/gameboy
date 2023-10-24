#ifndef _CPU_H_
#define _CPU_H_

#include <stdint.h>

typedef struct cpu
{
	uint8_t A, F, B, C, D, E, H, L;
	uint16_t PC, SP;
} cpu_t;

enum
{
	Z_FLAG = 7,
	N_FLAG = 6,
	H_FLAG = 5,
	CY_FLAG = 4
};

void cpu_init(cpu_t *cpu);

uint8_t *cpu_register_from_code(cpu_t *cpu, uint8_t code);

void cpu_print(cpu_t *cpu);

#endif
