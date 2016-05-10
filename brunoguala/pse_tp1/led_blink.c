
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los pines 8-13 de
 * arduino 
 */

#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif
 
#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include <stdio.h>

void delay_ms(int milisegundos);
 
int main(void)
{
    /* Ejercicio : Completar este programa ejemplo para habilitar/deshabilitar
     * un GPIO (blink de un led conectado al puerto B de un atmega328p)
     *
     * Paso 1 : Establecer el 5to bit del puerto B como salida
     * (el puerto se puede utilizar como entrada o salida). 
     * Para esto se debe poner en '1' el 5to bit de la dirección 0x24, que 
     * es el la dirección del registro de dirección de los datos del puerto B
     * DDRB (Data Direction Register). El 5to bit estable como entrada o salida
     * el pin del atmega328p que tiene conectado un led en una board arduino
     *
     * Paso 2:
     * Luego, para habilitar/deshabilitar (poner en ALTO/BAJO HIGH/LOW)
     * esa salida específica del puerto B
     * se debe poner en '1' el 5to bit de la dirección 0x25, que es la 
     * dirección del registro que controla el estado HIGH o LOW del 
     * pin de salida. En '1' ese bit enciende el led en una board arduino
     *
     * Poniendo en 0 la dirección anterior pone en LOW el pin de salida (apaga
     * el led)
     */

     /* Escribir un bucle infinito que repita los pasos 1 y 2, con un delay
      * entre el HIGH y LOW, de modo que pueda apreciarse el blink.
      */

     /* Utilice el ejemplo para el mr3020 como referencia de ayuda */

	//printf("Hello World !!!");
	
	//usamos unsigned char porque accedemos a un registro de 8 bis
	
	//volatile se usa para evitar que el comilador optimice codigo	
	volatile unsigned char *puerto_salida=(unsigned char *)0x24;      //000000
	
	//0 0 1 0 0 0 0 0 = 0x20
	unsigned char encender=0x20;
	
	//1 1 0 1 1 1 1 1 = 0xDF,  ~(0x20)
	unsigned char apagar=0xDF;
	//habilitamos el puerto B del atmega328 para salida
	*puerto_salida=(*puerto_salida) | encender;
	
	volatile unsigned char *led=(unsigned char *)0x25;                //000000

	while(1){
		//encendemos el led
		*led=(*led) | encender;

		//establecemos un delay de 1 segundo
		delay_ms(1000);

		//apagamos el led
		*led=(*led) & apagar;

		delay_ms(1000);
	}

}

void delay_ms (int milisegundos){
	volatile int fin=milisegundos*100;
	volatile int i;
	for(i=0; i<=fin; i++){
		
	}
}
