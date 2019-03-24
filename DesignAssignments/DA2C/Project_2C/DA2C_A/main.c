/*
 * DA2C_A.c
 *
 * Created: 3/22/2019 11:09:35 PM
 * Author : Cody Hudson
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int Count = 0;
int main(void)
{
	DDRB |= (1<<DDB2);		//SETS DIRECTION OF PORT B2 AS OUTPUT
	TCNT0 = 0x8F;			//SETS HIGHEST VALUE FOR TIMMER 0x8F
	TCCR0A = 0x00;			//SETS TIMMER TO BE NORMAL MODE
	TCCR0B = 0x05;			//SETS PRESCALLER TO 1024
	while(1){
		while((TIFR0 & 0x01) == 0)	//WHEN FLAG ISNT SET STAY HERE
		;
		TCNT0 = 0x8F;		//SET TNCT BACK UP TO 0x8F
		TIFR0 = 0x01;		//CLEAR FLAG
		Count++;			//INCRIMENT COUNTER
		if(Count == 60)		//40% OF THE TIME DO THIS
			PORTB &= (0<<PORTB2);	//SET WAVEFORM LOW
		if(Count == 100){	//60% OF THE TIME DO THIS
			PORTB |= (1<<PORTB2);	//SET WAVEFORM HIGH
			Count = 0;		//SET COUNTER BACK TO 0
		}
	}
}

