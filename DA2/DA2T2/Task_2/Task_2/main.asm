;
; DA2.asm
;
; Created: 3/9/2016 10:45:09 PM
; Author : jmsikorski
;

.INCLUDE "header.inc"		;Inculde header
.ORG 0x00					;Code begins here

	INITSTACK				;Initialize the stack

	LDI		R18, 0xFF		;Set R18 bits 0-7 high
	OUT		DDRB, R18		;Set PORTB to output
	OUT		DDRC, R18		;Set PORTC to output
BEGIN:
	RCALL	DELAY			;Call delay subroutine
	SUBI	R17, -1			;Increment R17
	OUT		PORTB, R17		;Output R17 to PORTB
	MOV		R16, R17		;Copy R17 to R16
	LSR		R16				;Shift R16 right
	LSR		R16				;Shift R16 right
	OUT		PORTC, R16		;Output R16 to PORTC
	RJMP	BEGIN
