.ORG 0x100

.MACRO INITSTACK			;Macro to initialize Stack Pointer
	LDI		R16, HIGH(RAMEND)
	OUT		SPH, R16		;Set Stack Pointer to RAMEND
	LDI		R16, LOW(RAMEND)
	OUT		SPL, R16
.ENDMACRO

DELAY:						;Delay subroutine for 0.5 second delay
	PUSH	R20				;Save R20 on the stack
	LDI		R20, 0x0B
	STS		TCNT1H, R20
	LDI		R20, 0xDB
	STS		TCNT1L, R20		;Set TCNT1 for 62,501 cycles
	LDI		R20, 0x00
	STS		TCCR1A, R20
	LDI		R20, 0x03
	STS		TCCR1B, R20		;Set prescalar to 64
AGAIN:
	IN		R20, TIFR1		;Get TIFR1 register
	SBRS	R20, TOV1		;Check TOV1 flag
	RJMP	AGAIN
	LDI		R20, 0x00	
	STS		TCCR1B, R20		;Stop Timer
	LDI		R20, 0x01
	OUT		TIFR1, R20		;Clear TOV1 flag
	POP		R20				;Restore R20
	RET