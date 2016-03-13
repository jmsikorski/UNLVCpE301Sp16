/*
 * Task_1_C.c
 *
 * Created: 3/13/2016 8:48:09 AM
 * Author : jmsikorski
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

char delay(char);	// Delay for 0.5 second period returns updated counter

int main(void)
{
	DDRB = 0xFF;	// Set PORTB to output
	DDRC = 0xFF;	// Set PORTC to output
	DDRD |= (1<<5) | (1<<6);	// Set PORTD5&6 to output
	char count = 0;	// Variable for 8 bit counter
	while(1)
	{
		count = delay(count); // Update counter by calling delay
		PORTB = count;	// Output count bits 0-5 to PINB0-5
		PORTC = count >> 2;	// Output count bits 6-7 to PINC4-5
		if(count%5 == 0)	// Check if count is div by 5
			PORTD ^= (1<<5);	// Toggle PIND5
		if(count%10 == 0)	// Check if count is div by 10
			PORTD ^= (1<<6);	// Toggle PIND6
	}
	return 0;
}

char delay(char a)
{
	TCNT1 = 3035;	// Set TCNT1 to 62,501 cycles
	TCCR1A = 0;
	TCCR1B |= (1<<CS10)|(1<<CS11);	// Set prescalar to 64
	while((TIFR1 &= 1<<TOV1) != 1);	// Wait for TOV1 flag
	TCCR1B = 0;	// Stop Timer
	TIFR1 |= (1<<TOV1);	// Clear TOV1 flag
	a++;	// increment counter
	return a;	// return counter
}
