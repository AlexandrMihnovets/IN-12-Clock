/*
 * interrupts.inc
 *
 *  Created: 21.03.2023 14:17:43
 *   Author: MikhnovetsA
 */ 
DS1307_SQW:	; Прерывание от импульса от микросхемы часов (раз в 1 секунду)

reti
; ==========================================================================================================
TIMER2_COMPARE:		; В прерывании по совпадению Таймера 2 происходит выключение индикатора,
					; соответствующего номеру в переменной Razryad. 
	; switch(Razryad)
		; case(0):
			cpi Razryad, 1
			brne case_11
			cbi PORTB, T1
			rjmp End_switch_2

		case_11:
			cpi Razryad, 2
			brne case_21
			cbi PORTB, T2
			rjmp End_switch_2

		case_21:
			cpi Razryad, 3
			brne case_31
			cbi PORTD, T3
			rjmp End_switch_2

		case_31:
			cpi Razryad, 4
			brne case_41
			cbi PORTD, T4
			rjmp End_switch_2

		case_41:
			cpi Razryad, 5
			brne case_51
			cbi PORTD, T5
			rjmp End_switch_2

		case_51:
			cpi Razryad, 6
			brne End_switch_2
			cbi PORTB, T6

			clr Razryad		; Если номер разряда стал равен 6, обнуляем его
	
	End_switch_2:
			
reti
; ==========================================================================================================
TIMER2_OVF:			; При переполнении Таймера 2 происходит включение индикатора, соответствующего 
					; переменной Razryad - 1 (0 - это Т1 и т.д.), выключаются индикаторы в прерывании
					; по совпадению Таймера 2.

	Switch:			; switch(Razryad)
		case_0:
			cpi Razryad, 0
			brne case_1
			sbi PORTB, T1		; Включаем первый индикатор (Т1)
			rjmp End_switch

		case_1:
			cpi Razryad, 1
			brne case_2
			sbi PORTB, T2		; Включаем второй индикатор (Т2)
			rjmp End_switch

		case_2:
			cpi Razryad, 2
			brne case_3
			sbi PORTD, T3		; Включаем третий индикатор (Т3)
			rjmp End_switch

		case_3:
			cpi Razryad, 3
			brne case_4
			sbi PORTD, T4		; Включаем четвёртый индикатор (Т4)
			rjmp End_switch

		case_4:
			cpi Razryad, 4
			brne case_5
			sbi PORTD, T5		; Включаем пятый индикатор (Т5)
			rjmp End_switch

		case_5:
			cpi Razryad, 5
			brne End_switch
			sbi PORTB, T6		; Включаем шестой индикатор (Т6)

	End_switch:	
		
		inc Razryad				; Переключили разряд,

reti
; ==========================================================================================================
TIMER1_COMPA:

reti

TIMER1_COMPB:

reti

TIMER1_OVF:

reti

TIMER0_OVF:

reti

ADC_READY:

reti

EE_READY:

reti
