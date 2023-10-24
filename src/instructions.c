#include "instructions.h"
#include "cpu.h"
#include "memory.h"

#include <stdio.h>
#include <stdint.h>

void push_register_pair(cpu_t *cpu, memory_t *memory, uint8_t higher, uint8_t lower)
{
	memory_write(memory, cpu->SP - 1, higher);
	memory_write(memory, cpu->SP - 2, lower);
	cpu->SP -= 2;
}

void pop_register_pair(cpu_t *cpu, memory_t *memory, uint8_t *higher, uint8_t *lower)
{
	*higher = memory_read(memory, cpu->SP);
	*lower = memory_read(memory, cpu->SP + 1);
	cpu->SP += 2;
}

/*
void execute_instruction(cpu_t *cpu, memory_t *memory)
{
	uint8_t opcode;
	uint8_t data0;
	uint8_t data1;
	uint8_t code;
	uint8_t destination;
	uint8_t source;
	uint8_t *destination_register;
	uint8_t *source_register;
	uint8_t register_pair_code;
	uint16_t address;
	uint16_t old_address;

	opcode = memory_read(memory, cpu->PC);
	cpu->PC++;

	code = (opcode & 0b11000000) >> 6;
	destination = (opcode & 0b00111000) >> 3;
	source = opcode & 0b00000111;

	printf("%x\n", opcode);
	printf("%x\n", code);
	printf("%x\n", destination);
	printf("%x\n", source);

	switch (opcode)
	{
	case 0b00110110:
		address = (cpu->H << 8) | cpu->L;
		data0 = memory_read(memory, cpu->PC);
		cpu->PC++;

		memory_write(memory, address, data0);
		break;
	case 0b00001010:
		address = (cpu->B << 8) | cpu->C;
		data0 = memory_read(memory, address);

		cpu->A = data0;
		break;
	case 0b00011010:
		address = (cpu->D << 8) | cpu->E;
		data0 = memory_read(memory, address);

		cpu->A = data0;
		break;
	case 0b11110010:
		address = 0xFF00 | cpu->C;
		data0 = memory_read(memory, address);

		cpu->A = data0;
		break;
	case 0b11100010:
		address = 0xFF00 | cpu->C;

		memory_write(memory, address, cpu->A);
		break;
	case 0b11110000:
		data0 = memory_read(memory, cpu->PC);
		cpu->PC++;
		address = 0xFF00 | data0;
		data0 = memory_read(memory, address);

		cpu->A = data0;
		break;
	case 0b11100000:
		data0 = memory_read(memory, cpu->PC);
		cpu->PC++;
		address = 0xFF00 | data0;

		memory_write(memory, address, cpu->A);
		break;
	case 0b11111010:
		address = (memory_read(memory, cpu->PC) << 8) | memory_read(memory, cpu->PC + 1);
		cpu->PC += 2;
		data0 = memory_read(memory, address);

		cpu->A = data0;
		break;
	case 0b11101010:
		address = (memory_read(memory, cpu->PC) << 8) | memory_read(memory, cpu->PC + 1);
		cpu->PC += 2;

		memory_write(memory, address, cpu->A);
		break;
	case 0b00101010:
		address = (cpu->H << 8) | cpu->L;
		data0 = memory_read(memory, address);

		cpu->A = data0;
		address++;
		cpu->H = (address >> 8);
		cpu->L = address;
		break;
	case 0b00111010:
		address = (cpu->H << 8) | cpu->L;
		data0 = memory_read(memory, address);

		cpu->A = data0;
		address--;
		cpu->H = (address >> 8);
		cpu->L = address;
		break;
	case 0b00000010:
		address = (cpu->B << 8) | cpu->C;

		memory_write(memory, address, cpu->A);
		break;
	case 0b00010010:
		address = (cpu->D << 8) | cpu->E;

		memory_write(memory, address, cpu->A);
		break;
	case 0b00100010:
		address = (cpu->H << 8) | cpu->L;

		memory_write(memory, address, cpu->A);
		address++;
		cpu->H = (address >> 8);
		cpu->L = address;
		break;
	case 0b00110010:
		address = (cpu->H << 8) | cpu->L;

		memory_write(memory, address, cpu->A);
		address--;
		cpu->H = (address >> 8);
		cpu->L = address;
		break;
	case 0b11111001:
		cpu->PC = (cpu->H << 8) | cpu->L;
		break;
	case 0b11111000:
		data0 = memory_read(memory, cpu->PC);
		cpu->PC++;

		if (cpu->SP + data0 < cpu->SP)
			cpu->F |= 1 << CY_FLAG;
		if (cpu->SP + data0 > 0xFFF)
			cpu->F |= 1 << H_FLAG;
		cpu->F &= ~(1 << Z_FLAG);
		cpu->F &= ~(1 << N_FLAG);

		address = cpu->SP + data0;
		cpu->H = (address >> 8);
		cpu->L = address;
		break;
	case 0b00001000:
		address = (memory_read(memory, cpu->PC) << 8) | memory_read(memory, cpu->PC + 1);
		cpu->PC += 2;

		memory_write(memory, address, cpu->SP);
		memory_write(memory, address + 1, cpu->SP >> 8);
		break;
	default:
		destination_register = cpu_register_from_code(cpu, destination);
		source_register = cpu_register_from_code(cpu, source);
		register_pair_code = (opcode | 0b00110000) >> 4;

		if (code == 0b01 && destination != 0b110 && source != 0b110)
		{
			*destination_register = *source_register;
		}
		else if (code == 0b00 && destination != 0b110 && source == 0b110)
		{
			data0 = memory_read(memory, cpu->PC);
			cpu->PC++;

			*destination_register = data0;
		}
		else if (code == 0b01 && destination != 0b110 && source == 0b110)
		{
			address = (cpu->H << 8) | cpu->L;
			data0 = memory_read(memory, address);

			*destination_register = data0;
		}
		else if (code == 0b01 && destination == 0b110 && source != 0b110)
		{
			address = (cpu->H << 8) | cpu->L;

			memory_write(memory, address, *source_register);
		}
		else if ((opcode | 0b11001111) == 0b00000001)
		{
			data0 = memory_read(memory, cpu->PC);
			cpu->PC++;
			data1 = memory_read(memory, cpu->PC);
			cpu->PC++;

			switch (register_pair_code)
			{
			case 0b00:
				cpu->B = data0;
				cpu->C = data1;
				break;
			case 0b01:
				cpu->D = data0;
				cpu->E = data1;
				break;
			case 0b10:
				cpu->H = data0;
				cpu->L = data1;
				break;
			default:
				cpu->SP = (data0 << 8) | data1;
				break;
			}
		}
		else if ((opcode | 0b11001111) == 0b11000101)
		{
			switch (register_pair_code)
			{
			case 0b00:
				push_register_pair(cpu, memory, cpu->B, cpu->C);
				break;
			case 0b01:
				push_register_pair(cpu, memory, cpu->D, cpu->E);
				break;
			case 0b10:
				push_register_pair(cpu, memory, cpu->H, cpu->L);
				break;
			default:
				push_register_pair(cpu, memory, cpu->A, cpu->F);
				break;
			}
		}
		else if ((opcode | 0b11001111) == 0b11000001)
		{
			switch (register_pair_code)
			{
			case 0b00:
				pop_register_pair(cpu, memory, &(cpu->B), &(cpu->C));
				break;
			case 0b01:
				pop_register_pair(cpu, memory, &(cpu->D), &(cpu->E));
				break;
			case 0b10:
				pop_register_pair(cpu, memory, &(cpu->H), &(cpu->L));
				break;
			default:
				pop_register_pair(cpu, memory, &(cpu->A), &(cpu->F));
				break;
			}
		}
		else
		{
			printf("unhandled opcode %x\n", opcode);
		}
	}
}
*/