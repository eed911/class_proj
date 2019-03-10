/*
 * DA2B_C.c
 *
 * Created: 3/8/2019 6:57:05 PM
 * Author : Cody Hudson
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
 	DDRB |= (1<<DDB2);
	PORTB |= (1<<PORTB2);
	DDRD &= (0<<DDD2);
	PORTD |= (1<<PORTD2);
	
	EICRA = 0x2;
	
	EIMSK = (1<<INT0);
	sei ();
	
	while(1);
}
	ISR (INT0_vect)
	{
		PORTB &= (0<<PORTB2);
		_delay_ms(1250);
		PORTB |= (1<<PORTB2);
	}


