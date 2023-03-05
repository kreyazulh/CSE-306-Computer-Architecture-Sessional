/*
* Registers.c
*
* Created: 12/2/2023 1:27:48 pm
* Author : Reyazul
*/

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define WRITE_REG_	0x01
#define CLK_		0x04
#define RESET_		0x02
#define OUTPUT_		0x08

uint8_t REGISTER[8] = {0}; //all registers 0


int main(void)
{
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);

	DDRA = 0b00000000;	// A[3:0] - SrcReg1, A[7:4] - SrcReg2
	DDRB = 0b00000000;	// B[3:0] - DstReg, B[7:4] - Write Data

	DDRC = 0b11111111;	// C[3:0] - $1, C[7:4] - $2
	DDRD = 0b11110000;	// D[0] - WriteReg, D[1] - RESET
	//PORTA = 0xff;
	//PORTB = 0xff;
	uint8_t src, dst_data, last_control = 0, current_control;
	//dstreg, writedata

	while (1)
	{
		src = PINA; //src1,2
		dst_data = PINB;  //dstreg, writedata
		current_control=PIND;

		PORTC = (REGISTER[(src>>4)&0b0111]<<4) | (REGISTER[src&0b0111]);	//read
		_delay_ms(100);
		if (current_control&RESET_) {
			for (uint8_t i=0; i<8; i++) REGISTER[i] = 0;
			_delay_ms(100);
			continue;
		}
		
		if ((current_control^last_control)&CLK_) {							// EDGE
			if ((last_control&CLK_) && (last_control&WRITE_REG_)) {	// NEGATIVE EDGE with WRITE INSTRUCTION
				
				REGISTER[dst_data&0b0111] = (dst_data>>4);							//write
				PORTD = dst_data & 0b11110000;
				//PORTC = (REGISTER[(src>>4)&0b0111]<<4) | (REGISTER[src&0b0111]);	//read
			}
		}
		_delay_ms(100);
		last_control = current_control;
		//}
	}
}


















	

