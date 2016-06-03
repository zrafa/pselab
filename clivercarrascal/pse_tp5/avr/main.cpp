/***************************************************************************
 *
 * Filename:	tasks.c
 *
 * Description: Simple environment of different and periodic tasks 
 *
 * 
 * Copyright (c) 1998 by Michael Barr.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 *
 * Tasks array and port to i386 and avr by Rodolfo del Castillo 
 * and Rafael Zurita
 *
 **********************************************************************/

#include <timer.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include "serial.h"
#include <string.h>


int n=1; 	//variable del contador

SerialPort serial(UART0, 19200L, 64, 64);
/* Definicion de las Tareas */

void led(void)
{
	 Timer  timerled;
	 
     PORTB |= 0x20;		//Se prende el PB5
	 timerled.start(100, OneShot);	//Se genera un timer para esperar 100 ms
	 timerled.waitfor();
	 PORTB &= 0xDF;		//Se apaga el PB5
	 
};

void rx232(void)
{
	int c;

	c = serial.getchar();
	if(c=='a')
		PORTB |= 0x02;	//Se prende el PB1
	if(c=='k')
		PORTB &= 0xFD;	//Se apaga el PB1
};

void contador(void)
{
	n++;
};

void helloworld(void)
{
	char str[100]="Hello world!. Segundos transcurridos : ";
	char str2[10]={};
	sprintf(str2,"%u",n);
	strcat(str,str2);
	serial.puts(str);
	
};
/* FIN de la definicion Tareas */


/* Tipo de datos para una tarea:
 * Contiene un reloj por software y una funcion (tarea)
 */
typedef struct {
	Timer * timer;
	void (*Func) (void);
} TaskType;

#define N_TAREAS 4

/* Arreglo que mantiene un listado de tareas con sus respectivos
 * relojes de software
 */
static TaskType Tasks[N_TAREAS] {
	{NULL , led},
	{NULL , rx232},
	{NULL , contador},
	{NULL , helloworld} 
};


/**********************************************************************
 *
 * Function:    main()
 *
 * Description: Defines and array with two tasks and timers.
 * 
 * Notes:       This outer loop is hardware-independent.
 *
 * Returns:     This routine contains an infinite loop.
 *
 **********************************************************************/

int main(void)
{
	
    /* Necesitamos un reloj de software para cada tarea */
    Timer  timer1;
    Timer  timer2;
    Timer  timer3;
    Timer  timer4;

    /* tareas cada 1000 microsegundos */
    timer1.start(333, Periodic);		//Blink
    timer2.start(500, Periodic);		//getchar
    timer3.start(1000, Periodic);	//Contador
    timer4.start(4000, Periodic);	//Hello!

    /* Asociamos cada reloj a una tarea*/
    Tasks[0].timer = &timer1;
    Tasks[1].timer = &timer2;
    Tasks[2].timer = &timer3;
    Tasks[3].timer = &timer4;

    int i;
    
	//PB5 y PB1 como salidas
	DDRB= 0x22;		//DDRB=TRISB. Esta definido en avr/io.h. 
	
    while (1)
    {

	/* Verificamos cada reloj software: si el contador ha expirado
         * es el momento de ejecutar la tarea asociada.
         */
        for (i=0; i<N_TAREAS; i++) {
            if ((Tasks[i].timer)->isDone() == 1)
                (*(Tasks[i].Func))();
        }
	
    }

    return 0;
}   /* main() */

