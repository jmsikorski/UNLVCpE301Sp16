/* Nokia 5110 LCD AVR Library example
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 * Original library written by SkewPL, http://skew.tk
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "nokia5110.h"

volatile char ov_flag = 0;
int read_temp();

ISR(TIMER1_OVF_vect)
{
	ov_flag = 1;
	TCNT1 = 57723;
}

int main(void)
{
	char buffer[20];
    nokia_lcd_init();
    nokia_lcd_clear();
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
			nokia_lcd_clear();
			ov_flag = 0;
			nokia_lcd_write_string("Temp: ", 2);
			nokia_lcd_set_cursor(0,16);
			sprintf(buffer, "%dF", t);
			nokia_lcd_write_string(buffer, 2);
			nokia_lcd_render();
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