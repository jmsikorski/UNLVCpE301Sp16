;
; DA2.asm
;
; Created: 3/9/2016 10:45:09 PM
; Author : jmsikorski
;

.INCLUDE "header.inc"		;Include header file
.ORG 0x00					;Code begins here

	INITSTACK				;Initialize the stack

	LDI		R18, 0xFF		;Set R18 bit 0-7 high
	OUT		DDRB, R18		;Set PORTB to output
	OUT		DDRC, R18		;Set PORTC to output
	OUT		DDRD, R18		;Set PORTD to output
	LDI		R17, 0x00		;Initialize R17 to 0
	LDI		R16, 0x00		;Initialize R16 to 0
	LDI		R19, 0x00		;Initialize R19 to 0
	LDI		R21, 0x00		;Initialize R21 to 0
	LDI		R18, 0x60		;Set R18 bit 5&6 high
	LDI		R20, 0x20		;Set R20 bit 5 high
BEGIN:
	RCALL	DELAY			;Call delay subroutine
	SUBI	R17, -1			;Increment R17 (counter)
	SUBI	R19, -1			;Increment R19 (counter for 5's)
	OUT		PORTB, R17		;Output R17 to PORTB
	MOV		R16, R17		;Copy R17 to R16
	LSR		R16				;Shift R16 Right
	LSR		R16				;Shift R16 Right
	ANDI	R16, 0x30		;Clear R16 bits 1-3 & 6-7
	CPI		R19, 5			;Check if 5's counter = 5
	BRNE	NOT5
	EOR		R21, R20		;Toggle R21 bit 5
NOT5:
	CPI		R19, 10			;Check if 5's counter = 10
	BRNE	NOT10
	EOR		R21, R18		;Toggle R21 bit 5&6
	LDI		R19, 0
NOT10:
	OUT		PORTC, R16		;Output R16 to PORTC
	OUT		PORTD, R21		;Output R21 to PORTD
	RJMP	BEGIN