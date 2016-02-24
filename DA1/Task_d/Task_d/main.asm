.INCLUDE "header.inc"
.ORG 0x00
.EQU	Var_Address = 0x100;
.EQU	Num = 25
	INITSTACK

	LDI		ZL, LOW(Var_Address)
	LDI		ZH, HIGH(Var_Address)
	LDI		TEMP1, LOW(RAMEND/2)
	LDI		COUNT, Num
GetNum:
	ST		Z+, TEMP1
	SUBI	TEMP1, -4
	DEC		COUNT
	CPI		COUNT, 0
	BRNE	GetNum

	LDI		ZL, LOW(Var_Address)
	LDI		ZH, HIGH(Var_Address)
	LDI		COUNT, Num
Divide:
	LD		TEMP1, Z
	CALL	Div7
	LD		TEMP1, Z+
	CALL	Div3
	DEC		COUNT
	CPI		COUNT, 0
	BRNE	Divide
	
	CPI		R24, 0
	BREQ	End1
	LDI		TEMP1, 8
	OR		R7, TEMP1

End1:
	RJMP	End1