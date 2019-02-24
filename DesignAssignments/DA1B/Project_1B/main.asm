;
; Project1B.asm
;
; Created: 2/23/2019 6:39:21 PM
; Author : Cody Hudson
;

RESET:
; INITIAL PARAMETERS
.EQU STARTADDS = 0X0200
.EQU COUNT = 99

.ORG 0
	LDI XL, LOW(STARTADDS)		;INITIALIZES [X] = 0X0200
	LDI XH, HIGH(STARTADDS)
	LDI YL, LOW(0X400)			;INITIALIZES [Y] = 0X0400
	LDI YH, HIGH(0X400)
	LDI ZL, LOW(0X600)			;INITIALIZES [Z] = 0X0600
	LDI ZH, HIGH(0X600)

	; INITILIZING COUNT REGISTERS
	LDI R21, COUNT				;R21 = 99
	LDI R22, 10					;R22 = 10 STARTING POINT OF COUNTER
	LDI R20, 3					;R20 = 3
	LDI R23, 1

	; CLEARING REGISTERS FOR SUMS
	CLR R0						;R0  = 0					
	CLR R16						;R16 = 0
	CLR R17						;R17 = 0
	CLR R18						;R18 = 0
	CLR R19						;R19 = 0

START:
	; ADDING LOWER AND UPPER ADDRESS BITS TO BE STORED
	MOV R1, XL					;R1 = XL
	ADD R1, XH					;R1 = XH + XL
	MOV R3, R1					;R3 = R1
	ADD R3, R22					;R3 = 10 + R3 
	ST X+, R3					;STORES VALUE OF R3 INTO INCRIMENTED "X" POINTER OF STACK


DIVBYTHREE:
	; CHECKING IF DIVISABLE BY 3
	CP R1, R20					
	BRLO DIVBAD					;IF R1 < 3 GOTO DIVBAD
	SUB R1, R20					;R1 - 3
	CP R1, R0					
	BREQ DIVGOOD				;IF R1 = 0 GOTO DIVGOOD
	RJMP DIVBYTHREE				;GO BACK TO DIVBYTHREE

DIVGOOD:
	; STORING VALUES IN STACK USING "Z" POINTER IF DIVISABLE BY 3 AND SUMMING TOGETHER
	SUB R3, R23					;TANKING IN ACOUNT THTAT R3 IS BING INCRIMENTED IN THE NEXT LINE R3=R3-1
	ST Z+, R3					;STORES VALUE OF R3 INTO INCRIMENTED "Z" POINTER OF STACK
	ADD R16, R3					;R16 = ZH + ZL
	ADC R17, R0					;R17 = CARRY VALUE FROM LINE ABOVE
	CP R21, R0					
	BREQ LVDIVGOOD				;IF R21 = 0 ADD LAST VALE
	RJMP DONE					;GO TO DONE

DIVBAD: 
	; STORING VALUES IN STACK USING "Y" POINTER IF NOT DIVISABLE BY 3 AND SUMMING TOGETHER
	SUB R3, R23					;TANKING IN ACOUNT THTAT R3 IS BING INCRIMENTED IN THE NEXT LINE R3=R3-1
	ST Y+, R3					;STORES VALUE OF R3 INTO INCRIMENTED "Y" POINTER OF STACK
	ADD R18, R3					;R18 = YH + YL
	ADC R19, R0					;R19 = CARRY VALUE FROM LINE ABOVE
	CP R21, R0					
	BREQ LVDIVBAD				;IF R21 = 0 ADD LAST VALE
	RJMP DONE					;GO TO DONE

DONE:
	SUBI R21, 1					;R21 = 21 - 1
	BRNE START					;IF R21 != 0 GO BACK TO START

 
LVDIVGOOD:
	;NEEDED TO INCLUDE 100TH VALUE IF DIVISABLE BY 3
	INC R3						;R3 = R3 + 1 
	ADD R18, R3					;ADD LAST VALUE
	ADC R19, R0					;CHECK FOR ANY LAST CARRYS
	RJMP FIN					;FINALLY DONE

LVDIVBAD:
	;NEEDED TO INCLUDE 100TH VALUE IF NOT DIVISABLE BY 3
	INC R3						;R3 = R3 + 1 
	ADD R18, R3					;ADD LAST VALUE 
	ADC R19, R0					;CHECK FOR ANY LAST CARRYS
	RJMP FIN					;FINALLY DONE

FIN:
	RJMP FIN					;ENDLES LOOP TO SHOW FINISH

