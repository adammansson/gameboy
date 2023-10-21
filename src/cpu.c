#include "cpu.h"

#include <stdio.h>

void cpu_init(cpu_t *cpu)
{
	cpu->A = 0;
	cpu->B = 0x80;
	cpu->C = 0;
	cpu->D = 0;
	cpu->E = 0;
	cpu->H = 0;
	cpu->L = 0;
	cpu->F = 0;

	cpu->PC = 0;
	cpu->SP = 0;
}

uint8_t *cpu_register_from_code(cpu_t *cpu, uint8_t code)
{
	switch(code)
	{
		case 0b111:
			return &(cpu->A);
		case 0b000:
			return &(cpu->B);
		case 0b001:
			return &(cpu->C);
		case 0b010:
			return &(cpu->D);
		case 0b011:
			return &(cpu->E);
		case 0b100:
			return &(cpu->H);
		case 0b101:
			return &(cpu->L);
		default:
			return NULL;
	}
}

void cpu_print(cpu_t *cpu)
{
	printf("A: %x\n", cpu->A);
	printf("F: %x\n", cpu->F);
	printf("B: %x\n", cpu->B);
	printf("C: %x\n", cpu->C);
	printf("D: %x\n", cpu->D);
	printf("E: %x\n", cpu->E);
	printf("H: %x\n", cpu->H);
	printf("L: %x\n", cpu->L);
	printf("PC: %x\n", cpu->PC);
	printf("SP: %x\n", cpu->SP);
}
