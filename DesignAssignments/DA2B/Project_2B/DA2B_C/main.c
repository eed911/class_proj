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
	DDRB |= (1<<DDB2);				//sets the direction of port B.2 to output
	PORTB |= (1<<PORTB2);			//enable pull up resistor, setting port b.2 logic high
	DDRD &= (0<<DDD2);				//sets the direction of port D.2 as an input
	PORTD |= (1<<PORTD2);			//enable pull up resistor, setting port d.2 logic high
	
	EICRA = 0x00;					//whenever the pin is low, enable interrupt
	EIMSK = (1<<INT0);				//setting interrupt to be looked at to be int0
	sei ();							//enabling global interrupt

	while(1);						//wait here until something happens
}

ISR (INT0_vect)					//interrupt subroutine
{
	uint8_t Count = 0;			//initialize counting variable
	TIMSK0 |= (1<<TOIE0);		//enable timer 0 interrupt
	sei ();						//enable global interrupt
	TCCR0B |= (1<<CS02) | (1<<CS00); //sets pre-scaler to 1024
	while(Count < 73){				//delay until counter reaches a value of 73
		PORTB &= (0<<PORTB2);		//turn on led
		//if(TCNT0 <10)				//
		Count++;	
		
						//increment counter variable by 1
		//do nothing while counting
		//TCNT0 = 0;				//set counter to 0
		//TIFR0 = 0X01;				//clear flag
		//Count++;					//increment count by 1
		//while (TCNT1 < 19530)		//whenever the counter is less than
		
	}
	PORTB |= (1<<PORTB2);
}
ISR (TIMER0_OVF_vect){
	TCNT0 = 0;
}
// .0065 * 1024 * 256 * 73 = 124,387 = 124.387ms



