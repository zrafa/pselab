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


//--------------------------------------------------------------------
//							DEFINES
//--------------------------------------------------------------------

#define LED_ROJO (0x20) /* 0b00100000 */
/* Number of decrement-and-test cycles. */
#define CYCLES_PER_MS (9000)
//--------------------------------------------------------------------
//-------------------------------------------------------------------
//							FUNCTIONS
//-------------------------------------------------------------------
void ledInit(void)
{
volatile unsigned char * DDR_B = 0x24; /* direccion de DDR B */
volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
/* Turn the GPIO pin voltage off, which will light the LED. This should
* be done before the pins are configured. */
*(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO); // and negado
/* Make sure the LED control pin is set to operate as OUTPUT */
*(DDR_B) = *(DDR_B) | (LED_ROJO);
}
void ledToggle(void)
{
volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
unsigned char valor_b;
valor_b = *(PUERTO_B);
valor_b ^= LED_ROJO;  //or exclusiva en c
*(PUERTO_B) = valor_b;
}
void delay_ms(int milliseconds)
{
long volatile cycles = (milliseconds * CYCLES_PER_MS);
while (cycles != 0)
cycles--;
}

//----------------------------------------------------------------
//						PROGRAM
//----------------------------------------------------------------
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
	ledInit();
while(1){	ledToggle();
			delay_ms(1000);
	}
return 0;
}
