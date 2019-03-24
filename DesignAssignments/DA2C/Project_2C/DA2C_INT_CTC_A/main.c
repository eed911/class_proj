/*
 * DA2C_INT_CTC_A.c
 *
 * Created: 3/23/2019 1:47:49 AM
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
	OCR0A = 0x71;			//SETS THE COUNTER TO COUNT TO 113
	TIMSK0 |= (1<<OCIE0A);	//SETS INTERRUPT TO ACTIVATE ON A COMPARE OF OCR0A
	sei();					//SETS GLOBAL INTERRUPT
	TCCR0A |= (1<<WGM01);	//SETS TIMMER TO CTC MODE
	TCCR0B = 0x05;			//SETS PRESCALLER TO 1024
	while(1);				//WAITS HERE FOR INTERRUPT
}
ISR (TIMER0_COMPA_vect){	//TIMMER COMPARE SUBROUTINE
	while(1){
		while((TIFR0 & 0x02) == 0)	//WHILE FLAG ISNT SET STAY HERE
		;					
		TIFR0 = 0x02;		//CLEARS FLAG
		Count++;			//INCRIMENTS COUNT
		if(Count == 60)		//40% OF THE PERIOD DO THIS
		PORTB &= (0<<PORTB2);	//SET WAVFORM LOW
		if(Count == 100){	//60% OF THE PERIODDO THIS
			PORTB |= (1<<PORTB2);	//SET WAVEFORM HIGH
			Count = 0;		//SET COUNT BACK TO 0
		}
	}
}
