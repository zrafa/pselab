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





typedef struct
{

  	uint8_t status_control_a;	/* ucsr0a USART Control and Status A (0xc0) */
	uint8_t status_control_b;	/* ucsr0b USART Control and Status B (0xC1) */
	uint8_t status_control_c; 	/* ucsr0c USART Control and Status C (0xC2) */
	uint8_t _reserved;			/* espacio sin utilizar (0xC3) */
	uint8_t baud_rate_l;		/* ubrr0l baud rate low (0xC4)*/
	uint8_t baud_rate_h;		/* ubrr0h baud rate high (0xC5) */
	uint8_t data_es; 			/* udr0 i/o data (0xC6) */

} volatile uart_t;


/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);


#define F_CPU 16000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define REC_ENEABLE 0x10
#define TRANS_ENEABLE 0x08
#define NOPARIDAD_1BITSTOP 0x04
#define INT_REC_EN 0x80
#define INT_UDR_EN 0x20
#define BUF_VACIO 0x20

int i=1;


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
    // Copy the input and output buffer pointers




	puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE>>8);
	puerto_serial->baud_rate_l = (unsigned char)BAUD_PRESCALE;

	puerto_serial->status_control_c |= NOPARIDAD_1BITSTOP;

	puerto_serial->status_control_b |= REC_ENEABLE;		// Habilito recepción



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

	/* si hay algo para transmitir habilito la interrupcion para transmisión */

	if(txQueue[channel]->isEmpty()==0)
		{

			puerto_serial->status_control_b |= INT_UDR_EN;			// Habilito interrupción para transmisión
	
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
	puerto_serial->status_control_b |= REC_ENEABLE;			// Habilito recepción

	puerto_serial->status_control_b |= INT_REC_EN;			// Habilito interrupcion para recepción





}   /* rxStart() */




/**********************************************************************
 *
 * Method:      ISR(USART_UDRE_vect)
 *
 * Description: .
 *
 * Notes:
 *
 * Returns:     .
 *
 **********************************************************************/
ISR(USART_UDRE_vect)
{


		UCSR0B=(0<<UDRIE0);			// Deshabilito interrupcion para transmisión


		puerto_serial->status_control_b |= TRANS_ENEABLE;			// Habilito transmisión



		puerto_serial->data_es=(txQueue[0]->remove()); 		// Envío el dato



	// Espero a que el dato termine de ser enviado.
	while ( !(( puerto_serial->status_control_a & BUF_VACIO) == BUF_VACIO) )
		;



} /* ISR(USART_UDRE_vect) */





/**********************************************************************
 *
 * Method:      ISR(USART_RX_vect)
 *
 * Description: .
 *
 * Notes:
 *
 * Returns:     .
 *
 **********************************************************************/


ISR(USART_RX_vect)
{


		rxQueue[0]->add(puerto_serial->data_es);		// Guardo el dato recibido en el buffer


} /* ISR(USART_RX_vect) */





