
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
	volatile unsigned char *pa7_salida=(unsigned char *)0x21;      //000000
	
	
	//1 0 0 0 0 0 0 0 = 0x80, mascara para encender el led
	unsigned char encender=0x80;
	
	//0 1 1 1 1 1 1 1 = 0xDF, mascara para apagar el led
	unsigned char apagar=0x7F;
	//habilitamos el puerto PA7 del atmega1284p para salida
	*pa7_salida=(*pa7_salida) | encender;
	
	//configuramos la direccion del led verde y rojo
	volatile unsigned char *pa7=(unsigned char *)0x22;                //000000
	
	volatile unsigned char *pb7_salida=(unsigned char *)0x23;
	*pb7_salida=(*pb7_salida) | encender;

	volatile unsigned char *pb7=(unsigned char *)0x24;	

	while(1){
		//encendemos el led
		*pa7=(*pa7) | encender;

		//establecemos un delay de 1 segundo
		delay_ms(3000);

		//apagamos el led. S
		*pa7=(*pa7) & apagar;

		delay_ms(3000);

		*pb7=(*pb7) | encender;

		delay_ms(3000);

		*pb7=(*pb7) & apagar;

		delay_ms(3000);

		
	}

}

void delay_ms (int milisegundos){
	//para ajustar el tiempo debemos usar un numero de 64 bits, para que se pueda apreciar la intermitencia
	volatile unsigned long long fin=milisegundos*6000;
	volatile int i;
	for(i=-2000; i<=fin; i++){
		
	}
}
