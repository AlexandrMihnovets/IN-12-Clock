/*
 * macro.inc
 *
 *  Created: 21.03.2023 14:18:59
 *   Author: MikhnovetsA
 */ 

 .macro Delay	; Задержка на пустых циклах
		ldi Razr1, @0
		ldi Razr0, @0	; Младший байт задержки
	R_sub:
		subi Razr0, 1	; Вычесть 1
		sbci Razr1, 0	; Вычесть заём
	brcc R_sub
.endm