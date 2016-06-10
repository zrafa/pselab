/**********************************************************************
 *
 * Filename:    circbuf.h
 * 
 * Description: An easy-to-use circular buffer class.
 *
 * Notes:       
 *
 * 
 * Copyright (c) 1998 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include <stdio.h>

#ifndef _CIRCBUF_H
#define _CIRCBUF_H

typedef unsigned char item;

class CircBuf
{
    public:
        CircBuf(int nItems);
        ~CircBuf(); //destructor

		//consideramos que el tail apunta siempre a una posicion vacia        
		void  add(item);

		void display_buffer();

		void display_sin_htc();
				
        item  remove();

        void  flush();
                                                     
        int   isEmpty();

        int   isFull();

    private:
        item *  array; //permite guardar los eltos del buffer circular
        int     size;  //contiene el tamanio del buffer
        int     head;  //apunta al primer elto del buffer
        int     tail;  //apunta al ultimo elto. del buffer
        int     count; //guarda la cantidad de eltos. que actualmente posee el buffer 
};

#endif /* _CIRCBUF_H */

