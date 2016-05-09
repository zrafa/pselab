/**********************************************************************
 *
 * Filename:    main.c
 * 
 * Description: The main program file the serial driver example.
 *
 *
 **********************************************************************/

#include "stdint.h"
#include "serial.h"
#include <avr/io.h>


/**********************************************************************
 *
 * Function:    main
 *
 **********************************************************************/
int main(void)
{
    char rcvChar = 0;
	volatile long cuenta=0;
	DDRB=0x20;
    /* Configure the UART for the serial driver. */
    serial_init();
	PORTB=0x20;
	while(cuenta++<500000);	//Blink de aprox 1seg
	PORTB=0x00;
    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');


    while (rcvChar != 'q')
    {
        /* Wait for an incoming character. */
        rcvChar = serial_get_char();

        /* Echo the character back along with a carriage return and line feed. */
        serial_put_char(rcvChar);
        serial_put_char('\r');
        serial_put_char('\n');
    }

    return 0;
}

