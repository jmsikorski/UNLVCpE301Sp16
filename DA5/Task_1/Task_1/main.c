/*
 * CpE301L8E1.c
 *
 * Created: 4/1/2016 4:10:42 PM
 * Author : jmsikorski
 */ 

#include <avr/io.h>

int read_speed();

int main()
{
	DDRC &= 0xFE; //make PORTC0 input pin
	DDRB |= (1<<PORTB1); // set PB1(OC1A) as output pin
	// enable 10 bit Fast PWM, select inverted PWM, 256 prescalar
	TCCR1A |= (1<<COM1A1) | (1<<COM1A0) | (1<<WGM10) | (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<CS12);

	while(1)
	{

		if((TIFR1 & (1<<OCF1A)) != 0)		
			OCR1A = read_speed(); 
	}
	return 0 ;
}

int read_speed()
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC Enable, Div factor = 128
	ADMUX = 0x00; //Use ADC0, ARef voltage ref
	ADCSRA |= (1<<ADSC); // Start conversion
	while((ADCSRA & (1<<ADIF))==0);
	return ADC;
}