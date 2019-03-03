/*
 * EXP2_C.c
 *
 * Created: 3/2/2019 1:47:48 PM
 * Author : hudsoc1
 */ 

#define F_CPU 16000000UL				//SETS THE FREQUENCY OF 16MHz FOR DELAY
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	DDRB |= (1<<PORTB2);				//SETS THE DIRECTION OF PORTB.2 AS OUTPUT
	PORTB |= (1<<PORTB2);				//ENABLE PULL UP RESISTOR OF PORTB.2
	DDRC &= (0 << PORTC2);				//SETS THE DIRECTION OF PORTC.2 AS AN INPUT
	PORTC |= (1 << PORTC2);				//ENABLES PULL UP RESISTOR OF PORTC.2
		while (1)
		{
			if (!(PINC & (1<<PINC2)))	//IF BUTTON IS PUSHED DO THIS
			{
			PORTB &= ~(1<<PORTB2);		//TURN PORTB.2 LED ON
			_delay_ms(1250);			//DELAY FOR 1.25s
			}
			
			else						//IF BUTTON ISNT PUSHED DO THIS
			PORTB |= (1<<PORTB2);		//TURN PORTB.2 LED OFF
		}
		
	return 0;
		
	}