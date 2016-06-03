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

#include "timer.h"
#include "stdlib.h"
#include "stdio.h"



/* Definicion de las Tareas */

void contador(void){
	printf("contador \n");
};

void led(void){
	printf("\t led \n");

};

/* FIN de la definicion Tareas */

/* Tipo de datos para una tarea: 
 * Contiene un reloj por software y una funcion (tarea)
 */
typedef struct {
	Timer * timer;
	void (*Func) (void);
} TaskType;

#define N_TAREAS 2

/* Arreglo que mantiene un listado de tareas con sus respectivos 
 * relojes software
 */
static TaskType Tasks[N_TAREAS] {
	{NULL , contador},
	{NULL , led},
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

    timer1.start(10000000, Periodic);
    timer2.start(32000000, Periodic);

    /* Asociamos cada reloj a una tarea*/
    Tasks[0].timer = &timer1;
    Tasks[1].timer = &timer2;

    int i;

    while (1)
    {

	/* Verificamos cada reloj software: si el contador ha expirado
         * es el momento de ejecutar la tarea asociada.
         */
        for (i=0; i<N_TAREAS; i++) {
            if ((Tasks[i].timer)->isDone() == 1)
                (*(Tasks[i].Func))();
        }
	
	/* No utilizamos interrupciones en i386 para realizar un tick */
        Timer::Interrupt();
    }

    return 0;
}   /* main() */

