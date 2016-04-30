/*
 * CpE301L7E1.c
 *
 * Created: 3/30/2016 11:32:44 AM
 * Author : jmsikorski
 */ 
#define F_CPU 8000000UL 
#include <avr/io.h>
#include <util/delay.h>

int read_speed();
int main()
{
	DDRD = 0xFF;
	DDRC &= 0xFE; //make PORTC0 input pin
	DDRB |= (1<<PORTB1); // set PB1(OC1A) as output pin
	// enable 10 bit Fast PWM, select inverted PWM, 1024 prescalar
	TCCR1A |= (1<<COM1A1) | (1<<COM1A0) | (1<<WGM10) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);

	while(1)
	{
		if((TIFR1 & (1<<OCF1A)) != 0)
			OCR1A = read_speed();

		if ((PINB&0x02) != 0x00)
		{
			PORTD = 0X66;
			_delay_ms(2);
			PORTD = 0xCC;
			_delay_ms(2);
			PORTD = 0x99;
			_delay_ms(2);
			PORTD = 0x33;
			_delay_ms(2);
		}
	}
	return 0;
}

int read_speed()
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC Enable, Div factor = 128
	ADMUX = 0x00; //Use ADC0, ARef voltage ref
	ADCSRA |= (1<<ADSC); // Start conversion
	while((ADCSRA & (1<<ADIF))==0);
	return ADC;
}