/*
 * Task_1_C.c
 *
 * Created: 3/13/2016 8:48:09 AM
 * Author : jmsikorski
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void delay();	// Delay function for 0.5 second delay

int main(void)
{
	DDRB |= (1<<0);	// Set PORTB0 to output
	while(1)
	{
		delay();	// Call delay infinitely
	}
	return 0;
}

void delay()
{
	TCNT1 = 3035;	// Set TCNT1 to 62,501 cycles
	TCCR1A = 0;
	TCCR1B |= (1<<CS10)|(1<<CS11);	// Set prescalar to 64
	while((TIFR1 &= 1<<TOV1) != 1);	// Wait for TOV1 flag
	TCCR1B = 0;	// Stop Timer
	TIFR1 |= (1<<TOV1);	// Clear TOV1 flag
	PORTB ^= (1<<0);	// Toggle PORTB0
	return;
}
