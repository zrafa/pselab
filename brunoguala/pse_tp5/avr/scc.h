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
#include <avr/io.h>

//Para poder utilizar las macros ISR(vector_interrupcion). Las macros ISR son rutinas que permiten atender interrupciones.
#include <avr/interrupt.h>
#include "stdint.h"

//Mediante estas macros evitamos hacer inclusiones recursivas de archivos .h.
#ifndef _SCC_H
#define _SCC_H

#include "circbuf.h"

//Constantes para establecer la velocidad de transferencia de datos entre el microcontrolador y el periferico USART
#define USART_BAUDRATE 9600
#define F_CPU 16000000UL
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

//Macros para definir mascaras de bits.
#define SERIAL         0xc0 
#define UDR            0xc6
#define UCSRnB         0xc1
#define UDRIEn         0x20
#define RESTAURAR      0xDF
#define RXCIEn         0x80
#define FRAME          0x06

//Estructura completa del USART para avr.
typedef struct
{
	//Estos son los registros del HW USART asociados al perferico UART
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    /* demas registros */
	
	uint8_t status_control_b;   /* ucsr0b USART Control and Status B */ /* Los bits 7 y 6 permiten activar las interrupciones para transmision y recepcion */
	uint8_t status_control_c;   /* ucsr0c USART Control and Status C */
	uint8_t _reserved;
	uint8_t baud_rate_l;        /* ubrr0l baud rate low */
	uint8_t baud_rate_h;        /* ubrr0h baud rate high */

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t; //Es el nombre del nuevo tipo de dato definido para gestionar el periferico USART.

/* puntero a la estructura de los registros del periferico */

class SCC
{
    public:        
        SCC();

        void  reset(int channel);
        void  init(int channel, unsigned long baudRate, CircBuf * pTxQueue, CircBuf * pRxQueue);

        void  txStart(int channel);
        void  rxStart(int channel);

		void activar_tx();

		void activar_rx();

    private:    
			uart_t *puerto_serial; //Para poder usar el serial en scc.
			
//        static void interrupt  Interrupt(void);
};

#endif /* _SCC_H */

