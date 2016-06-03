/**********************************************************************
 *
 * Filename:    scc.h
 * 
 * Description: 
 *
 * Notes:       
 *
 * 
 * Copyright (c) 1998 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#ifndef _SCC_H
#define _SCC_H

#include <avr/io.h>

/* definiciones para transmisión */

#define UDRE0        (1<<5)	// 1 if DATA REGISTER is EMPTY  								está en el status_control_a
#define TXC0         (1<<6) // 1 if TRANSMIT COMPLETE										está en el status_control_a
#define TXEN         (1<<3) // habilitar transmisión                						está en el status_control_b
#define UDRIE0       (1<<5) //if 1 ENABLE DATA REGISTER EMPTY INTERRUPT 					está en el status_control_b

/* definiciones para recepción */
#define RXC0         (1<<7) // reception flag: 1 if there is unread data in the FIFO e		está en el status_control_a
#define RXCIE0		 (1<<7) // if 1 ENABLE RX Complete Interrupt 							está en el status_control_b
/*
USART_RXC
USART_UDRE 
*/





typedef struct
{
uint8_t status_control_a;	/* ucsr0a USART Control and Status A */
uint8_t status_control_b;	/* ucsr0b USART Control and Status B */
uint8_t status_control_c;	/* ucsr0c USART Control and Status C */
uint8_t _reserved;			/* espacio sin utilizar */
uint8_t baud_rate_l;		/* ubrr0l baud rate low */;
uint8_t baud_rate_h;		/* ubrr0h baud rate high */
uint8_t data_es; 			/* udr0 i/o data */

} volatile uart_t;


#include "circbuf.h"

class SCC
{
    public:        
        SCC();

        void  reset(int channel);
        void  init(int channel, unsigned long baudRate, CircBuf * pTxQueue, CircBuf * pRxQueue);

        void  txStart(int channel);
        void  rxStart(int channel);
		void  scc_put (void);
		int   DataReg_isEmpty(int channel);
		void  DataReg_intEnable(void);      /*habilitar interrupción por DATA REGISTER EMPTY*/
		void  DataReg_intDisable(void);      /*deshabilitar interrupción por DATA REGISTER EMPTY*/
		void  Transmit_Enable (void);        /*habilitar transmisión*/
		void  Transmit_Disable(void);       /* deshabilitar transmisión*/
		void  clear_RxFlag    (void);       /*borrar bandera de interrupción por recepción*/
		void  scc_get         (void);       /*adquiero el dato de recepción*/
		void  Rx_Int_Disable  (void);       /* deshabilito interrupciones por recepción */
    private:    
	uart_t *puerto_serial = (uart_t *) (0xc0);
//        static void interrupt  Interrupt(void);
};

#endif /* _SCC_H */

