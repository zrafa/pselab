
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los pines 8-13 de
 * arduino 
 */

#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif
#include <stdio.h> 
#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()

#define LED_MASK (0x20)
#define REG_DIR_DAT (0x24)
#define REG_ESTADO_HIGH_LOW (0x25)

uint8_t volatile *rdd = (uint8_t volatile *)REG_DIR_DAT ;
uint8_t volatile *rehl = (uint8_t volatile *)REG_ESTADO_HIGH_LOW ;

void inicializaLed(){
	*rdd = (*rdd) | (LED_MASK) ;
}

void cambiaLed(){
	*rehl = (*rehl) ^ (LED_MASK) ;
}

void delay_ms(int ms){
	long volatile ciclos = ms * 9000;
	while(ciclos != 0){
		ciclos --;	
	}
}

int main(void)
{
	inicializaLed();
	//printf(" check this\n");
	while (1){
		cambiaLed();
		delay_ms(200);//parpadea a las chapas
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
