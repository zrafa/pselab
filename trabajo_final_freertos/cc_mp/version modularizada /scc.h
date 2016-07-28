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
#include <avr/io.h>


#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define UDREn 0x20
#define TXCn 0x40
#define RXCn 0x80


#define LED_MASK (0x20)
#define REG_DIR_DAT (0x24)
#define REG_ESTADO_HIGH_LOW (0x25) 

typedef struct
{
    uint8_t status_control_a;    // ucsr0a USART Control and Status A  (0xC0)
    uint8_t status_control_b;   // ucsr0b (0xC1)
    uint8_t status_control_c;	// ucsr0c (0xC2)
    uint8_t reserved;           // (0xC3)
    uint8_t baud_rate_l;        // ubrr0l (0xC4)
    uint8_t baud_rate_h;	// ubrr0h (0xC5)
    uint8_t data_es;    // udr0 i/o data (0xC6)

} volatile uart_t;


class SCC
{
    public:        
        SCC();

        void  reset(int channel);
        void  init(int channel, unsigned long baudRate, CircBuf * pTxQueue, CircBuf * pRxQueue);

        void  txStart(int channel);;
        void  rxStart(int channel);

		void desactivarUART();
		void activarUART();
		
		void serial_put_char (char outputChar);
		char serial_get_char(void);
		
		//static void interrupt  Interrupt(void);//publico o privado?
	private:
		uart_t *puerto_serial ;	
		
};

#endif /* _SCC_H */

