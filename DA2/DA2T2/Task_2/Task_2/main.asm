;
; DA2.asm
;
; Created: 3/9/2016 10:45:09 PM
; Author : jmsikorski
;

.INCLUDE "header.inc"
.ORG 0x00

	INITSTACK

	LDI		R18, 0xFF
	OUT		DDRB, R18
	OUT		DDRC, R18
BEGIN:
	RCALL	DELAY
	SUBI	R17, -1
	OUT		PORTB, R17
	MOV		R16, R17
	LSR		R16
	LSR		R16
	OUT		PORTC, R16
	RJMP	BEGIN
