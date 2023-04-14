/*
 * macro.inc
 *
 *  Created: 21.03.2023 14:18:59
 *   Author: MikhnovetsA
 */ 

 ; N = T * fтакт / (r + 2),
 ; где	r - кол-во регистров, каждый регистр - это ещё одна команда sbci.

 .macro Delay	; Задержка на пустых циклах
		ldi Razr1, @0	; Старший байт задержки
		ldi Razr0, @1	; Младший байт задержки
	R_sub:
		subi Razr0, 1	; Вычесть 1
		sbci Razr1, 0	; Вычесть заём, если он появился
	brcc R_sub
.endm