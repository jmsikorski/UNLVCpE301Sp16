/*
 * Task_1.c
 *
 * Created: 4/12/2016 6:36:29 PM
 * Author : jmsikorski
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

int main(void)
{
	uint8_t i = 0;
	DDRB |= (1<<PORTB1) | (1<<PORTB3); // set PB1(OC1A) and PB3(OC2A) for output
	DDRD |= (1<<PORTD6); // set PD6(OC0A) and PB3 for output
	PORTB = 0x00; // set output high -> turn all LEDs off
	PORTD = 0x00; // set output high -> turn all LEDs off
	// enable 8 bit PWM, select inverted PWM
	TCCR1A |= (1<<COM1A1) | (1<<WGM10);
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);
	TCCR0B |= (1<<CS00);
	TCCR2A |= (1<<COM2A1) | (1<<WGM21) | (1<<WGM20);
	TCCR2B |= (1<<CS20);

	while(1)
	{
		OCR0A = 0;
		OCR1A = 0;
		OCR2A = 0;

		_delay_ms(5000);
		/* dimm LED on */
		for (i=0; i<255; i++) 
		{
			_delay_ms(10);
			OCR2A = i; // RED
		} // RGB = 100 (RED)
		_delay_ms(2000); 
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR2A = -i; // RED
		}
		for (i=0; i<255; i++) 
		{
			_delay_ms(10);
			OCR1AL = i; // BLUE
		} // RGB = 001 (BLUE)
		_delay_ms(2000);
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR1AL = -i; // BLUE
		}
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR0A = i; // GREEN
		} // RGB = 010 (GREEN)
		_delay_ms(2000);
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR0A = -i; // GREEN
		}
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR1AL = i; // BLUE
			OCR2A = i; // RED
			OCR0A = i; // GREEN
		} // RGB = 111 (WHITE)
		_delay_ms(2000);
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR1AL = -i; // BLUE
		} // RGB = 110 (YELLOW)
		_delay_ms(2000);
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR0A = -i; // GREEN
		} // RGB = 100 (RED)
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR1AL = i; // BLUE
		} // RGB = 101 (MAGENTA)
		_delay_ms(2000);
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR2A = -i; // RED
		} // RGB = 001 (BLUE)
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR0A = i; // GREEN
		} // RGB = 011 (CYAN)
		_delay_ms(2000);
		for (i=0; i<255; i++)
		{
			_delay_ms(10);
			OCR1AL = -i; // BLUE
		} // RGB = 010 (GREEN)
		for (i=0; i<255; i++) 
		{
			_delay_ms(10);
			OCR0A = -i; // GREEN
		} // RGB = 000 (OFF)
	}
	return 0;
}
