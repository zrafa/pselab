
led_blink.elf:     formato del fichero elf32-avr


Desensamblado de la sección .data:

00800100 <__data_start>:
  800100:	25 00       	.word	0x0025	; ????

00800102 <rdd>:
  800102:	24 00       	.word	0x0024	; ????

Desensamblado de la sección .text:

00000000 <__vectors>:
   0:	0c 94 34 00 	jmp	0x68	; 0x68 <__ctors_end>
   4:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
   8:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
   c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  10:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  14:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  18:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  1c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  20:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  24:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  28:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  2c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  30:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  34:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  38:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  3c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  40:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  44:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  48:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  4c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  50:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  54:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  58:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  5c:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  60:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>
  64:	0c 94 49 00 	jmp	0x92	; 0x92 <__bad_interrupt>

00000068 <__ctors_end>:
  68:	11 24       	eor	r1, r1
  6a:	1f be       	out	0x3f, r1	; 63
  6c:	cf ef       	ldi	r28, 0xFF	; 255
  6e:	d8 e0       	ldi	r29, 0x08	; 8
  70:	de bf       	out	0x3e, r29	; 62
  72:	cd bf       	out	0x3d, r28	; 61

00000074 <__do_copy_data>:
  74:	11 e0       	ldi	r17, 0x01	; 1
  76:	a0 e0       	ldi	r26, 0x00	; 0
  78:	b1 e0       	ldi	r27, 0x01	; 1
  7a:	ec e2       	ldi	r30, 0x2C	; 44
  7c:	f1 e0       	ldi	r31, 0x01	; 1
  7e:	02 c0       	rjmp	.+4      	; 0x84 <__do_copy_data+0x10>
  80:	05 90       	lpm	r0, Z+
  82:	0d 92       	st	X+, r0
  84:	a4 30       	cpi	r26, 0x04	; 4
  86:	b1 07       	cpc	r27, r17
  88:	d9 f7       	brne	.-10     	; 0x80 <__do_copy_data+0xc>
  8a:	0e 94 8b 00 	call	0x116	; 0x116 <main>
  8e:	0c 94 94 00 	jmp	0x128	; 0x128 <_exit>

00000092 <__bad_interrupt>:
  92:	0c 94 00 00 	jmp	0	; 0x0 <__vectors>

00000096 <inicializaLed>:
  96:	e0 91 02 01 	lds	r30, 0x0102
  9a:	f0 91 03 01 	lds	r31, 0x0103
  9e:	80 81       	ld	r24, Z
  a0:	80 62       	ori	r24, 0x20	; 32
  a2:	80 83       	st	Z, r24
  a4:	08 95       	ret

000000a6 <cambiaLed>:
  a6:	e0 91 00 01 	lds	r30, 0x0100
  aa:	f0 91 01 01 	lds	r31, 0x0101
  ae:	80 81       	ld	r24, Z
  b0:	90 e2       	ldi	r25, 0x20	; 32
  b2:	89 27       	eor	r24, r25
  b4:	80 83       	st	Z, r24
  b6:	08 95       	ret

000000b8 <delay_ms>:
  b8:	cf 93       	push	r28
  ba:	df 93       	push	r29
  bc:	00 d0       	rcall	.+0      	; 0xbe <delay_ms+0x6>
  be:	00 d0       	rcall	.+0      	; 0xc0 <delay_ms+0x8>
  c0:	cd b7       	in	r28, 0x3d	; 61
  c2:	de b7       	in	r29, 0x3e	; 62
  c4:	28 e2       	ldi	r18, 0x28	; 40
  c6:	33 e2       	ldi	r19, 0x23	; 35
  c8:	ac 01       	movw	r20, r24
  ca:	42 9f       	mul	r20, r18
  cc:	c0 01       	movw	r24, r0
  ce:	43 9f       	mul	r20, r19
  d0:	90 0d       	add	r25, r0
  d2:	52 9f       	mul	r21, r18
  d4:	90 0d       	add	r25, r0
  d6:	11 24       	eor	r1, r1
  d8:	aa 27       	eor	r26, r26
  da:	97 fd       	sbrc	r25, 7
  dc:	a0 95       	com	r26
  de:	ba 2f       	mov	r27, r26
  e0:	89 83       	std	Y+1, r24	; 0x01
  e2:	9a 83       	std	Y+2, r25	; 0x02
  e4:	ab 83       	std	Y+3, r26	; 0x03
  e6:	bc 83       	std	Y+4, r27	; 0x04
  e8:	89 81       	ldd	r24, Y+1	; 0x01
  ea:	9a 81       	ldd	r25, Y+2	; 0x02
  ec:	ab 81       	ldd	r26, Y+3	; 0x03
  ee:	bc 81       	ldd	r27, Y+4	; 0x04
  f0:	89 2b       	or	r24, r25
  f2:	8a 2b       	or	r24, r26
  f4:	8b 2b       	or	r24, r27
  f6:	41 f0       	breq	.+16     	; 0x108 <delay_ms+0x50>
  f8:	89 81       	ldd	r24, Y+1	; 0x01
  fa:	9a 81       	ldd	r25, Y+2	; 0x02
  fc:	ab 81       	ldd	r26, Y+3	; 0x03
  fe:	bc 81       	ldd	r27, Y+4	; 0x04
 100:	01 97       	sbiw	r24, 0x01	; 1
 102:	a1 09       	sbc	r26, r1
 104:	b1 09       	sbc	r27, r1
 106:	ec cf       	rjmp	.-40     	; 0xe0 <delay_ms+0x28>
 108:	0f 90       	pop	r0
 10a:	0f 90       	pop	r0
 10c:	0f 90       	pop	r0
 10e:	0f 90       	pop	r0
 110:	df 91       	pop	r29
 112:	cf 91       	pop	r28
 114:	08 95       	ret

00000116 <main>:
 116:	0e 94 4b 00 	call	0x96	; 0x96 <inicializaLed>
 11a:	0e 94 53 00 	call	0xa6	; 0xa6 <cambiaLed>
 11e:	88 ec       	ldi	r24, 0xC8	; 200
 120:	90 e0       	ldi	r25, 0x00	; 0
 122:	0e 94 5c 00 	call	0xb8	; 0xb8 <delay_ms>
 126:	f9 cf       	rjmp	.-14     	; 0x11a <main+0x4>

00000128 <_exit>:
 128:	f8 94       	cli

0000012a <__stop_program>:
 12a:	ff cf       	rjmp	.-2      	; 0x12a <__stop_program>

Desensamblado de la sección .comment:

00000000 <.comment>:
   0:	47 43       	sbci	r20, 0x37	; 55
   2:	43 3a       	cpi	r20, 0xA3	; 163
   4:	20 28       	or	r2, r0
   6:	47 4e       	sbci	r20, 0xE7	; 231
   8:	55 29       	or	r21, r5
   a:	20 34       	cpi	r18, 0x40	; 64
   c:	2e 38       	cpi	r18, 0x8E	; 142
   e:	2e 31       	cpi	r18, 0x1E	; 30
	...
