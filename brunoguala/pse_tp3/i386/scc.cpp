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
#include "circbuf.h" //<circbuf.h>

#include "scc.h"     //el compilador busca la libreria en el mismo directorio donde se encuentra el archivo que se quiere compilar

#include <stdio.h>

#include <iostream>   //el compilador busca la libreria en un directorio por defecto

CircBuf *  txQueue[2]; //pueden existir varios canales de comunicacion, en este caso 0 y 1
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
{printf("LLegamos a init");
    //
    // Copy the input and output buffer pointers.
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
SCC::txStart(int channel) //envia el item referenciado por head
{printf("Ejecutamos tsStart");
	/* Mientras la cola no está vacía enviar el siguiente byte */
	/* COMPLETAR */
	if(!(*(txQueue[channel])).isEmpty())
		printf("%s", ((*(txQueue[channel])).remove()) );

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
{printf("Ejecutamos rxStart");
	/* Obtener el siguiente byte */
	/* COMPLETAR */
	volatile item c=' ';
	//while(c==0)
	scanf("%c", &c);

	//printf("Caracter leido : %u", c);
	(rxQueue[channel])->add(c);
	//(*txQueue[channel]).add(c);
	//(*rxQueue[channel]).display_buffer();

}   /* rxStart() */


