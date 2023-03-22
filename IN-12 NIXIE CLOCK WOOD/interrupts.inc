/*
 * interrupts.inc
 *
 *  Created: 21.03.2023 14:17:43
 *   Author: MikhnovetsA
 */ 
 DS1307_SQW:	; Прерывание от импульса от микросхемы часов (раз в 1 секунду)

ret

TIMER2_COMPARE:

ret

TIMER2_OVF:
	inc Razryad		; Увеличили номер рабочего разряда
	cpi Razryad, 6	; Сравниваем. Если дошли до 6 (т.е.7), обнуляем
	brne Next		; Если ещё не дошли до 6, продолжаем счёт
		clr Razryad	; Сброс регистра
	Next:
	
ret

TIMER1_COMPA:

ret

TIMER1_COMPB:

ret

TIMER1_OVF:

ret

TIMER0_OVF:

ret

ADC_READY:

ret

EE_READY:

ret
