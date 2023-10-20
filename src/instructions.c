#include "instructions.h"
#include "cpu.h"
#include "memory.h"

#include <stdio.h>
#include <stdint.h>

void execute_instruction(cpu_t *cpu, memory_t *memory)
{
	uint8_t opcode, n;

	opcode = memory_read(memory, cpu->PC);
	cpu->PC++;

	switch(opcode)
	{
		case LD_AA:
			break;
		case LD_AB:
			cpu->A = cpu->B;
			break;
		case LD_AC:
			cpu->A = cpu->C;
			break;
		case LD_AD:
			cpu->A = cpu->D;
			break;
		case LD_AE:
			cpu->A = cpu->E;
			break;
		case LD_AH:
			cpu->A = cpu->H;
			break;
		case LD_AL:
			cpu->A = cpu->L;
			break;

		case LD_BA:
			cpu->B = cpu->A;
			break;
		case LD_BB:
			break;
		case LD_BC:
			cpu->B = cpu->C;
			break;
		case LD_BD:
			cpu->B = cpu->D;
			break;
		case LD_BE:
			cpu->B = cpu->E;
			break;
		case LD_BH:
			cpu->B = cpu->H;
			break;
		case LD_BL:
			cpu->B = cpu->L;
			break;

		case LD_CA:
			cpu->C = cpu->A;
			break;
		case LD_CB:
			cpu->C = cpu->B;
			break;
		case LD_CC:
			break;
		case LD_CD:
			cpu->C = cpu->D;
			break;
		case LD_CE:
			cpu->C = cpu->E;
			break;
		case LD_CH:
			cpu->C = cpu->H;
			break;
		case LD_CL:
			cpu->C = cpu->L;
			break;

		case LD_DA:
			cpu->D = cpu->A;
			break;
		case LD_DB:
			cpu->D = cpu->B;
			break;
		case LD_DC:
			cpu->D = cpu->C;
			break;
		case LD_DD:
			break;
		case LD_DE:
			cpu->D = cpu->E;
			break;
		case LD_DH:
			cpu->D = cpu->H;
			break;
		case LD_DL:
			cpu->D = cpu->L;
			break;

		case LD_AN:
			n = memory_read(memory, cpu->PC);
			cpu->PC++;
			cpu->A = n;
			break;
		case LD_BN:
			n = memory_read(memory, cpu->PC);
			cpu->PC++;
			cpu->B = n;
			break;
		case LD_CN:
			n = memory_read(memory, cpu->PC);
			cpu->PC++;
			cpu->C = n;
			break;
		case LD_DN:
			n = memory_read(memory, cpu->PC);
			cpu->PC++;
			cpu->D = n;
			break;
		case LD_EN:
			n = memory_read(memory, cpu->PC);
			cpu->PC++;
			cpu->E = n;
			break;
		case LD_HN:
			n = memory_read(memory, cpu->PC);
			cpu->PC++;
			cpu->H = n;
			break;
		case LD_LN:
			n = memory_read(memory, cpu->PC);
			cpu->PC++;
			cpu->L = n;
			break;

		default:
			printf("unhandled opcode %x\n", opcode);
			break;
	}
}
