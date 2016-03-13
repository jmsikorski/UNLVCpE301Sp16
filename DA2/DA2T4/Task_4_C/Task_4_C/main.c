/*
 * Task_1_C.c
 *
 * Created: 3/13/2016 8:48:09 AM
 * Author : jmsikorski
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void delay();	// Delay function for 0.5 sec delay

ISR(TIMER1_OVF_vect)	// Timer 1 overflow interrupt 
{
	PORTC |= (1<<0);	// Set PORTC0 to 1, flag for Timer1 completion
}

int main(void)
{
	DDRB = 0xFF;	// Set PORTB to output
	DDRC = 0xFF;	// Set PORTC to output
	DDRD |= (1<<5) | (1<<6);	// Set PORTD5&6 to output
	PORTC |= (1<<0);	// Initialize Timer1 flag to 1
	TIMSK1 |= (1<<TOIE1);	// Enable Timer1 interrupts
	char count = 0;	// Variable for 8 bit counter
	sei();	// Enable Global Interrupts
	while(1)
	{
		if((PORTC & (1<<0)) == 1)	// Check Timer1 completion flag
		{
			count++;	// Increment counter
			PORTB = count;	// Output counter to port B(bits 0-5)
			PORTC = count >> 2; // Output counter to port C(bits 6 & 7) 
			if(count%5 == 0)	// Check if count is div by 5
				PORTD ^= (1<<5);	// Toggle PORTD5
			if(count%10 == 0)	// Check if count is div by 10
				PORTD ^= (1<<6);	// Toggle PORTD6
			delay();	// Start Delay
			PORTC &= 0xFE;	// Clear Timer1 completion flag
		}
	}
	return 0;
}

void delay()
{
	TCNT1 = 3035;	// Set TCNT1 for 62,501 cycles
	TCCR1A = 0;
	TCCR1B |= (1<<CS10)|(1<<CS11);	// Set prescalar to 64
	return;
}
