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
#define USART_BAUDRATE 19200
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define UDREn 0x20		//Bit de buffer vacio en status_control_a
#define TXCn  0x40		//Bit de transmision terminada en status_control_a
#define RXCn  0x80		//Bit de recepcion completa en status_control_a



typedef struct
{
	uint8_t status_control_a;    /* ucsr0a USART Control and Status A */		//Tienen que estar en el mismo orden de la memoria!
	uint8_t status_control_b;    /* ucsr0a USART Control and Status B */		//    (Ver datasheet pag 612)
	uint8_t status_control_c;    /* ucsr0a USART Control and Status C */
	uint8_t reserved;			//Este tiene que estar para que el baudrate y siguientes esten bien ubicados en la memoria
	uint8_t baudrate_l;			 /* UBRRLn USART Baud Rate Registers */
	uint8_t baudrate_h;			 /* UBRRLn USART Baud Rate Registers */
	uint8_t data_es;    /* udr0 i/o data */
} volatile uart_t;

 

class SCC
{
    public:        
        SCC();

        void  reset(int channel);
        void  init(int channel, unsigned long baudRate, CircBuf * pTxQueue, CircBuf * pRxQueue);

        void  txStart(int channel);
        void  rxStart(int channel);
        void  serial_put_char (char outputChar);	
		char  serial_get_char(void);
		int	  get_Count(int channel);
		//uart_t *puerto_serial; 
		static void interrupt(void);
    //private:    //Funciones y variables para usar el 232 del mini pro (hechos en el tp2)
		//void serial_put_char (char outputChar);	
		//char serial_get_char(void);
		//uart_t *puerto_serial; 		/* puntero a la estructura de los registros del periferico */
//        static void interrupt  Interrupt(void);
};




#endif /* _SCC_H */

