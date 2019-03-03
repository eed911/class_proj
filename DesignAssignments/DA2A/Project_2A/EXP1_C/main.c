/*
 * EXP1_C.c
 *
 * Created: 3/2/2019 1:34:56 PM
 * Author : hudsoc1
 */ 

#define F_CPU 16000000UL			//SETS THE FREQUECY OF MY OPERTION FOR DELAYS
#include <avr/io.h>		
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<PORTB2);			//INITIALIZES DIRECITON OF PORTB.2 AS AN OUTPUT
	while (1)
	{
		PORTB |= (1<<PORTB2);		//SETS PORTB.2 HIGH
		_delay_ms(435);				//DELAY OF 435ms
		PORTB &= ~ (1<<PORTB2);		//SETS PORTB.2 LOW
		_delay_ms(290);				//DLEAY OF 290ms
	}

}