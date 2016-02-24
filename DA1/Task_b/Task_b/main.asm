.INCLUDE "header.inc"				;Header file contains macros & subroutines
.ORG 0x00							;Begining of code
.EQU	Var_Address = 0x100;		;Variable for values array pointer
.EQU	Num = 25					;Variable for number of values
	INITSTACK

	LDI		ZL, LOW(Var_Address)	;Load Z with variable array address
	LDI		ZH, HIGH(Var_Address)
	LDI		TEMP1, LOW(RAMEND/2)	;Load Temp1 with initial value 
	LDI		COUNT, Num				;Number of values to add
	
GetNum:
	ST		Z+, TEMP1				;Store Temp1 into (Z) then increment Z
	SUBI	TEMP1, -4				;Update Temp1 value
	DEC		COUNT					;Decrement Counter
	CPI		COUNT, 0				;Loop until Counter equals 0
	BRNE	GetNum

	LDI		ZL, LOW(Var_Address)	;Load Z with array index[0]
	LDI		ZH, HIGH(Var_Address)
	LDI		COUNT, Num				;Variable Counter
Divide7:
	LD		TEMP1, Z+				;Load TEMP1 with the value in (Z), post increment Z
	CALL	Div7					;Call Div7 Subroutine
	DEC		COUNT					;Decrement counter
	CPI		COUNT, 0				;Repeat until Counter equals 0
	BRNE	Divide7
		
End1:
	RJMP	End1					;Infinte Loop