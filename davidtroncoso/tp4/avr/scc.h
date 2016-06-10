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



/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */


class SCC
{

    public:
        SCC();

        void  reset(int channel);
        void  init(int channel, unsigned long baudRate, CircBuf * pTxQueue, CircBuf * pRxQueue);

        static void  txStart(int channel);
        static void  rxStart(int channel);



//        static void interrupt  Interrupt(void);
};

#endif /* _SCC_H */
