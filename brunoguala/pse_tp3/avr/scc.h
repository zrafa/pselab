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

#include <circbuf.h>

//estructura completa del uart para avr
typedef struct
{
	//Estos son los registros del HW USART asociados al perferico UART
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    /* demas registros */
	
	uint8_t status_control_b;   /* ucsr0b USART Control and Status B */
	uint8_t status_control_c;   /* ucsr0c USART Control and Status C */
	uint8_t _reserved;
	uint8_t baud_rate_l;        /* ubrr0l baud rate low */
	uint8_t baud_rate_h;        /* ubrr0h baud rate high */

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */


class SCC
{
    public:        
        SCC();

        void  reset(int channel);
        void  init(int channel, unsigned long baudRate, CircBuf * pTxQueue, CircBuf * pRxQueue);

        void  txStart(int channel);
        void  rxStart(int channel);
		char serial_get_char();
		void serial_put_char()

    private:    
			uart_t *puerto_serial; //para poder usar el serial en scc
//        static void interrupt  Interrupt(void);
};

#endif /* _SCC_H */

