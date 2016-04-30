/*
 * CpE301L8E3a.c
 *
 * Created: 4/12/2016 5:17:57 PM
 * Author : jmsikorski
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int get_pos();
int main()
{
	DDRC &= 0xFE; //make PORTC0 input pin
	DDRB |= (1<<PORTB1); // set PB1(OC1A) as output pin
	//TOP = ICR1;
	//output compare OC1A 8 bit non inverted PWM
	//Clear OC1A on Compare Match, set OC1A at TOP
	//Fast PWM
	//ICR1 = 20000 defines 50Hz pwm
	ICR1 = 20000;
		
	TCCR1A|=(0<<COM1A0)|(1<<COM1A1)|(0<<COM1B0)|(0<<COM1B1)|(0<<FOC1A)|(0<<FOC1B)|(1<<WGM11)|(0<<WGM10); //TCCR1A = 0x82
	TCCR1B|=(0<<ICNC1)|(0<<ICES1)|(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10);
	//start timer with prescaler 8
	int offset = 490; // 0 position offset
	// Servo range is from 2140 to 490, so 1650 steps
	// 1650/1024 = 1.61, so each ADC value = 1.6 servo steps
	while (1)
	{
		OCR1A = (get_pos()*16)/10 + offset;
	}
}

int get_pos()
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // ADC Enable, Div factor = 128
	ADMUX = 0x00; //Use ADC0, ARef voltage ref
	ADCSRA |= (1<<ADSC); // Start conversion
	while((ADCSRA & (1<<ADIF))==0);
	return ADC;
}