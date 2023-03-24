/*
 * vectors.inc
 *
 *  Created: 21.03.2023 14:20:36
 *   Author: MikhnovetsA
 */ 
 .org $000
	rjmp Reset
.org $001
reti;	rjmp DS1307_SQW
.org $003
	rjmp TIMER2_COMPARE
.org $004
	rjmp TIMER2_OVF
.org $006 
	rjmp TIMER1_COMPA
.org $007
	rjmp TIMER1_COMPB
.org $008 
	rjmp TIMER1_OVF
.org $009 
	rjmp TIMER0_OVF
.org $00e
	rjmp ADC_READY
.org $00f
	rjmp EE_READY
.org INT_VECTORS_SIZE
