/*
 * DA2C_INT_NORMAL_A.c
 *
 * Created: 3/23/2019 1:41:52 AM
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
	TIMSK0 |= (1<<TOIE0);	//THE INTERRUPT TO ACTIVATE WHEN TIMER 0 HAS OVERFLOW
	sei();					//SETS GLOBAL INTERRUPT
	TCNT0 = 0x8F;			//SETS TCNT0 TO 0x8F
	TCCR0A = 0x00;			//SETS TIMMER 0 TO NORMAL MODE
	TCCR0B = 0x05;			//SETS PRESCALLER TO 1024
	while(1);
}
ISR (TIMER0_OVF_vect){		//TV0V INTERUPT SUBROUTINE
	while(1){
		while((TIFR0 & 0x01) == 0)	//WHILE FLAG ISNT SET STAY HERE
		;
		TCNT0 = 0x8F;		//SET TCNT0 BACK TO 0x8F
		TIFR0 = 0x01;		//CLEAR FLAG
		Count++;			//INCRIMENT TIMMER
		if(Count == 60)		//40% OF THE TIME DO THIS
			PORTB &= (0<<PORTB2);	//SET WAVEFORM LOW
		if(Count == 100){	//60% OF THE TIME DO THIS
			PORTB |= (1<<PORTB2);	//SET WAVEFORM HIGH
			Count = 0;		//SET COUNTER BACK TO 0
		}
	}
}

