.ORG 0x00
	RJMP	MAIN			;Set Reset Interrupt
.ORG 0x1A
	RJMP	TIM1_OVF		;Set Timer1 Overflow Interrupt

TIM1_OVF:					;Timer1 Overflow Interrupt Subroutine
	PUSH	R20				;Save R20
	LDS		R20, SREG		;Save SREG
	PUSH	R20
	LDI		R20, 0x00	
	STS		TCCR1B, R20		;Stop Timer1
	LDI		R20, 1<<TOV1	
	OUT		TIFR1, R20		;Clear TOV1 flag
	LDI		TEMP, 0			;Set TEMP reg to 0
	RCALL	DELAY			;Call Delay subroutine
	POP		R20				
	STS		SREG, R20		;Restore SREG
	POP		R20				;Restore R20
	RETI

.ORG 0x500

.DEF	COUNT1 = R17		;Count1 Variable in R17
.DEF	COUNT5 = R19		;Count5 Variable in R19
.DEF	TEMP = R23			;Temp Register in R23 (This Reg is not saved)


.MACRO INITSTACK			; Initialize Stack Point to RAMEND
	LDI		R16, HIGH(RAMEND)
	OUT		SPH, R16
	LDI		R17, LOW(RAMEND)
	OUT		SPL, R16
.ENDMACRO

DELAY:						;Delay Subroutine for 0.5 sec delay
	PUSH	R20				;Save R20
	LDI		R20, 0x0B
	STS		TCNT1H, R20
	LDI		R20, 0xDB
	STS		TCNT1L, R20		;Set TCNT1 to 62,501 cycles
	LDI		R20, 0x00
	STS		TCCR1A, R20
	LDI		R20, 0x03
	STS		TCCR1B, R20		;Set prescalar to 64
	LDI		R20, 0x01
	STS		TIMSK1, R20		;Enable Timer1 Overflow Interrupt
	POP		R20
	RET