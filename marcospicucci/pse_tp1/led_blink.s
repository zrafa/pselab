	.file	"led_blink.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
.global	rdd
	.data
	.type	rdd, @object
	.size	rdd, 2
rdd:
	.word	36
.global	rehl
	.type	rehl, @object
	.size	rehl, 2
rehl:
	.word	37
	.text
.global	inicializaLed
	.type	inicializaLed, @function
inicializaLed:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	lds r24,rdd
	lds r25,rdd+1
	lds r18,rdd
	lds r19,rdd+1
	mov r30,r18
	mov r31,r19
	ld r18,Z
	ori r18,lo8(32)
	mov r30,r24
	mov r31,r25
	st Z,r18
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	inicializaLed, .-inicializaLed
.global	cambiaLed
	.type	cambiaLed, @function
cambiaLed:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	lds r24,rehl
	lds r25,rehl+1
	lds r18,rehl
	lds r19,rehl+1
	mov r30,r18
	mov r31,r19
	ld r19,Z
	ldi r18,lo8(32)
	eor r18,r19
	mov r30,r24
	mov r31,r25
	st Z,r18
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	cambiaLed, .-cambiaLed
.global	delay_ms
	.type	delay_ms, @function
delay_ms:
	push r28
	push r29
	rcall .
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 6 */
/* stack size = 8 */
.L__stack_usage = 8
	std Y+6,r25
	std Y+5,r24
	ldd r18,Y+5
	ldd r19,Y+6
	mov r24,r18
	mov r25,r19
	lsl r24
	rol r25
	lsl r24
	rol r25
	add r24,r18
	adc r25,r19
	mov r18,r24
	mov r19,r25
	swap r18
	swap r19
	andi r19,0xf0
	eor r19,r18
	andi r18,0xf0
	eor r19,r18
	sub r18,r24
	sbc r19,r25
	mov r24,r18
	mov r25,r19
	swap r24
	swap r25
	andi r25,0xf0
	eor r25,r24
	andi r24,0xf0
	eor r25,r24
	sub r24,r18
	sbc r25,r19
	lsl r24
	rol r25
	lsl r24
	rol r25
	lsl r24
	rol r25
	clr r26
	sbrc r25,7
	com r26
	mov r27,r26
	std Y+1,r24
	std Y+2,r25
	std Y+3,r26
	std Y+4,r27
	rjmp .L4
.L5:
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	sbiw r24,1
	sbc r26,__zero_reg__
	sbc r27,__zero_reg__
	std Y+1,r24
	std Y+2,r25
	std Y+3,r26
	std Y+4,r27
.L4:
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	sbiw r24,0
	cpc r26,__zero_reg__
	cpc r27,__zero_reg__
	brne .L5
/* epilogue start */
	adiw r28,6
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r29
	pop r28
	ret
	.size	delay_ms, .-delay_ms
.global	main
	.type	main, @function
main:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	rcall inicializaLed
.L7:
	rcall cambiaLed
	ldi r24,lo8(-56)
	ldi r25,0
	rcall delay_ms
	rjmp .L7
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.1"
.global __do_copy_data
