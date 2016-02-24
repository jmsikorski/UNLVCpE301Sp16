; Created: 2/19/2016 1:39:33 PM
; Author : jmsikorski
;
.ORG	0x20			;Place after program code

.MACRO INITSTACK		;Initialize Stack Pointer
	LDI		R16, HIGH(RAMEND)
	OUT		SPH, R16
	LDI		R16, LOW(RAMEND)
	OUT		SPL, R16
.ENDMACRO

.DEF	TEMP1 = R17		;R17 is a temp regsiter and its value is not saved
.DEF	COUNT = R18		;R18 is used for loop counting
.EQU	Var_Address = 0x100;

Div3:					;Checks if a value is divisible by 3
						;Value is stored in TEMP1 register
						;Algorithm subtracts odd bits and adds even bits
						;If the sum is 0, 3, or -3 then TEMP1 is divisible by 3
	PUSH	R16			;Save R16 state
	PUSH	R25			;Save R25 state
	PUSH	R22			;Save R22 state
	PUSH	COUNT		;Save Count state
	LDI		R25, 0		;Clear summing register
	LDI		R22, 0		;Store 0 value
	LDI		COUNT, 4	;Loop Counter
	MOV		R16, TEMP1	;Save TEMP1 value
Repeat3:
	LSL		TEMP1		;Shift out MSB of TEMP1
	SBC		R25, R22	;Subtract carry from count
	LSL		TEMP1		;Shift out MSB of TEMP1
	ADC		R25, R22	;Add carry to count
	DEC		COUNT		;Decrement loop counter
	CPI		COUNT, 0	;Check loop counter
	BRNE	Repeat3		;Stay in loop
	CPI		R25, 0		
	BREQ	Add3		;If count != 0 don't add
	CPI		R25, 3
	BREQ	Add3		;If count != 3 don't add
	CPI		R25, -3
	BREQ	Add3		;If count != -3 don't add
	RJMP	End3
Add3:
	ADD		R23, R16	;Add the value to R24
	ADC		R24, R22	;Add the carry if any to R25		
End3:
	POP		COUNT		;Restore Count
	POP		R22			;Restore R22
	POP		R25			;Restore R25
	POP		R16			;Restore R16
	RET					;Return to program

Div7:					;Checks if a value is divisible by 7
						;Value is stored in TEMP1 register
						;Algorithm divides 8 bits into 3 bit segments,
						;segments are summed, if sum = 7 then TEMP1 is
						;divisible by 7, if sum > 7, repeat summation 
	PUSH	R16			;Save R16 state
	PUSH	R25			;Save R25 state
	PUSH	R22			;Save R22 state
	PUSH	COUNT		;Save Count state
	LDI		R25, 0		;Clear summing register1
	LDI		R22, 0		;Store 0 value
	LDI		COUNT, 3	;Loop counter
	MOV		R16, TEMP1	;Save TEMP1 value
Repeat7:				
	SBRC	TEMP1, 0	;Add 1 if bit 0 is 1
	SUBI	R25, -1
	SBRC	TEMP1, 1	;Add 2 if bit 1 is 1
	SUBI	R25, -2
	SBRC	TEMP1, 2	;Add 4 if bit 1 is 1
	SUBI	R25, -4
	LSR		TEMP1		;Shift out 1st 3 bits
	LSR		TEMP1
	LSR		TEMP1
	DEC		COUNT		;Decrement Counter		
	CPI		COUNT, 0	;Loop until Counter equals 0
	BRNE	Repeat7
	SUBI	R25, 7		;Subtract 7 from sum register
	BRMI	End7		;If Sum less than 0, not divisible by 7
	BREQ	Add7		;If Sum equal 7, divisible by 7
	LDI		COUNT, 3	;If greater than 0, sum again
	RJMP	Repeat7

Add7:
	ADD		R20, R16	;Add the value to R20
	ADC		R21, R22	;Add the carry if any to R21
End7:
	POP		COUNT		;Restore Count
	POP		R22			;Restore R22
	POP		R25			;Restore R25
	POP		R16			;Restore R16
	RET					;Return to program
			

