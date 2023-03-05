/*
 * GccApplication1.c
 *
 * Created: 14/2/2023 12:54:27 pm
 * Author : Reyazul
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint16_t INSTRUCTIONS[1<<8] = {
	0x306f,
	0x3023,
	0x5032,
	0x3334,
	0x6231,
	0xc234,
	0xd135,
	0x9323,
	0x1331,
	0xa341,
	0x21a0,
	0x0441,
	0xf334,
	0x5661,
	0x9620,
	0x5661,
	0x9630,
	0x2190,
	0x8131,
	0x7531,
	0x4225,
	0xf630,
	0x3661,
	0xb352,
	0x21a0,
	0xe138

};

int main(void)
{
	// Some pins of PORTC can not be used for I/O directly.
	// turn of JTAG to use them
	// o write a 1 to the JTD bit twice consecutively to turn it off
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRB = 0x00;	// input pc
	
	// Instruction : D[7:0]C[7:0]
	DDRA = 0xFF;	// lower 8-bits of instruction
	DDRC = 0xFF;	// upper 8-bits of instruction
	
	uint8_t pc = -1;
	uint16_t instruction;
	/* Replace with your application code */
	while (1)
	{
		if (PINB != pc) {
			pc = PINB;
			instruction = INSTRUCTIONS[pc];
			PORTA = (uint8_t) instruction;
			PORTC = (uint8_t) (instruction >> 8);
			_delay_ms(50);
		}
	}
}


