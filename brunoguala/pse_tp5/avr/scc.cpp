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

//Buffers circulares intermedios en los procesos de transmision y recepcion.
CircBuf *  txQueue[2];
CircBuf *  rxQueue[2];

//Definimos una variable puntero para poder utilizar el registro de datos, data_es, en las macros ISR(vector_interrupcion).
volatile uint8_t * udr;

//Definimos una variable global para poder usar un canal de recepcion o transmision en las macros ISR(vector_interrupcion).
int canal;

//Definimos una variable puntero global para poder usar el registro status_control_b (UCSRnB) en la funcion desactivar_tx.
volatile uint8_t * control_b;


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

	//Inicializamos el puerto serial, y los demas registros que componen a la estructura USART.
	puerto_serial = (uart_t *) SERIAL;

	//Inicializamos un puntero al registro de datos, data_es, para poder utilizarlo dentro de la macro ISR(vector_interrupcion).
	udr=(uint8_t *) UDR;

	//Inicializamos un puntero al registro status_control_b, para poder utilizarlo en la funcion estatica desactivar_tx().
	control_b=(uint8_t *) UCSRnB;

	/* Configurar los registros High y Low con BAUD_PRESCALE */
	//Establecemos la velocidad de transferencia de datos entre el microprocesador y el periferico USART.
	//El registro baud_rate es de 16 bits, por eso debemos configurarlo como height y low.
	puerto_serial->baud_rate_h=(uint8_t) (BAUD_PRESCALE >> 8);

	puerto_serial->baud_rate_l=(uint8_t) BAUD_PRESCALE;

	//Inicializamos una variable global a SCC para poder acceder a un canal de transmision dentro de las macro ISR(vector_interrupcion).
	canal=channel;

	//Configuramos un frame de 8 bits. El frame representa la cantidad de informacion transmitida.
	puerto_serial->status_control_c=(uint8_t) FRAME;

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
	
	while(!(txQueue[channel])->isEmpty()){
		activar_tx();
	}
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

	activar_rx();
	
}   /* rxStart() */

/**********************************************************************
 * 
 * Method:      activar_tx()
 *
 * Description: Activamos interrupciones de transmision por buffer vacio.
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
void 
SCC::activar_tx(){

//Activamos el bit 5 del registro status_control_b (UCSR0b) para interrupciones de transmision mediante buffer vacio
//Utilizamos la mascara 0x20, 0010 0000 o (1 << 5).
//Al mismo tiempo mantenemos parte del estado anterior del registro.
puerto_serial->status_control_b |= UDRIEn;


//No tiene sentido especificar esta sentencia porque la interrupcion se produce cuando el registro de datos esta disponible.
//while(!((puerto_serial->status_control_a & (0x20))==0x20));

}

/**********************************************************************
 * 
 * Method:      desactivar_tx()
 *
 * Description: desactivamos las interrupciones de transmision y mantenemos 
				el estado actual del registro, usamos la mascara 1101 1111
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
static void desactivar_tx(){
  
*control_b = *control_b & RESTAURAR;

}

/**********************************************************************
 * 
 * Method:      activar_rx()
 *
 * Description: Activamos interrupciones de recepcion.
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
void
SCC::activar_rx(){

//Activamos el bit 7 del registro status_control_b para interrupciones de recepcion, utilizando la mascara 0x80 o la convencion (1 << 7).
//Al mismo tiempo mantenenos parte del estado anterior del registro.
puerto_serial->status_control_b |= RXCIEn;

}

/**********************************************************************
 * 
 * Method:      ISR(USART_UDRE_vect)
 *
 * Description: Macro de avr-interrupt para gestionar la transmision 
 *				de datos entre el USART y el microprocesador.
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
ISR(USART_UDRE_vect){

//El momento apropiado para desactivar las interrupciones de recepcion es cuando el registro de datos queda configurado con algun valor. Desactivamos interrupciones de
//transmision para evitar que el sistema embebido guarde algun caracter en el registro de datos.
desactivar_tx();

*udr=(char)(txQueue[canal]->remove());

}

/**********************************************************************
 * 
 * Method:      ISR(USART_RX_vect)
 *
 * Description: Macro de avr-interrupt para gestionar la recepcion de datos 
 *				entre el USART y el microprocesador.
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
ISR(USART_RX_vect){

/* DEBE devolver el valor que se encuentra en el registro de datos de E/S gestionado por el puntero udr */
(*rxQueue[canal]).add(*udr);

//Desactivamos las interrupciones de recepcion y mantenemos el estado actual del registro, usamos la mascara 0x7F (0111 1111) o la convencion (1 << 7)
//puerto_serial->status_control_b=puerto_serial->status_control_b & (0x7f);

}


