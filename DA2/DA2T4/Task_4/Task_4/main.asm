;
; DA2.asm
;
; Created: 3/9/2016 10:45:09 PM
; Author : jmsikorski
;

.INCLUDE "header.inc"		;Include header file

.ORG 0x100					;Begining of code goes here

MAIN:						;Label for reset interrupt
	INITSTACK				;Initalize the stack

	LDI		R18, 0xFF		;Set R18 bits 0-7 high
	OUT		DDRB, R18		;Set PORTB to output
	OUT		DDRC, R18		;Set PORTC to output
	OUT		DDRD, R18		;Set PORTD to output
	LDI		COUNT1, 0x00	;Initialize Count1 to 0
	LDI		COUNT5, 0x00	;Initialize Count5 to 0
	LDI		R16, 0x00		;Initialize R16 to 0
	LDI		R18, 0x60		;Set R18 bits 5&6 hight
	LDI		R20, 0x00		;Initialize R20 to 0
	LDI		R21, 0x00		;Initialize R21 to 0
	LDI		R22, 0x20		;Set R22 bit 5 high
	SEI						;Enable Global Interrupts
	RCALL	DELAY			;Call Delay subroutine

COUNT:
	LDI		TEMP, 0x01		;Set TEMP bit 1 high
	SUBI	COUNT1, -1		;Increment Count1
	SUBI	COUNT5, -1		;Increment Count5
	OUT		PORTB, COUNT1	;Output Count1 to PORTB
	MOV		R16, COUNT1		;Copy Count1 to R16
	LSR		R16				;Right Shift R16
	LSR		R16				;Right Shift R16
	ANDI	R16, 0x30		;Clear R16 bits 0-3 and 6-7
	CPI		COUNT5, 5		;Check if Count5 = 5
	BRNE	NOT5
	EOR		R21, R22		;Toggle R21 bit 5
NOT5:
	CPI		COUNT5, 10		;Check if Count5 = 10
	BRNE	NOT10
	EOR		R21, R18		;Toggle R21 bit 5&6
	LDI		COUNT5, 0		;Reset Count5
NOT10:
	OUT		PORTC, R16		;Output R16 to PORTC
	OUT		PORTD, R21		;Output R21 to PORTD

WAIT:
	CPI		TEMP, 0			;Loop here while TEMP = 1
	BREQ	COUNT		
	RJMP	WAIT