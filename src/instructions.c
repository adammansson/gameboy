#include "instructions.h"
#include "cpu.h"
#include "memory.h"

#include <stdio.h>
#include <stdint.h>

void execute_instruction(cpu_t *cpu, memory_t *memory)
{
	uint8_t opcode, data, code, destination, source, *destination_register, *source_register;
	uint16_t address;

	opcode = memory_read(memory, cpu->PC);
	cpu->PC++;

	code = (opcode & 0b11000000) >> 6;
	destination = (opcode & 0b00111000) >> 3;
	source = opcode & 0b00000111;

	printf("%x\n", opcode);
	printf("%x\n", code);
	printf("%x\n", destination);
	printf("%x\n", source);

	switch(opcode)
	{
		case 0b00110110:
			address = (cpu->H << 8) | cpu->L;
			data = memory_read(memory, cpu->PC);
			cpu->PC++;

			memory_write(memory, address, data);
			break;
		case 0b00001010:
			address = (cpu->B << 8) | cpu->C;
			data = memory_read(memory, address);

			cpu->A = data;
			break;
		case 0b00011010:
			address = (cpu->D << 8) | cpu->E;
			data = memory_read(memory, address);

			cpu->A = data;
			break;
		case 0b11110010:
			address = 0xFF00 | cpu->C;
			data = memory_read(memory, address);

			cpu->A = data;
			break;
		case 0b11100010:
			address = 0xFF00 | cpu->C;

			memory_write(memory, address, cpu->A);
			break;
		case 0b11110000:
			data = memory_read(memory, cpu->PC);
			cpu->PC++;
			address = 0xFF00 | data;
			data = memory_read(memory, address);

			cpu->A = data;
			break;
		case 0b11100000:
			data = memory_read(memory, cpu->PC);
			cpu->PC++;
			address = 0xFF00 | data;

			memory_write(memory, address, cpu->A);
			break;
		case 0b11111010:
			address = (memory_read(memory, cpu->PC) << 8) | memory_read(memory, cpu->PC + 1);
			cpu->PC += 2;
			data = memory_read(memory, address);

			cpu->A = data;
			break;
		case 0b11101010:
			address = (memory_read(memory, cpu->PC) << 8) | memory_read(memory, cpu->PC + 1);
			cpu->PC += 2;

			memory_write(memory, address, cpu->A);
			break;
		case 0b00101010:
			address = (cpu->H << 8) | cpu->L;
			data = memory_read(memory, address);

			cpu->A = data;
			address++;
			cpu->H = (address >> 8);
			cpu->L = address;
			break;
		case 0b00111010:
			address = (cpu->H << 8) | cpu->L;
			data = memory_read(memory, address);

			cpu->A = data;
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
		default:
			destination_register = cpu_register_from_code(cpu, destination);
			source_register = cpu_register_from_code(cpu, source);

			if (code == 0b01 && destination != 0b110 && source != 0b110)
			{

				*destination_register = *source_register;
			}
			else if (code == 0b00 && destination != 0b110 && source == 0b110)
			{
				data = memory_read(memory, cpu->PC);
				cpu->PC++;

				*destination_register = data;
			}
			else if (code == 0b01 && destination != 0b110 && source == 0b110)
			{
				address = (cpu->H << 8) | cpu->L;
				data = memory_read(memory, address);

				*destination_register = data;
			}
			else if (code == 0b01 && destination == 0b110 && source != 0b110)
			{
				address = (cpu->H << 8) | cpu->L;

				memory_write(memory, address, *source_register);
			}
			else
			{
				printf("unhandled opcode %x\n", opcode);
			}
	}
}
