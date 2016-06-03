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

//#include <stdio.h>//0_o
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
 * Notes:       It is up  the caller to check isFull() first, since
 *              there is no convenient way to indicate that error.
 *
 * Returns:     None defined.
 *
 **********************************************************************/
void
CircBuf::add(item i) // verifico aca o en el que llama a add si esta lleno?
{
	if(isFull() == 0){
		if(isEmpty() == 1){ //si esta vacio head y tail se inicializaron em 0,primera posicion del array, asiq no modifico
			array[head] = i;	
		}
		else{
			if(tail == size -1){// si no esta lleno y tail == size -1
				array[0] = i;
				tail = 0;
			}
			else{
				array[tail + 1] = i;
				tail++;
			}		
		  //estaba aca el t++
		}
count++;			
	}//si esta lleno no hago nada	 
	
	
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
item elremovido = array[head];//ver

array[head] = '-';//mmm

if(isEmpty() == 0){	
	if(head == size -1 ){//si head esta en la "ultima" posicion del buffer
		/*if(tail == size -1){
			flush();
		}*/
					
					//head al final y tail adelante del array
		head = 0;

	}
	else{
		head++;
	}
	
count --;

if(isEmpty() == 1)
	flush();
	
}
	
return elremovido;//cambiaraca?

}  

void
CircBuf::flush() {
	head = 0 ;
	tail = 0 ;
	count = 0; 
}

int   
CircBuf::isEmpty() {
	if(count == 0){
		return 1;
	}
	else{
		return 0;
	}
}

int  
CircBuf::isFull() {
	if(size == count){
		return 1;
	}
	else{
		return 0;
	}
}

/*
void 
CircBuf::imprimirPosicion(int i){
printf("%c,\n",array[i]);		
}*/

item 
CircBuf::getHead(){
return array[head];		
}

item
CircBuf::getTail(){
return array[tail];		
}

int
CircBuf::getCount(){
return count;
}

/*
void
CircBuf::imprimirBuf(){
int i;
for(i=0;i<size;i++)
	printf("%c",array[i]);

printf("\n");
}
*/
