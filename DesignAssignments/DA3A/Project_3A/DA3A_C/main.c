/*
 * DA3A_C.c
 *
 * Created: 3/26/2019 7:21:07 PM
 * Author : Cody Hudson
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL)))-1)

//Functions
volatile int Count;
void USART_init( unsigned int ubrr );	//CREATES A VOID FUNCTION "USART_init"
void USART_TX_string(char *data);		//CREATES A VOID FUNCITON "USART_TX_string"
char outs[30];							//SETS VARIABLE "OUTS" AS A MATRIX FOR CONVERSIONS
int n;									//SETS "n" AS AN INTEGER VALUE
float PI;								//SETS "PI" AS A FLOATING VARIABLE
char str[] = "Lets Get It";				//CREATES STRING "LETS GET IT"
char empty[] = " ";						//CREATES EMPTY STRING FOR SPACING

int main(void)
{
	Count = 0;
	TIMSK0 |= (1<<TOIE0);				//SETS THE INERRUPT TO ACTIVATE WHEN TIMMER 0 GETS OVERFLOW FLAG
	sei ();								//SETS GLOBAL INTERRUPT
	TCCR0A = 0x00;						//SETS NORMAL MODE ON TIMMER
	TCCR0B |= (1<<CS02)|(1<<CS00);		//SETS PRESCALER TO 1024
	USART_init(BAUD_PRESCALLER);		//SETS THE BAUD PRESCALLER
	USART_TX_string("Connected!\r\n");	//PRINTS "CONNECTED" TO SERIAL. WE MADE IT!! 
    while (1);							//WAITS HERE FOR TIMMER INTERUPT
}
/*INT USART (RS-232)*/
void USART_init( unsigned int ubrr ){
	UBRR0H = (unsigned char)(ubrr>>8);	//SIZING THE PRESCALLER
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);				//Enable Tx interrupt
	UCSR0C = (3 << UCSZ00);				//asynchronous 8 N 1
}
/* SEND A STRING TO TEH RS-232*/
void USART_TX_string(char *data) {		//FUNCTION CREATED IN ORDER TO SEND THROUGH SERIAL
	while (*data != '\0') {
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = *data;
		data++;
	}
}
ISR (TIMER0_OVF_vect){					//TV0V FLAG INTERUPT
	while (Count < 60){					//WHILE COUNT IS LESS THAN 76 LOOP
		if ((TIFR0 & 0x01) == 1){		//IF TV0V FLAG IS HIGH DO THIS
			TIFR0 = 0X01;				//CLEAR FLAG
			Count++;					//INCREMENT COUNT
		}
	}
	if (Count > 59){					//IF COUNT IS > 60 EXICUTE THIS
		USART_TX_string(str);			//PRINT STRING "LETS GET IT"
		USART_TX_string(empty);			//PRINTS A BLANK SPACE
				
		n = rand();						//GENERATES A RANDOM NUMBER STORES TO VARIABLE n
		PI = 3.1415;					//GENERATES PI AND STORES 
				
		snprintf(outs, sizeof(outs), "%3d\r\n", n);
		USART_TX_string(outs);			//PRINTS THE STING VERSION OF RANDOM NUMBER TO SERIAL PORT
		USART_TX_string(empty);			//PRINTS A BLANK SPACE
		
		sprintf(outs, "%f", PI);		//CONVERTS THE FLOTING VALUE PI INTO A STRING TO BE SENT THROUGH THE TERMAINL
		USART_TX_string(outs);			//PRINTS THE STRING VERSION PI TO THE SERIAL MONITOR
		USART_TX_string(empty);			//PRINTS A BLANK SPACE
		Count = 0;						//RESETS THE COUNT VARIABLE BACK TO 0
	}
}