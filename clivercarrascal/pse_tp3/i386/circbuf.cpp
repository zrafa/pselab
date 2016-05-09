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
#include <stdio.h>

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
void
CircBuf::add(item i)
{
	if(isFull()==0)		//Si no esta lleno se agrega el item
	{
		if(isEmpty()==1)	//Si esta vacio se agrega el item donde esta el head, sin incrementar el tail
		{
			array[head]=i;
		}
		else
		{
			if(tail == size-1)	//Si esta en el ultimo elemento del buffer, el item lo pone en el ppio (
			{
				tail=0;
				array[tail]=i;
			}
			else
			{
				tail++;
				array[tail]=i;	//Si no, pone el item en el siguiente elemento normalmente
			}
		}
		count++;	//Hay un elemento mas en el buffer
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
item
CircBuf::remove(void)	/* Elimina el primero que entro (el head) */
{
	item removido=array[head];	//Se guarda lo que se va a eliminar
	array[head]='-';		//Lo que se elimina se reemplaza por un guion, para que sea visible en el ejemplo
	if(isEmpty()==0)	//Si no esta vacio se va a eliminar
	{
		if(head==size-1)	//Si el head esta en el final del buffer, el head vuelve al ppio
		{
			head=0;
		}
		else
		{
			head++;		//De lo contrario el head se incrementa normalmente
		}
		count--;
	}
	if(isEmpty()==1)	//Si despues de borrar no quedo nada, se pone el head y tail en cero.
	{
		flush();
	}
	return removido;
}   /* remove() */

void					//Este es el tipo de la funcion flush
CircBuf::flush()	//Se le pone Circbuf porque flush pertenece a la clase CircBuf (igual a las struct)
{
	count=0;
	head=0;
	tail=0;
}
											 
int
CircBuf::isEmpty() 
{
	if(count==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int   
CircBuf::isFull() 
{
	if(size==count)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

item
CircBuf::getHead()
{
	return array[head];
}

item
CircBuf::getTail()
{
	return array[tail];
}

int
CircBuf::getCount()
{
	return count;
}
void
CircBuf::imprimirBuf()
{
	int i;
	for(i=0;i<size;i++)
		printf("%c",array[i]);
	printf("\n");
}
