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
    puerto_serial= (uart_t *) (0xc0);
    puerto_serial->status_control_c=0b00000110;	/* Configurar un frame de 8bits, sin bit de paridad y bit de stop */

	puerto_serial->baudrate_l= (((F_CPU/(baudRate*16UL)))-1);
	puerto_serial->baudrate_h=( (((F_CPU/(baudRate*16UL)))-1) >> 8);		/* Configurar los registros High y Low con BAUD_PRESCALE */
	
	puerto_serial->status_control_b=0b00011000;	/* Activar la recepcion y transmision */
    
    
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
	while(txQueue[channel]->isEmpty()!=1)
	{
		//puerto_serial->data_es=txQueue[channel]->remove();
		//serial_put_char(puerto_serial->data_es);
		serial_put_char(txQueue[channel]->remove());
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
	if(rxQueue[channel]->isFull()!=1)
	{
		rxQueue[channel]->add((item)serial_get_char());
	}

}   /* rxStart() */



/* Estas son las rutinas que hicimos en el tp2, para transmitir por 232 en avr */
void
SCC::serial_put_char (char outputChar)		
{
    while((puerto_serial->status_control_a & UDREn)==0);/* Wait until the transmitter is ready for the next character. */
    puerto_serial->data_es=outputChar;    /* Send the character via the serial port. */
	while((puerto_serial->status_control_a & TXCn)==0);	/*Wait until the transmitter flushed all the data */

}
char
SCC::serial_get_char(void)
{
    while((puerto_serial->status_control_a & RXCn)==0);/* Wait for the next character to arrive. */
	return puerto_serial->data_es;  /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
}

