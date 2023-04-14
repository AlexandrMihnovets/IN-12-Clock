;
; IN-12 NIXIE CLOCK WOOD.asm
;
; Created: 21.03.2023 13:03:44
; Author : MikhnovetsA (�������� ��������� ������������, ������, �.���������)
; e-mail: sasha_mihnovets@mail.ru
; ��������� ��� ����� � �������������� ������������ ��-12 (6 ����) ��� ����������� ���������������� ATmega8 
; � ���������� ����� ��������� ������� DS1307.

; F_CPU = 8 MHz
.device ATmega8
.include "m8def.inc"

; ������� � ���������� =========================================================================================================
.def SECONDS = r1				; ������� � ������� ������ � BCD-�������
.def MINUTES = r2				; ������� � ������� ����� � BCD-�������
.def HOURS	 = r3				; ������� � ������� ����� � BCD-�������
.def temp	 = r16				; ��������� ����������
.def Razryad = r17				; ��� ������������ ����������� (�������� �� 0 �� 5)
;.def Razr1	 = r18
;.def Razr0	 = r19
.def eSec	= r18
.def dSec	= r19
.def eMin	= r20
.def dMin	= r21
.def eHour	= r22
.def dHour	= r23
.equ T1 = 6						; ��������� �������� �����
.equ T2 = 7						; ��������� ������ �����
.equ T3 = 5						; ��������� �������� �����
.equ T4 = 6						; ��������� ������ �����
.equ T5 = 7						; ��������� �������� ������
.equ T6 = 0						; ��������� ������ ������

; ������� �������� ���������� ==================================================================================================
.include "vectors.inc"
; ������� ======================================================================================================================
.include "macro.inc"
; ����������� ���������� =======================================================================================================
.include "interrupts.inc"
; ��������� ====================================================================================================================
.include "procedures.inc"

.DSEG ; ������� ����������� ������ ��� =========================================================================================
	.org SRAM_START		; ������ ����������� ������ (�� ����� ���������� �����-������)

.CSEG ; ������� ���� ������ ��� ================================================================================================

Numbers:
; ������ ���� ��� ����������� (�� �� ������� ��-�� �������� ��������)
;	0	 1	  2	   3	4	 5	  6	   7	8	 9
.db $00, $01, $04, $05, $08, $09, $0C, $0D, $02, $03

; ������ ���������
Reset:	
	.include "ini.inc"	; ������������� �����, ��������� � �.�.
	
	;sbi PORTC, 2
	;sbi PORTC, 0

	
	;lpm temp, Z+
	;out PORTC, temp
	/*
	ldi temp, 0;$14
	mov HOURS, temp
	ldi temp, 0;$58
	mov MINUTES, temp
	ldi temp, 0;$9c
	mov SECONDS, temp
	*/

	clr temp

	;inc r1
	;inc r1
	
    sei					; �������� ���������� ����������

	LOOP:				; �������� ���� ���������

	ldi ZL, low(Numbers*2)
	ldi ZH, high(Numbers*2)
	
		Switch_loop:
				cpi Razryad, 1	; ���� �������� ������ ���������,
				brne Ind_2
				add ZL, dHour
				lpm temp, Z
				out PORTC, temp	; ������������ ����������� �������� �� ����������

			Ind_2:
				cpi Razryad, 2
				brne Ind_3
				add ZL, eHour
				lpm temp, Z
				out PORTC, temp

			Ind_3:
				cpi Razryad, 3
				brne Ind_4
				add ZL, dMin
				lpm temp, Z
				out PORTC, temp

			Ind_4:
				cpi Razryad, 4
				brne Ind_5
				add ZL, eMin
				lpm temp, Z
				out PORTC, temp

			Ind_5:
				cpi Razryad, 5
				brne Ind_6
				add ZL, dSec
				lpm temp, Z
				out PORTC, temp

			Ind_6:
				cpi Razryad, 6
				brne End_switch_loop
				add ZL, eSec
				lpm temp, Z
				out PORTC, temp

		End_switch_loop:
	
    rjmp LOOP

