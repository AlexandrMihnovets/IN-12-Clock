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
.def Razr1	 = r18
.def Razr0	 = r19
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
; ������ ���������
Reset:	
	.include "ini.inc"	; ������������� �����, ��������� � �.�.
	
	;sbi PORTC, 2
	;sbi PORTC, 0

	ldi ZL, low(Numbers*2)
	ldi ZH, high(Numbers*2)

	;lpm temp, Z+
	;out PORTC, temp

	ldi temp, $14
	mov HOURS, temp
	ldi temp, $58
	mov MINUTES, temp
	ldi temp, $9c
	mov SECONDS, temp


	;inc r1
	;inc r1
	
    sei					; �������� ���������� ����������

	LOOP:				; �������� ���� ���������
	
		Switch_loop:
				cpi Razryad, 1	; ���� �������� ������ ���������,
				brne Ind_2
				mov temp, HOURS	; ������ �������� �����	
				swap temp		; �������������, �.�. ��� ����� ���� 3-0
				andi temp, $0F	; �������� ���� �������
				out PORTC, temp	; ������������ ����������� �������� �� ����������

			Ind_2:
				cpi Razryad, 2
				brne Ind_3
				mov temp, HOURS
				andi temp, $0F
				out PORTC, temp

			Ind_3:
				cpi Razryad, 3
				brne Ind_4
				mov temp, MINUTES
				swap temp
				andi temp, $0F
				out PORTC, temp

			Ind_4:
				cpi Razryad, 4
				brne Ind_5
				mov temp, MINUTES
				andi temp, $0F
				out PORTC, temp

			Ind_5:
				cpi Razryad, 5
				brne Ind_6
				mov temp, SECONDS
				swap temp
				andi temp, $0F
				out PORTC, temp

			Ind_6:
				cpi Razryad, 6
				brne End_switch_loop
				mov temp, SECONDS
				andi temp, $0F
				out PORTC, temp

		End_switch_loop:
	
    rjmp LOOP

Numbers:
; ������ ���� ��� ����������� (�� �� ������� ��-�� �������� ��������)
;	0	 1	  2	   3	4	 5	  6	   7	8	 9
.db $00, $01, $04, $05, $08, $09, $0C, $0D, $02, $03