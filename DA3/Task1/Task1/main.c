/*
 * Task1.c
 *
 * Created: 3/31/2016 7:23:17 PM
 * Author : jmsikorski
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>

int read_temp();
void usart_init();
void usart_send();

volatile char ov_flag = 0;

ISR(TIMER1_OVF_vect)
{
	ov_flag = 1;
	TCNT1 = 57723;
}

int main(void)
{
	char buffer[20];
	usart_init();
	TCNT1 = 57723;
	TCCR1B = (1<<CS12) | (1<<CS10);
	TIMSK1 = (1<<TOIE1);
	int t = 0;
	sei();
	
    while (1) 
    {
		t = read_temp();
		if(ov_flag == 1)
		{
			ov_flag = 0;
			sprintf(buffer, "Temperature: %dF\n", t);
			usart_send(buffer);
		}
    }
}

int read_temp()
{
	ADCSRA = 0x87;
	ADMUX = (1<<REFS1) | (1<<REFS0); //Use ADC0
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & (1<<ADIF))==0);
	double t = ADC;
	t *= 99;
	t /= 512;
	t -= 58;
	return (int)t;
}

void usart_init()
{
	UCSR0B = (1<<TXEN0); // TX Enable
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); // 8 bit data segment
	UBRR0 = 0x33; // Baud rate
}

void usart_send(char* data)
{
	for(int i = 0; i < strlen(data); i++)
	{
		while (! (UCSR0A & (1<<UDRE0)));
		UDR0 = data[i];
	}
	return;
}
