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
	brne Switch		; Если ещё не дошли до 6, работаем дальше
		clr Razryad	; Сброс регистра
	Switch:
		; switch(Razryad)

			; case(0):
			cpi Razryad, 0
			brne case_1
			in temp, PORTB
			andi temp, ~(0b11000001)
			out PORTB, temp		; Сбрасываем идикаторы порта В
			in temp, PORTD
			andi temp, ~(0b11100000)
			out PORTD, temp		; Сбрасываем индикаторы порта D
			sbi PORTB, T1		; Включаем первый индикатор (Т1)

			case_1:
			cpi Razryad, 1
			brne case_2
			in temp, PORTB
			andi temp, ~(0b11000001)
			out PORTB, temp		; Сбрасываем идикаторы порта В
			in temp, PORTD
			andi temp, ~(0b11100000)
			out PORTD, temp		; Сбрасываем индикаторы порта D
			sbi PORTB, T2		; Включаем второй индикатор (Т2)

			case_2:
			cpi Razryad, 2
			brne case_3
			in temp, PORTB
			andi temp, ~(0b11000001)
			out PORTB, temp		; Сбрасываем идикаторы порта В
			in temp, PORTD
			andi temp, ~(0b11100000)
			out PORTD, temp		; Сбрасываем индикаторы порта D
			sbi PORTD, T3		; Включаем третий индикатор (Т3)

			case_3:
			cpi Razryad, 3
			brne case_4
			in temp, PORTB
			andi temp, ~(0b11000001)
			out PORTB, temp		; Сбрасываем идикаторы порта В
			in temp, PORTD
			andi temp, ~(0b11100000)
			out PORTD, temp		; Сбрасываем индикаторы порта D
			sbi PORTD, T4		; Включаем четвёртый индикатор (Т4)

			case_4:
			cpi Razryad, 4
			brne case_5
			in temp, PORTB
			andi temp, ~(0b11000001)
			out PORTB, temp		; Сбрасываем идикаторы порта В
			in temp, PORTD
			andi temp, ~(0b11100000)
			out PORTD, temp		; Сбрасываем индикаторы порта D
			sbi PORTD, T5		; Включаем пятый индикатор (Т5)

			case_5:
			cpi Razryad, 5
			brne End_Switch
			in temp, PORTB
			andi temp, ~(0b11000001)
			out PORTB, temp		; Сбрасываем идикаторы порта В
			in temp, PORTD
			andi temp, ~(0b11100000)
			out PORTD, temp		; Сбрасываем индикаторы порта D
			sbi PORTB, T6		; Включаем шестой индикатор (Т5)

	End_Switch:
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
