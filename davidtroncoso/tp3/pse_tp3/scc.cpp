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
#include <avr.h>
#include <scc.h>

#include <stdio.h>

#define F_CPU 16000000UL

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define RECIVE_TRANSMIT_ENABLE 0x18
#define PARIDADPAR_2BITSTOP 0x24

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

	puerto_serial= (uart_t *) (0xc0);
	puerto_serial->status_control_b = puerto_serial->status_control_b | RECIVE_TRANSMIT_ENABLE;

	puerto_serial->status_control_c = puerto_serial->status_control_c | PARIDADPAR_2BITSTOP;
	
	puerto_serial->baud_rate_h = BAUD_PRESCALE>>8;
	puerto_serial->baud_rate_l = BAUD_PRESCALE;


    // Copy the input and output buffer pointers.
    //
    txQueue[channel] = pTxQueue;
    rxQueue[channel] = pRxQueue;

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
	while(txQueue[channel]->isEmpty()==0)
		serial_put_char(txQueue[channel]->remove());
		

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
	rxQueue[channel]->add(serial_get_char());
	printf("%c\n",rxQueue[channel]->remove());


}   /* rxStart() */

void serial_put_char (char outputChar)
{
   while(!((puerto_serial->status_control_a & 0x20) == 0x20));
	
	puerto_serial->data_es=outputChar;
  
}

char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
	while((puerto_serial->status_control_a & 0x80) != 0x80);

    // while ( /* completar con E/S programada */ )
    //     ;
	return puerto_serial->data_es;
    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */

}



