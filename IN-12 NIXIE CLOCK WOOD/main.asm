;
; IN-12 NIXIE CLOCK WOOD.asm
;
; Created: 21.03.2023 13:03:44
; Author : MikhnovetsA (Михновец Александр Владимирович, Россия, г.Челябинск)
; e-mail: sasha_mihnovets@mail.ru
; Программа для часов с газоразряжными индикаторами ИН-12 (6 штук) под управлением микроконтроллера ATmega8 
; и микросхемы часов реального времени DS1307.

; F_CPU = 8 MHz
.device ATmega8
.include "m8def.inc"

; Дефайны и переменные =========================================================================================================
.def SECONDS = r1				; Десятки и единицы секунд в BCD-формате
.def MINUTES = r2				; Десятки и единицы минут в BCD-формате
.def HOURS	 = r3				; Десятки и единицы часов в BCD-формате
.def temp	 = r16				; Временная переменная
.def Razryad = r17				; Для переключения индикаторов (значения от 0 до 5)
;.def Razr1	 = r18
;.def Razr0	 = r19
.def eSec	= r18
.def dSec	= r19
.def eMin	= r20
.def dMin	= r21
.def eHour	= r22
.def dHour	= r23
.equ T1 = 6						; Индикатор десятков часов
.equ T2 = 7						; Индикатор единиц часов
.equ T3 = 5						; Индикатор десятков минут
.equ T4 = 6						; Индикатор единиц минут
.equ T5 = 7						; Индикатор десятков секунд
.equ T6 = 0						; Индикатор единиц секунд

; Таблица векторов прерываний ==================================================================================================
.include "vectors.inc"
; Макросы ======================================================================================================================
.include "macro.inc"
; Обработчики прерываний =======================================================================================================
.include "interrupts.inc"
; Процедуры ====================================================================================================================
.include "procedures.inc"

.DSEG ; Область оперативной памяти ОЗУ =========================================================================================
	.org SRAM_START		; Начало оперативной памяти (за всеми регистрами ввода-вывода)

.CSEG ; Область флэш памяти ПЗУ ================================================================================================

Numbers:
; Массив цифр для дешифратора (не по порядку из-за дурацкой разводки)
;	0	 1	  2	   3	4	 5	  6	   7	8	 9
.db $00, $01, $04, $05, $08, $09, $0C, $0D, $02, $03

; Начало программы
Reset:	
	.include "ini.inc"	; Инициализация стека, перифирии и т.д.
	
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
	
    sei					; Разрешаю глобальные прерывания

	LOOP:				; Основной цикл программы

	ldi ZL, low(Numbers*2)
	ldi ZH, high(Numbers*2)
	
		Switch_loop:
				cpi Razryad, 1	; Если работает первый индикатор,
				brne Ind_2
				add ZL, dHour
				lpm temp, Z
				out PORTC, temp	; устанавливаю необходимое значение на дешифратор

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

