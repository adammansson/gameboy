#include "cpu.h"
#include "memory.h"
#include "instructions.h"
#include <stdio.h>

int main()
{
	cpu_t cpu;
	memory_t memory;

	cpu_init(&cpu);
	memory_init(&memory);

	cpu_print(&cpu);

	execute_instruction(&cpu, &memory);
	cpu_print(&cpu);

	execute_instruction(&cpu, &memory);
	cpu_print(&cpu);

	return 0;
}
