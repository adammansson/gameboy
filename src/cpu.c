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

	cpu->PC = 0;
}

void cpu_print(cpu_t *cpu)
{
	printf("Print registers:\n");
	printf("A: %x\n", cpu->A);
	printf("B: %x\n", cpu->B);
	printf("C: %x\n", cpu->C);
	printf("D: %x\n", cpu->D);
	printf("E: %x\n", cpu->E);
	printf("H: %x\n", cpu->H);
	printf("L: %x\n", cpu->L);
}
