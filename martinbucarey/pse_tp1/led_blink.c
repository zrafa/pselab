
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

#define REG_DIR_DAT (0x24)
#define AUX (0x20)
#define REG_H_L (0x25)

 
void delay_ms(int milliseconds){
	long volatile cycles = (milliseconds * 9000);
	while (cycles != 0)
	cycles--;
}
int main(void)
{
	char *rdd;
	char *rhl;

	//*(volatile unsigned char *)REG_DIR_DAT=rdd;
	rdd=(volatile unsigned char *)REG_DIR_DAT;
	rhl=(volatile unsigned char *)REG_H_L;
		*rdd=*rdd|AUX;
		while(1){
			*rhl=*rhl^AUX;	
			delay_ms(1000);
		}
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
}
