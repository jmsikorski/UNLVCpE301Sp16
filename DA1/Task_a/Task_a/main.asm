.INCLUDE "header.inc"				;Header file contains macros & subroutines
.ORG 0x00							;Begining of code

	INITSTACK						;Initialize the stack pointer

	LDI		ZL, LOW(Var_Address)	;Load Z with variable address
	LDI		ZH, HIGH(Var_Address)
	LDI		TEMP1, LOW(RAMEND/2)	;Load Temp1 with initial value 
	LDI		COUNT, 25				;Number of values to add
Get25:
	ST		Z+, TEMP1				;Store Temp1 into (Z) then increment Z
	SUBI	TEMP1, -4				;Update Temp1 value
	DEC		COUNT					;Decrement Counter
	CPI		COUNT, 0				;Loop until Counter equals 0
	BRNE	Get25

End1:
	RJMP	End1					;Infinite loop