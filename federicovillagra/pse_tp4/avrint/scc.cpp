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
#include<avr/io.h>
#include <circbuf.h>
#include <avr/interrupt.h>
#include <scc.h>



typedef struct
 {
  uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
  uint8_t status_control_b;    /* ucsr0a USART Control and Status B */
  uint8_t status_control_c;    /* ucsr0a USART Control and Status C */
  uint8_t reserved;  /* Registro reservado */
  uint8_t baud_rate_l;  /* UBBR0L baud rate low */
  uint8_t baud_rate_h;  /* UBBR0H baud rate high */
  uint8_t data_es;  /* udr0 i/o data */
 } volatile uart_t;

uart_t *puerto_serial = (uart_t *) (0xc0);


volatile uint8_t *dato;


#define F_CPU 16000000
#define RECEIVER_ENABLE 0x10
#define TRANSMITTER_ENABLE 0x08
#define RX_INTERRUPT_ENABLE 0x80	//transmision por recepcion
#define	UDRE_INTERRUPT_ENABLE 0x20
#define UDRE_INTERRUPT_DISEABLE 0x00
#define CHARACTER_SIZE_0 0x20
#define CHARACTER_SIZE_1 0x40
#define READY_TO_READ 0x80
#define READY_TO_WRITE 0x20
#define PARITY_ENABLE_ODD 0x30
#define PARITY_ENABLE_EVEN 0x20
#define TWO_STOP_BITS 0x08
#define CHARACTER_SIZE_EIGHT 0x06
int channelglobal;



CircBuf* txQueue[2];
CircBuf* rxQueue[2];


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
	dato= (uint8_t *) (0xc6);

	channelglobal=channel;
   puerto_serial ->baud_rate_l= (uint8_t) ((((F_CPU/(baudRate*16UL)))-1));
   puerto_serial ->baud_rate_h= (uint8_t) ((((F_CPU/(baudRate*16UL)))-1)>>8);
   puerto_serial ->status_control_c= (uint8_t) (CHARACTER_SIZE_EIGHT);
   puerto_serial ->status_control_b= (uint8_t) (TRANSMITTER_ENABLE | RECEIVER_ENABLE | RX_INTERRUPT_ENABLE); //(los bits 3, 4, 6 y 7)
   
	sei();
   //
    // Copy the input and output buffer pointers.
    //
    txQueue[0] = pTxQueue;
    rxQueue[0] = pRxQueue;

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
void SCC::txStart(int channel)
 {
/*
  while (txQueue[channel] -> isEmpty() == 0){
    while ( !((puerto_serial ->status_control_a )& (READY_TO_WRITE) ))
       ;
           puerto_serial -> data_es =txQueue[channel]->remove();
        }
*/

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
void SCC::rxStart(int channel)
 {
/*
   while (!((puerto_serial ->status_control_a )& (READY_TO_READ) ));
      rxQueue[channel]->add(puerto_serial->data_es) ;
*/
 }    /* rxStart() */


/**********************************************************************
 *
 * Method:      INTERRUPT()
 *
 * Description: Initialize interrupt for txStart and rxStart
 * 
 * Notes:       no tiene
 *              
 *
 * Returns:     None defined.
 *
 **********************************************************************/

	ISR(USART_RX_vect){  
	//*(dato)='a';
	
	rxQueue[channelglobal]->add (*dato);

	}   


	ISR(USART_UDRE_vect){	

	*dato =txQueue[channelglobal]->remove();
	
}

