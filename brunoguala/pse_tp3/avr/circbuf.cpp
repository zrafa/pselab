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

	if(isEmpty()){  //ahora, el buffer tiene 1 elto.
			array[0]=i;
			count++;
			head=0;
			tail=0;	
	}
	else{
			if(isFull()){
				; //quitamos el mensaje de error porque en el microcontrolador no podemos usar librerias de c 
			}
			else{ //en esta rama sabemos que hay lugar en el buffer
				tail++;
				if(tail==(size-1)){	//la ultima posicion del buffer puede estar disponible u ocupada
					
					//if(!isFull()){ //si tail esta en la ultima posicion del buffer y hay lugar en el mismo debemos llevar a tail a posicion cero, y escribir en ese lugar un item
						//tail=0;
					//}
			
					array[tail]=i;
					count++;						

					//si existe head desplazado, debemos cambiar la posicion del tail a 0. Caso contrario tail debe quedar en la misma posicion porque el buffer 
					//esta completo
					//if(head > 0){
						//tail=0;
					//}
						
				}
				else{ 
					if(tail>(size-1)){
						tail=0;
					} //si tail no esta en la ultima posicion del buffer y hay lugar en el mismo debemos escribir item en la posicion donde se encuentra el tail
					
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
	
	if(head==tail && (tail==(size-1))){
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


