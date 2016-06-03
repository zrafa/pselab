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

#ifndef _CIRCBUF_H
#define _CIRCBUF_H

typedef unsigned char item;

class CircBuf
{
    public:
        CircBuf(int nItems);
        ~CircBuf();

        void  add(item);

        item  remove();

        void  flush();
			                                        
        int   isEmpty();
		
        int   isFull();
        
        void imprimirPosicion(int);

		item getHead();
		
		item getTail();
		
		int getCount();
		
		void imprimirBuf();
		
    private:
        item *  array;
        int     size;
        int     head;
        int     tail;
        int     count;
};

#endif /* _CIRCBUF_H */

