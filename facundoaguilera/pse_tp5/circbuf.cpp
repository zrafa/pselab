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
CircBuf::add(item i)
{

	/* Si el Buffer esta lleno, no hay lugar en la cola para colocar los datos*/
		if(isFull()){ printf("ERROR : BUFFER COMPLETO "); }
		/*Si el Buffer está vacío el elemento se coloca en la 1° posición de la cola
		* Y se incrementan count y tail
		*/
		else if (isEmpty()){
		array[0]=i;
		count=1;
		head=0; 		//primer elemento no vacío
		tail=count;
						}
		/*Si la cola tiene más de dos espacios vacíos (a la derecha de la cola)
		 *el elemento se coloca donde apunta tail y se incrementan tail y count
		*/
		else if (tail< size-1){ 
		array[tail]=i;
		tail++;
		count++;
		/*Si la cola sólo tiene el último espacio libre a la derecha, el elemento se coloca en ese
		 *último espacio. 
		*/						}
		else if(tail== size-1){
		array[tail]=i;
		/*Si hay espacio al principio de la cola (a la izquierda del buffer), tail se pone a 0, y count
		* es igual al tamaño de la cola menos la cabecera head.
		*/	
		if(head>0){
		tail=0;
		count=size-head;
					}
		/*Si no hay espacio a la izquierda del buffer, tail se pone a 0 y count es igual al tamaño del buffer, o sea, el buffer 
		está lleno
		*/
		if(head==0){tail=0;
					count=size;
					
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
	int item=array[head];
	array[head]=NULL;
	
	if(isEmpty()){
		item=-1;
	}else
	{
	if(head==(size-1)){
	head=0;
			}
	else { head++; 
	count--;}
	return item;
	}
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
	return (count==0);//si la condición es verdadera devuelve 1 si no 0
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
/**********************************************************************
 *
 * Method:      flush()
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
CircBuf::flush(void)
{
	
}


