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

#include "circbuf.h"

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
CircBuf::add(item i) //considero que tail apunta al ultimo elto del buffer circular
{

	if(isEmpty()){  
			//Agregamos al buffer 1 elto en la posicion cero.
			array[0]=i;
			count++;
			head=0;
			tail=0;	
	}
	else{
			if(isFull()){
				; //Quitamos el mensaje de error porque en el microcontrolador no podemos usar librerias de C.
			}
			else{ //En esta rama sabemos que hay lugar en el buffer. Ese lugar puede estar en cualquier parte del buffer, al pricipio o al final.
			    //Si el tail apunta al ultimo elto. del buffer circular, en la siguiente posicion se puede escribir, pero hay que verificar si no nos salimos de rango.
				tail++;
				if(tail==(size-1)){	
								
					array[tail]=i;
					count++;						
						
				}
				else{ 
					if(tail>(size-1)){ //Si se cumple esta condicion estamos fuera de rango, debemos resetear el tail a la posicion 0. La posicion cero se encuentra
									   //disponible porque ya pasamos la condicion isFull().
						tail=0;
					} 
					//Si tail no esta en la ultima posicion del buffer y hay lugar, escribimos item en la posicion donde se encuentra el tail.
					//Sabemos que hay lugar porque ya pasamos la condicion isFull().
					array[tail]=i;
					count++;
					
					
				}
			}
	}
			  
}   /* add() */

/**********************************************************************
 *
 * Method:      display_buffer()
 * 
 * Description: Remove an item from the buffer.
 *
 * Notes:       It is up to the caller to check isEmpty() first, since
 *              there is no convenient way to indicate that error.
 *
 * Returns:     The removed item.
 *
 **********************************************************************/

void 
CircBuf::display_buffer(void){

	printf("\nHEAD : %d \n", head);
	printf("TAIL : %d \n", tail);
	printf("COUNT : %d \n\n", count);

	display_sin_htc();	

}

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
CircBuf::remove(void)
{
	
	item i;	
	if(isEmpty()){
		i=' ';
	}else{

		i=array[head];
		array[head]=NULL;
	
		if(head == (size-1))
			head=0;
		else
			head++;
	}	
	
	count--;	
	
	//Como el count se decrementa en el paso anterior es posible preguntar si el buffer esta vacio para resetear los atributos head, tail y count. Esto sirve 
	//cuando agregamos un elto al buffer y despues lo eliminamos, en este caso el head queda en una posicion que no es la cero. 
	if(isEmpty()){ //(head==tail && (tail==(size-1)))
		head=0;
		tail=0;
		count=0;
	}

	return i;

}   /* remove() */

/**********************************************************************
 *
 * Method:      isEmpty()
 * 
 * Description: Remove an item from the buffer.
 *
 * Notes:       It is up to the caller to check isEmpty() first, since
 *              there is no convenient way to indicate that error.
 *
 * Returns:     The removed item.
 *
 **********************************************************************/
int
CircBuf::isEmpty(void)
{
	return (count==0);
}

/**********************************************************************
 *
 * Method:      isFull()
 * 
 * Description: Remove an item from the buffer.
 *
 * Notes:       It is up to the caller to check isEmpty() first, since
 *              there is no convenient way to indicate that error.
 *
 * Returns:     The removed item.
 *
 **********************************************************************/
int
CircBuf::isFull(void)
{
	return (count==size);
}

/**********************************************************************
 *
 * Method:      display_sin_htc()
 * 
 * Description: Remove an item from the buffer.
 *
 * Notes:       It is up to the caller to check isEmpty() first, since
 *              there is no convenient way to indicate that error.
 *
 * Returns:     The removed item.
 *
 **********************************************************************/
void
CircBuf::display_sin_htc(void){

	int i;
	char *c=",";
	int item=0;

	printf("[");

	for(i=0; i < size; i++){

		item=array[i];

		if((size - 1) == i)
			c="";		
		
		if(item != NULL){
			printf(" %d %c", item, *c);
		}
		else{
			printf(" # %c", *c);
		}
	}

	printf("]");
	
}


