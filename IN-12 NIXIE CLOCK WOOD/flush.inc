/*
 * flush.inc
 *
 *  Created: 28.04.2023 12:36:06
 *   Author: MikhnovetsA
 */ 

 RAM_Flush:							; Очистка памяти от мусора	
			LDI  ZL,Low(SRAM_START)		; Адрес начала ОЗУ в индекс 
			LDI  ZH,High(SRAM_START) 
			CLR  R16					; Очищаем R16 
	Flush:    
			ST   Z+,R16					; Сохраняем 0 в ячейку памяти 
			CPI  ZH,High(RAMEND+1)		; Достигли конца оперативки? 
			BRNE  Flush					; Нет? Крутимся дальше! 
  
			CPI  ZL,Low(RAMEND+1)		; А младший байт достиг конца? 
			BRNE  Flush 
  
			CLR  ZL						; Очищаем индекс 
			CLR  ZH

			LDI  ZL, 30					; Адрес самого старшего регистра   
			CLR  ZH						; А тут у нас будет ноль 
			DEC  ZL						; Уменьшая адрес 
			ST  Z, ZH					; Записываем в регистр 0 
			BRNE  PC-2					; Пока не перебрали все не успокоились