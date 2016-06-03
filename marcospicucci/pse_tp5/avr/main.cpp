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
#include <led.h>
#include <serial.h>
#include <stdio.h>

Led led((uint8_t volatile *)0x24, (uint8_t volatile *)0x25, 0x20);
Led led2((uint8_t volatile *)0x24, (uint8_t volatile *)0x25, 0x2);
int cont = 0;
SerialPort serial(0, 19200L, 64, 64);
char st[100];

/* Definicion de las Tareas */

void parpadea(void){
	int i;
	for(i=0;i<3;i++){
		led.enciende();
		led.delay_ms(1000);
		led.apaga();
	}
};

void contador(){
	cont++;
};

void obtenerCaracter(){//PB1(OC1A)_13_D9

int c;
	//c = serial.getchar();
	if((c == 'a')
		led2.enciende();
	
	if(c == 'k')
		led2.apaga();
	
};

void hiSegTrans(){
	sprintf(st,"Hola mundo!. Segundos transcurridos :  %d\n",cont);//convierto la cant d segundos a *char
	//serial.puts("Hola mundo!. Segundos transcurridos : ");
	serial.puts(st);
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
	{NULL , parpadea},
	{NULL, contador},
	{NULL, obtenerCaracter},
	{NULL, hiSegTrans}
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

    timer1.start(333, Periodic);
    timer2.start(1000, Periodic);
    timer3.start(1000, Periodic);
    timer4.start(4000, Periodic);

    /* Asociamos cada reloj a una tarea*/
    Tasks[0].timer = &timer1;
    Tasks[1].timer = &timer2;
	Tasks[2].timer = &timer3;
	Tasks[3].timer = &timer4;
	
    int i;

    while (1)
    {
	//led2.enciende();
	
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

