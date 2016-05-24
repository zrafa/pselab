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
#include "circbuf.h"

#include "scc.h"

#include <stdio.h>

#define USART_BAUDRATE 9600
#define F_CPU 16000000UL 
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

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

    txQueue[channel] = pTxQueue;
    rxQueue[channel] = pRxQueue;

unsigned long baud_prescale =(((F_CPU/(baudRate*16UL)))-1);
	
	puerto_serial->baud_rate_h= (uint8_t) (baud_prescale>>8);
	puerto_serial->baud_rate_l= (uint8_t) (baud_prescale);
//paridad desabilitada , 1 bit de stop y 8 bit de longitud y habilito transmisión y recepción
	puerto_serial->status_control_b = (uint8_t) 0x18;
	puerto_serial->status_control_c = (uint8_t) 0x06;
	Transmit_Disable();       /* deshabilitar transmisión*/
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
 while(!(txQueue[channel]->isEmpty()))
 DataReg_intEnable(); 


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

    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;

    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
/*if((puerto_serial->status_control_a & (1<<8))==0x80){
return puerto_serial->data_es;
}*/
puerto_serial->status_control_b = puerto_serial->status_control_b | RXCIE0;
}   /* rxStart() */

/**********************************************************************
 * 
 * Method:      dataRegister_isEmpty()
 *
 * Description: Kickstart the receive process after a previous stall.
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
int   
SCC::DataReg_isEmpty(int channel)
{
return(puerto_serial->status_control_a & UDRE0);
}
/**********************************************************************
 * 
 * Method:      DataReg_intEnable()
 *
 * Description: Habilitar interrupciones por DATA REGISTER EMPTY
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
void  
SCC::DataReg_intEnable(void){      /*habilitar interrupción por DATA REGISTER EMPTY*/
puerto_serial->status_control_b= (puerto_serial->status_control_b) | UDRIE0;

}
/**********************************************************************
 * 
 * Method:      DataReg_intDisable()
 *
 * Description: Deshabilitar interrupciones por DATA REGISTER EMPTY
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
void  
SCC::DataReg_intDisable(void){      /*deshabilitar interrupción por DATA REGISTER EMPTY*/
puerto_serial->status_control_b= (puerto_serial->status_control_b) & (~UDRIE0);

}
/**********************************************************************
 * 
 * Method:      Transmit_Enable()
 *
 * Description: Habilitar Transmisión
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/

void  
SCC::Transmit_Enable (void){
puerto_serial->status_control_b= (puerto_serial->status_control_b) | TXEN; //pongo el bit TXEN en 1
} 
/**********************************************************************
 * 
 * Method:      Transmit_Disable()
 *
 * Description: Deshabilitar Transmisión
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/

void  
SCC::Transmit_Disable(void){
puerto_serial->status_control_b= (puerto_serial->status_control_b) & (~TXEN); //pongo el bit TXEN a 0
}
/**********************************************************************
 * 
 * Method:     serial_put()
 *
 * Description: cargo el buffer de transmisión con un byte
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/

void  
SCC::scc_put (void){
while(!DataReg_isEmpty(0));
puerto_serial->data_es = txQueue[0]->remove();
}

/**********************************************************************
 * 
 * Method:     clear_RxFlag()
 *
 * Description: Borra bandera de interrupción por recepción
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
void  
SCC::clear_RxFlag   (void){

puerto_serial->status_control_b= (puerto_serial->status_control_b) & (~RXC0); //borro bandera de recepción
}

/**********************************************************************
 * 
 * Method:     scc_get()
 *
 * Description: adquiere el dato de la fifo
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/
void 
SCC::scc_get   (void){
while(!(puerto_serial->status_control_a & (0x80)));
char lectura;
lectura=puerto_serial->data_es;
rxQueue[0]->add(lectura);
}

/**********************************************************************
 * 
 * Method:     Rx_Int_Disable
 *
 * Description: deshabilito interrupcion de recepcion
 *
 * Notes:       The caller shou
 * Returns:     None defined.
 *
 **********************************************************************/

void  
SCC::Rx_Int_Disable  (void){

puerto_serial->status_control_b = puerto_serial->status_control_b | (~RXCIE0);

}
