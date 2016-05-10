/**********************************************************************
 *
 * Filename:    scc.cpp
 * 
 * Description: Implementation of the Linux simulator SCC class.  
 *              This class abstracts the behavior of a general serial 
 *              communications controller (two channels).
 *
 * Notes:       
 *
 * 
 * Copyright (c) 1998 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/
#include <circbuf.h>

#include <scc.h>

#include <stdio.h>

CircBuf *  txQueue[2];
CircBuf *  rxQueue[2];


/**********************************************************************
 *
 * Method:      SCC()
 * 
 * Description: Create a new SCC object.
 *
 * Notes:       
 *
 * Returns:     None defined.
 *
 **********************************************************************/
SCC::SCC(void)
{
}


/**********************************************************************
 *
 * Method:      reset()
 * 
 * Description: Reset the serial channel.
 *
 * Notes:       
 *
 * Returns:     None defined.
 *
 **********************************************************************/
void
SCC::reset(int channel)
{
}   /* reset() */


/**********************************************************************
 *
 * Method:      init()
 * 
 * Description: Initialize one of the serial channels for asynchronous
 *              communications.
 *
 * Notes:       Only the baud rate is selectable.  All communications
 *              are assumed to be 8 data bits, no parity, 1 stop bit.
 *
 * Returns:     None defined.
 *
 **********************************************************************/
void
SCC::init(int channel, unsigned long baudRate,
                 CircBuf * pTxQueue, CircBuf * pRxQueue)
{
    //
    // Copy the input and output buffer pointers.
    //
    txQueue[channel] = pTxQueue;
    rxQueue[channel] = pRxQueue;

	//inicializamos el puerto serial, y los demas registros que componen a la estructura
	uart_t *puerto_serial = (uart_t *) (0xc0);

	//Agregamos el contenido de init de serial

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
	//establecemos la velocidad de transferencia de datos entre el 			   microprocesador y el periferico UART
	puerto_serial->baud_rate_h=(uint8_t) (BAUD_PRESCALE >> 8);

	puerto_serial->baud_rate_l=(uint8_t) BAUD_PRESCALE;

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	//para configuar un frame de 8 bits debemos usar la combinacion 011, esto implica setear dos registros : status_control_c y status_control_b.
	puerto_serial->status_control_c=(uint8_t) (0x06);
	
	/* Activar la recepcion y transmicion */
	//me desplazo 2 bits a la izquierda y colocamos 111 en esa posicion
	puerto_serial->status_control_b=(uint8_t) (0x18);

}   /* init() */


/**********************************************************************
 * 
 * Method:      txStart()
 *
 * Description: Kickstart the transmit process after a previous stall.
 *
 * Notes:       It's okay if this gets called too often, since it will
 *              always check the TX_READY flag before writing.  If the
 *              TX_READY flag isn't set, nothing will be done here.
 *
 * Returns:     None defined.
 *
 **********************************************************************/
void
SCC::txStart(int channel)
{
	/* Mientras la cola no está vacía enviar el siguiente byte */
	/* COMPLETAR */
	//Entonces, serial utiliza un objeto scc y a partir del mismo accede a las funciones txStart y rxStart, dentro de getchar y putchar.
	//A su vez las funciones txStart y rxStart utilizan las funciones serial_put_char y serial_get_char del practico anterior.
	//Para que esto pueda funcionar debemos incluir la estructura uart en la definicion scc.h y la signatura de serial_put_char y serial_get_char.
	//Testemos con el Minicom y la placa ProMini.
	while(!(*txQueueu[channel]).isEmpty())
		serial_put_char((*txQueueu[channel]).remove());
}   /* txStart() */


/**********************************************************************
 * 
 * Method:      rxStart()
 *
 * Description: Kickstart the receive process after a previous stall.
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
void
SCC::rxStart(int channel)
{
	/* Obtener el siguiente byte */
	/* COMPLETAR */
	(*rxQueueu[channel]).add(serial_get_char())
}   /* rxStart() */

//Interfaz de serial, para que este disponible en la clase scc

/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    // while ( /* completar con E/S programada */ )
    //     ;

	//usamos la mascara 0x20 porque debemos testear el estado del bit 5 del registro UCSRnA
	//me desplazo 5 bits a la izquierda o coloco en esa posicion un 1
	while(!((puerto_serial->status_control_a & (0x20))==0x20))
		;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
	puerto_serial->data_es=outputChar;
}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;
	//RXC se enncuentra en la posicion 8.
	while(!((puerto_serial->status_control_a & (0x80))==0x80))
		;
    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
	return puerto_serial->data_es;
}



