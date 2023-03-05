/*
 * ALU.c
 *
 * Created: 12/2/2023 12:48:46 am
 * Author : Reyazul
 */ 

#include <avr/io.h>
#define F_CPU 1000000 // Clock Frequency (need testing)
#include <util/delay.h>


int main(void)
{
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD); //make port C usable for I/O

	DDRA = 0b00000000;	
	PORTA = 0xFF;			// A(0-3), B(4-7) input
	DDRB = 0b11111000;				// ALUOp (0-2) input
	DDRD = 0b10001111;				// D(7) - Zero Flag | D(0-3) - Output

		uint8_t control_bits;
		uint8_t in1, in2, out;  // unsigned single-byte 

		while (1)
		{
			control_bits = PINB & 0b00000111;  //copying ALUOp in control_bits

			in1 = PINA & 0b00001111;
			in2 = (PINA & 0b11110000) >> 4;  //copied and shifted to lsb
			out = 0;

			if(control_bits == 0) {
				out = in1 + in2;
				} else if(control_bits == 1){
				out = in1 - in2;
				} else if(control_bits == 2) {
				out = in1 & in2;
				} else if(control_bits == 3) {
				out = in1 | in2;
				} else if(control_bits == 4) {
				out = ~(in1 | in2);
				} else if(control_bits == 5) {
				out = in1 << in2;
				} else if(control_bits == 6) {
				out = in1 >> in2;
			}

			out = out & 0b00001111;  //output
			if(!out) {
				out = out | 0b10000000;  //enable 0 bit if out is 0
			}

			PORTD = out;   //D7 is zero flag
		}

}

