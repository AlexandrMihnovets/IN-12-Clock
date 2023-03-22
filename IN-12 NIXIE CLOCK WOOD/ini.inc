/*
 * ini.inc
 *
 *  Created: 21.03.2023 14:21:50
 *   Author: MikhnovetsA
 */ 

 ; Инициализация стэка
 ldi temp, high(RAMEND)
 out SPH, temp
 ldi temp, low(RAMEND)
 out SPL, temp

 ; Отключение компаратора
 ldi temp, (1<<ACD)
 out ACSR, temp

 ; Настройка портов ввода-вывода
 ldi temp, (1<<DDB7) | (1<<DDB6) | (1<<DDB0)	; T2, T1, T0 (единицы и десятки часов, единицы секунд соответственно)
 out DDRB, temp

 ldi temp, (1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD1) | (1<<DDD0)	; T5, T4, T3 (Десятки секунд, единицы и десятки минут соответственно)
 out DDRD, temp															; SDA и SCL для инициализации DS1307, потом SDA будет меняться для чтения из DS1307

 ldi temp, (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0)	; A, D, B, C дешифратора
 out DDRC, temp

 ; Настройка АЦП

 ; Настройка внешнего прерывания на INT0 от часов DS1307
 ldi temp, (1<<INT0)	; Прерывание по спаду
 out GICR, temp

 ; Настройка Таймера0

 ; Настройка Таймера1

 ; Настройка Таймера2
