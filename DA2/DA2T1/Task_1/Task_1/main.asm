;
; DA2.asm
;
; Created: 3/9/2016 10:45:09 PM
; Author : jmsikorski
;

.INCLUDE "header.inc"		;Include header file
.ORG 0x00					;Begining of code goes here

	INITSTACK				;Initialize the stack

	SBI		DDRC, 0			;Set PORTC0 to output
	LDI		R17, 0x01		;Set R17 bit 1 high
	LDI		R16, 0x01		;Set R16 bit 1 high
	OUT		PORTC, R17		;Output R17 to PORTC
BEGIN:
	RCALL	DELAY			;Call delay subroutine
	EOR		R17, R16		;Toggle R17 bit 1
	OUT		PORTC, R17		;Output R17 to PORTC
	RJMP	BEGIN
