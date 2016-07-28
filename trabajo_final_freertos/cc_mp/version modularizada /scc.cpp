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

#include <avr/io.h>

#include <avr/interrupt.h>

#define RX_INT 0x80
#define TX_INT 0x20//BIT 4

CircBuf *  txQueue[2];
CircBuf *  rxQueue[2];

volatile uint8_t *dato;
unsigned char aux;
int chan=0;
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
    puerto_serial = (uart_t *) (0xc0);
    dato = (uint8_t *) (0xc6) ;
    chan = channel;
    
    txQueue[channel] = pTxQueue;
    rxQueue[channel] = pRxQueue;
    puerto_serial->status_control_c = 0b00000110;
	puerto_serial->baud_rate_l = (((F_CPU/(baudRate*16UL)))-1);
	puerto_serial->baud_rate_h = (((F_CPU/(baudRate*16UL)))-1)>>8;
	puerto_serial->status_control_b = 0b00011000;
	sei();
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
	
	
	puerto_serial->status_control_b = (puerto_serial->status_control_b) | TX_INT;//activo
	
	
    while(txQueue[channel]->isEmpty() != 1){
		//q hacer aca?
	}
	puerto_serial->status_control_b = (puerto_serial->status_control_b) & (~ TX_INT);  //desactivo
	
}   

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
		puerto_serial->status_control_b = (puerto_serial->status_control_b) | RX_INT;//activo
			
//desactivo??
}

// *********************************************************************
/*void
SCC::serial_put_char (char outputChar)
{       
    puerto_serial->data_es = outputChar; // envio dato por puerto serial (lo escribo en el reg de datos de e/s)
}
// *********************************************************************
char
SCC::serial_get_char(void)
{  
   return puerto_serial->data_es;
}
// *********************************************************************
*/


// *********************************************************************
//USART_UDRE_vect        USART Data Register Empty????
ISR(USART_RX_vect){	
	rxQueue[chan]->add(*dato);
}

ISR(USART_UDRE_vect){
	if(txQueue[chan]->isEmpty() != 1){
	*dato = (txQueue[chan]->remove());
	}
}


