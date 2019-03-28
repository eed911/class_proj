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
volatile int OVF_Count;
void USART_init( unsigned int ubrr );
void USART_TX_string(char *data);
char outs[25];
char flout[25];
int n;
float number;
char str[] = "Lets Get It";
char empty[] = " ";

int main(void)
{
	OVF_Count = 0;
	USART_init(BAUD_PRESCALLER);
	USART_TX_string("Connected!\r\n");
	
    while (1) 
    {
		USART_TX_string(str);
		USART_TX_string(empty);
		
		n = rand();
		number = 3.1415;
		snprintf(flout, sizeof(flout), "%.2f", number); //?????????
		USART_TX_string(flout); // ????????????????????????????????
		
		snprintf(outs, sizeof(outs), "%3d\r\n", n);
		USART_TX_string(outs);
		_delay_ms(5000);
    }
}
/*INT USART (RS-232)*/
void USART_init( unsigned int ubrr ){
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);	//Enable Tx interrupt
	UCSR0C = (3 << UCSZ00);	//asynchronous 8 N 1
}
/* SEND A STRING TO TEH RS-232*/
void USART_TX_string(char *data) {
	while (*data != '\0') {
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = *data;
		data++;
	}
}