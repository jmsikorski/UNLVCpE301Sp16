;
; sikorsk4_DA0_CpE301_S16.asm
;
; Created: 2/15/2016 5:21:48 PM
; Author : jmsikorski
;


; Replace with your application code
	.EQU a = 35	; Using variables for code efficiency
	.EQU b = 37
	.EQU c = 42
	.EQU d = 48
	.EQU e = 59

	SBI		DDRB, 2		;Set Pin 2 of B register to output
	LDI		R17, 0x04	;Set register 3 to 4
	SUBI	R16, -a		;Using SUBI for speed to not haveZ to load
	BRVS	OVER;		;If there is overflow, jump to OVER
	SUBI	R16, -b		;Using SUBI for speed to not have to load
	BRVS	OVER;		;If there is overflow, jump to OVER
	SUBI	R16, -c		;Using SUBI for speed to not have to load
	BRVS	OVER;		;If there is overflow, jump to OVER
	SUBI	R16, -d		;Using SUBI for speed to not have to load
	BRVS	OVER;		;If there is overflow, jump to OVER
	SUBI	R16, -e		;Using SUBI for speed to not have to load
	BRVS	OVER		;If there is overflow, jump to OVER
	RJMP	DONE		;Jump to end
OVER:
	OUT		PORTB, R17	;Output pin2 high on PORTB
DONE:
	RJMP	DONE		;Loop here forever