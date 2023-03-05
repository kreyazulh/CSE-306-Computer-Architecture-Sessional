/*
 * control_unit.c
 *
 * Created: 12/2/2023 1:09:08 am
 * Author : Reyazul
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>


uint16_t CONTROL_ROM[1<<4] = {0x02B,
	0x033,
	0x400,
	0x003,
	0x01B,
	0x00B,
	0x801,
	0x013,
	0x819,
	0x006,
	0x108,
	0x811,
	0x809,
	0x821,
	0x208,
	0x0C3}; //shifted to lsb

int main(void)
{
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRA = 0b11110000; // A[0-3] - Opcode Input
	
	// Control Unit Bits : B(0-7), C(0-3)
	// C[reg_dst[1], jump[1], br_eq[1], br_neq[1], mem_read[1], mem_to_reg[1], ALUOp[3], mem_write[1], ALUSrc[1], reg_write[1]]
	DDRB = 0b11111111;  //output
	DDRC = 0b11111111;
	
	uint8_t opcode = ~0; //111 is no operation
    while (1) 
    {
		if (opcode != (0b00001111 & PINA)) {  //if opcode does not come from 0000-1111
			opcode = (0b00001111 & PINA);
			PORTB = CONTROL_ROM[opcode];  //portb (0-7)
			PORTC = (CONTROL_ROM[opcode] >> 8);  //portc (0-3)
			_delay_ms(50);
		}
    }
}

