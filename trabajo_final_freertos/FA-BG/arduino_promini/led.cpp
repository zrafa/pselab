

#ifndef F_CPU
#define F_CPU   16000000UL
#endif

#include <led.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

Led::Led(volatile unsigned char *direccion, volatile unsigned char *direccion_led, volatile unsigned char mask){

//Guardamos la direccion de memoria donde esta mapeado el registro de direcciones.
puerto=direccion;

//Guardamos la mascara adecuada para encender o apagar un led.
mascara=mask;

//Habilitamos el pin gpio para salida. Usamos la misma mascara para encender o pagar el led.
*puerto |= mascara;

//Guardamos la direccion del registro de estado.
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

