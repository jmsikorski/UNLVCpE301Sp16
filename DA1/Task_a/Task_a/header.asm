; Created: 2/19/2016 1:39:33 PM
; Author : jmsikorski
;

.MACRO INITSTACK
	LDI		R16, HIGH(RAMEND)
	OUT		SPH, R16
	LDI		R16, LOW(RAMEND)
	OUT		SPL, R16
.ENDMACRO

.DEF	TEMP = R20		;R20 is a temp regsiter and its value is not saved
.DEF	COUNT = R23		;R23 is used for loop counting

	INITSTACK
	LDI		R26, 252
	PUSH	R26

Div3:					;Checks if a value is divisible by 3
						;Value is retrieved from top of the stack
	POP		TEMP		;Get the value to check into temp from the stack
	PUSH	R16			;Save R16 state
	PUSH	R21			;Save R21 state
	PUSH	R22			;Save R22 state
	PUSH	COUNT		;Save Count state
	LDI		R21, 0		;Clear summing register
	LDI		R22, 0		;Store 0 value
	LDI		COUNT, 4	;Loop Counter
	MOV		R16, TEMP
Repeat3:
	LSL		TEMP		;Shift out MSB of TEMP
	SBC		R21, R22	;Subtract carry from count
	LSL		TEMP		;Shift out MSB of TEMP
	ADC		R21, R22	;Add carry to count
	DEC		COUNT		;Decrement loop counter
	CPI		COUNT, 0	;Check loop counter
	BRNE	Repeat3		;Stay in loop
	CPI		R21, 0		
	BREQ	Add3		;If count != 0 don't add
	CPI		R21, 3
	BREQ	Add3		;If count != 3 don't add
	CPI		R21, -3
	BREQ	Add3		;If count != -3 don't add
	RJMP	End3
Add3:
	ADD		R1, R16		;Add the value to R1
End3:
	POP		COUNT		;Restore Count
	POP		R22			;Restore R22
	POP		R21			;Restore R21
	POP		R16			;Restore R16
	RJMP	Div7
	RET					;Return to program

Div7:					;Checks if a value is divisible by 7
						;Value is retrieved from top of the stack
	LDI		R26, 252
	PUSH	R26

	POP		TEMP		;Get the value to check into temp from the stack
	PUSH	R16
	PUSH	R21			;Save R21 state
	PUSH	R22			;Save R22 state
	PUSH	COUNT		;Save Count state
	LDI		R21, 0		;Clear summing register1
	LDI		R22, 0		;Store 0 value
	LDI		R23, 3		;Loop counter
	MOV		R16, TEMP
Repeat7:
	SBRC	TEMP, 0		;Add 1 if bit 0 is 1
	SUBI	R21, -1
	SBRC	TEMP, 1		;Add 2 if bit 1 is 1
	SUBI	R21, -2
	SBRC	TEMP, 2		;Add 4 if bit 1 is 1
	SUBI	R21, -4
	LSR		TEMP			;Shift out 1st 3 bits
	LSR		TEMP
	LSR		TEMP
	DEC		R23
	CPI		R23, 0
	BRNE	Repeat7
	SUBI	R21, 7
	BRMI	End7
	BREQ	Add7
	LDI		R23, 3
	RJMP	Repeat7

Add7:
	ADD		R2, R16
End7:
	RJMP	End7
	POP		R16
	POP		COUNT		;Restore Count
	POP		R22			;Restore R22
	POP		R21			;Restore R21
	RET					;Return to program
			

