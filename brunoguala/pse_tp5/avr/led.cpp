

#ifndef F_CPU
#define F_CPU   16000000UL
#endif

#include <led.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

Led::Led(volatile unsigned char *direccion, volatile unsigned char *direccion_led, volatile unsigned char mask){

//Guardamos en puerto la direccion de memoria donde esta mapeado el registro de direcciones PORTB de un pin gpio.
puerto=direccion;

//Guardamos la mascara adecuada para encender o apagar un led.
mascara=mask;

//Habilitamos el pin gpio para salida. Usamos la mascara 0x20, referenciada por la macro HABILITAR_SALIDA.
*puerto |= HABILITAR_SALIDA;

//Configuramos la direccion del registro de estado, 0x25, del led.
led=direccion_led;

}

void
Led::encender(){

*led |= mascara;

}

void
Led::apagar(){

*led &= (~mascara);

}

void
Led::delay(long milisegundos){
	volatile unsigned long n=milisegundos*100;
	volatile int i;
	for(i=0; i <= n; i++)
		;

}

