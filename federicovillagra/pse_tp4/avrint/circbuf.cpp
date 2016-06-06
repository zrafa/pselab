/**********************************************************************
 *
 * Filename:    circbuf.cpp
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

#include <circbuf.h>

/**********************************************************************
 *
 * Method:      CircBuf()
 *
 * Description: Create a circular buffer.
 *
 * Notes:
 *
 * Returns:     None defined.
 *
 **********************************************************************/

CircBuf::CircBuf(int nItems)
{
    size  = nItems;
    array = new item[size];
    head  = 0;
    tail  = 0;
    count = 0;

}   /* CircBuf() */

/**********************************************************************
 *
 * Method:      ~CircBuf()
 *
 * Description: Destroy a circular buffer.
 *
 * Notes:
 *
 * Returns:     None defined.
 *
 **********************************************************************/

CircBuf::~CircBuf(void)
 {
    delete array;
 }   /* ~CircBuf() */

/**********************************************************************
 *
 * Method:      add()
 *
 * Description: Add an item to the buffer.
 *
 * Notes:       It is up to the caller to check isFull() first, since
 *              there is no convenient way to indicate that error.
 *
 * Returns:     None defined.
 *
 **********************************************************************/
void CircBuf::add(item i)
 {
  
  if ( isFull()==0 )
   {
		array[head]=i;
		count=count+1;
		if(head==size){
			if(tail!=0)
				head=0;
  	 }
		else
			head++;
	}
 }   /* add() */


/**********************************************************************
 *
 * Method:      remove()
 *
 * Description: Remove an item from the buffer.
 *
 * Notes:       It is up to the caller to check isEmpty() first, since
 *              there is no convenient way to indicate that error.
 *
 * Returns:     The removed item.
 *
 **********************************************************************/
item CircBuf::remove(void)
{

  item aux=0;
	if(isEmpty()==0){
		if(tail!=head){
			aux=array[tail];
			count=count-1;
			if(tail!=size)
				tail=tail+1;
			else
				tail=0;
		}

	}
	return aux;

}   /* remove() */
