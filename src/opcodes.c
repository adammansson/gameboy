#include "opcodes.h"

#include "cpu.h"
#include "memory.h"
#include "instructions.h"

void execute_instruction(cpu_t *cpu, memory_t *memory)
{
	uint8_t opcode;

	opcode = memory_read(memory, cpu->PC);
	cpu->PC++;

	switch (opcode)
	{
	case 0x00: // NOP
		break;
	case 0x01: // LD BC,nn
		break;
	case 0x02: // LD (BC),A
		break;
	case 0x03: // INC BC
		break;
	case 0xC1: // POP BC
		pop_register_pair(cpu, memory, &cpu->B, &cpu->C);
		break;
	case 0xC5: // PUSH BC
		push_register_pair(cpu, memory, &cpu->B, &cpu->C);
		break;
	case 0xD1: // POP DE
		pop_register_pair(cpu, memory, &cpu->D, &cpu->E);
		break;
	case 0xD5: // PUSH DE
		push_register_pair(cpu, memory, &cpu->D, &cpu->E);
		break;
	case 0xE1: // POP HL
		pop_register_pair(cpu, memory, &cpu->H, &cpu->L);
		break;
	case 0xE5: // PUSH HL
		push_register_pair(cpu, memory, &cpu->H, &cpu->L);
		break;
	case 0xF1: // POP AF
		pop_register_pair(cpu, memory, &cpu->A, cpu->F);
		break;
	case 0xF5: // PUSH AF
		push_register_pair(cpu, memory, &cpu->A, &cpu->F);
		break;
	default:
		break;
	}
}