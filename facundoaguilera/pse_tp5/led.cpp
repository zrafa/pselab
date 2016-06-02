#include <led.h>




/* Constructor de la clase Led*/

Led::Led(unsigned char * DDR_dir,unsigned char * Port_dir,unsigned char Port_pin){

DDR_X = DDR_dir;    /* direccion de DDRX */
PUERTO_X = Port_dir; /* direccion de PUERTO X*/
led_mask = Port_pin;           /* máscara del led*/

}

/* Inicialización del led */

void
Led::ledInit(){

/* Turn the GPIO pin voltage off, which will light the LED. This should
* be done before the pins are configured. */
*PUERTO_X = *PUERTO_X  & (~ led_mask); // and negado
/* Make sure the LED control pin is set to operate as OUTPUT */
*DDR_X = *DDR_X  | (led_mask);

}

/* Toggle led */
void
Led::ledToggle(){

unsigned char valor_b;
valor_b = *PUERTO_X;
valor_b ^= led_mask;  //or exclusiva en c
*PUERTO_X = valor_b;

}

/* Encender led */
void
Led::led_ON(){
*PUERTO_X = *PUERTO_X | led_mask;
}

/* Apagar led */
void 
Led::led_OFF(){
*PUERTO_X = *PUERTO_X & (~(led_mask));
}

/* delay */
void 
Led::delay_ms(int milliseconds)
{
long volatile cycles = (milliseconds * CYCLES_PER_MS);
while (cycles != 0)
cycles--;
}
