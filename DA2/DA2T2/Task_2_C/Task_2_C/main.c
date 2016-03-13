/*
 * Task_1_C.c
 *
 * Created: 3/13/2016 8:48:09 AM
 * Author : jmsikorski
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

char delay(char);	// Delay function for 0.5 second delay, returns updated counter

int main(void)
{
	DDRB = 0xFF;	// Set PORTB to output
	DDRC = 0xFF;	// Set PORTC to output
	char count = 0;	// 8 bit counter variable
	while(1)
	{
		count = delay(count);	// Call delay function on counter variable
		PORTB = count;	// Output counter bits 0-5 on PORTB0-5
		PORTC = count >> 2;	// Output counter bits 6-7 on PORTC4-5
	}
	return 0;
}

char delay(char a)
{
	TCNT1 = 3035;	// Set TCNT1 to 62,501 cycles
	TCCR1A = 0;
	TCCR1B |= (1<<CS10)|(1<<CS11);	// Set prescalar to 64
	while((TIFR1 &= 1<<TOV1) != 1);	// Wait for TOV1 flag
	TCCR1B = 0;	// Stop timer
	TIFR1 |= (1<<TOV1);	// Clear TOV1 flag
	a++;	// increment counter variable
	return a;	// return counter variable
}
