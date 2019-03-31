/*
 * DA3B_C.c
 *
 * Created: 3/28/2019 7:03:24 PM
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
volatile unsigned int adc_temp; 
void USART_init( unsigned int ubrr );	//CREATES A VOID FUNCTION "USART_init"
void USART_TX_string(char *data);		//CREATES A VOID FUNCITON "USART_TX_string"
void read_adc(void);        // Function Declarations
void adc_init(void);
char outs[30];							//SETS VARIABLE "OUTS" AS A MATRIX FOR CONVERSIONS
char str[] = "Lets Get It";				//CREATES STRING "LETS GET IT"
char empty[] = " ";						//CREATES EMPTY STRING FOR SPACING

int main(void)
{
	Count = 0;
	TIMSK0 |= (1<<TOIE0);				//SETS THE INERRUPT TO ACTIVATE WHEN TIMMER 0 GETS OVERFLOW FLAG
	sei ();								//SETS GLOBAL INTERRUPT
	TCCR0A = 0x00;						//SETS NORMAL MODE ON TIMMER
	TCCR0B |= (1<<CS02)|(1<<CS00);		//SETS PRESCALER TO 1024
	adc_init();             // Initialize the ADC
	USART_init(BAUD_PRESCALLER);		//SETS THE BAUD PRESCALLER
	USART_TX_string("Connected!\r\n");	//PRINTS "CONNECTED" TO SERIAL. WE MADE IT!!
	while (1){
			if (Count > 59){					//IF COUNT IS > 60 EXICUTE THIS
				read_adc();
				snprintf(outs,sizeof(outs),"%3d\r\n", adc_temp);  // print it
				USART_TX_string(outs);
				Count = 0;						//RESETS THE COUNT VARIABLE BACK TO 0
			}
		}							//WAITS HERE FOR TIMMER INTERUPT
}
/* INIT ADC */
void adc_init(void)
{
	/** Setup and enable ADC **/
	ADMUX = (0<<REFS1)|    // Reference Selection Bits
	(1<<REFS0)|    // AVcc - external cap at AREF
	(0<<ADLAR)|    // ADC Left Adjust Result
	(1<<MUX2)|     // Analog Channel Selection Bits
	(0<<MUX1)|     // ADC5 (PC2 PIN?)
	(1<<MUX0);
	ADCSRA = (1<<ADEN)|    // ADC ENable
	(0<<ADSC)|     // ADC Start Conversion
	(0<<ADATE)|    // ADC Auto Trigger Enable
	(0<<ADIF)|     // ADC Interrupt Flag
	(0<<ADIE)|     // ADC Interrupt Enable
	(1<<ADPS2)|    // ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);
}
/* READ ADC PINS */
void read_adc(void)
{
	unsigned char i = 4;
	adc_temp = 0;
	while (i--)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		adc_temp+= ADC;
		_delay_ms(50);
	}
	adc_temp = adc_temp / 4 - 100;  // Average a few samples
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
	while (Count < 60){					//WHILE COUNT IS LESS THAN 60 LOOP
		if ((TIFR0 & 0x01) == 1){		//IF TV0V FLAG IS HIGH DO THIS
			TIFR0 = 0X01;				//CLEAR FLAG
			Count++;					//INCREMENT COUNT
		}
	}
}