/*
 * interrupts.inc
 *
 *  Created: 21.03.2023 14:17:43
 *   Author: MikhnovetsA
 */ 
DS1307_SQW:	; Прерывание от импульса от микросхемы часов (раз в 1 секунду)
	;inc SECONDS
	;cpi
reti
; ==========================================================================================================
TIMER2_COMPARE:		; В прерывании по совпадению Таймера 2 происходит выключение индикатора,
					; соответствующего номеру в переменной Razryad. 
	; switch(Razryad)
		; case(0):
			cpi Razryad, 0		; При первом прерывании тут делать нечего, пока ни один индаикатор не горит
			breq End_switch_2	; так что на выход
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

	ldi ZL, low(Numbers*2)	; В Z адрес цифр во флэш памяти в порядке возрастания
	ldi ZH, high(Numbers*2)	; каждый цикл обнуляется

	Switch:			; switch(Razryad)
		case_0:
			cpi Razryad, 0
			brne case_1
			lds temp, Hour_h_BCD
			rcall Find_num_in_flash_and_set_to_PORTC
			sbi PORTB, T1		; Включаем первый индикатор (Т1)
			rjmp End_switch

		case_1:
			cpi Razryad, 1
			brne case_2
			lds temp, Hour_l_BCD
			rcall Find_num_in_flash_and_set_to_PORTC
			sbi PORTB, T2		; Включаем второй индикатор (Т2)
			rjmp End_switch

		case_2:
			cpi Razryad, 2
			brne case_3
			lds temp, Min_h_BCD
			rcall Find_num_in_flash_and_set_to_PORTC
			sbi PORTD, T3		; Включаем третий индикатор (Т3)
			rjmp End_switch

		case_3:
			cpi Razryad, 3
			brne case_4
			lds temp, Min_l_BCD
			rcall Find_num_in_flash_and_set_to_PORTC
			sbi PORTD, T4		; Включаем четвёртый индикатор (Т4)
			rjmp End_switch

		case_4:
			cpi Razryad, 4
			brne case_5
			lds temp, Sec_h_BCD
			rcall Find_num_in_flash_and_set_to_PORTC
			sbi PORTD, T5		; Включаем пятый индикатор (Т5)
			rjmp End_switch

		case_5:
			cpi Razryad, 5
			brne End_switch
			lds temp, Sec_l_BCD
			rcall Find_num_in_flash_and_set_to_PORTC
			sbi PORTB, T6		; Включаем шестой индикатор (Т6)

	End_switch:	
		
		inc Razryad				; Переключили разряд
reti
; ==========================================================================================================
TIMER1_COMPA:	; Таймер настроен на прерывание раз в секунду. Потом этот обработчик надо перенести в прерывание по Int0
	; Инкрементируем секунды
	inc Sec_counter				; Через секунду прибавили 1 к секундам
	cpi Sec_counter, 60			; Проверка на переполнение секунд
	brne Sec_exit				; Нет переполнения, минуты и часы не трогаем
	; Инкрементируем минуты, если было переполнение секунд
	clr Sec_counter				; Обнуляем счётчик секунд
	inc Min_counter				; Прибавили минуту
	cpi Min_counter, 60			; Проверка на переполнение минут
	brne Min_exit				; Нет переполнения, часы не трогаем
	; Инкрементируем часы, если было переполнение минут
	clr Min_counter				; Обнуляем счётчик минут
	inc Hour_counter			; Прибавили часы
	cpi Hour_counter, 24		; Проверка на переполнение часов
	brne Hour_exit				; Если нет переполнеия, не обнуляем
	clr Hour_counter			; ...иначе, обнуляем

	Hour_exit:					; Преобразование HEX часов в BCD
	mov temp, Hour_counter		; Значение часов в temp
	rcall bin2bcd8				; На выходе в temp1 десятки, в temp единицы часов
	ldi YL, low(Hour_l_BCD)		; Адрес единиц часов в индекс
	rcall Save_BCD_to_SRAM		; Сохраняем распакованные и упакованные BCD в ОЗУ

	Min_exit:
	mov temp, Min_counter		; Значение минут в temp
	rcall bin2bcd8				; На выходе в temp1 десятки, в temp единицы минут
	ldi YL, low(Min_l_BCD)		; Адрес единиц минут в индекс
	rcall Save_BCD_to_SRAM		; Сохраняем распакованные и упакованные BCD в ОЗУ

	Sec_exit:
	mov temp, Sec_counter		; Значение секунд в temp
	rcall bin2bcd8				; На выходе в temp1 десятки, в temp единицы минут
	ldi YL, low(Sec_l_BCD)		; Адрес единиц секунд в индекс
	rcall Save_BCD_to_SRAM		; Сохраняем распакованные и упакованные BCD в ОЗУ

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
