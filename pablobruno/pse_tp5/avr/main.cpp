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
#include <avr/io.h>
#include "serial.h"
#include <stdio.h>

//Uso de funciones del led

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define GPIO 0x25
#define GPIO_HL 0x24
#define CYCLES_PER_MS (9600)

void delay_ms(int milliseconds)
 {

 long volatile cycles = (milliseconds * CYCLES_PER_MS);
   while (cycles != 0)
    cycles--;
 }


void toggleInit (){
 unsigned char puertoB;
 volatile unsigned char * valueGPIO;
   valueGPIO=(volatile unsigned char *)GPIO;
   puertoB= (*(valueGPIO) | 0x20);

   *valueGPIO=puertoB;


}


void toggleLed(int queHacer){

	 unsigned char puertoHL;
	 volatile unsigned char * valueGPIO_HL;
	   valueGPIO_HL=(volatile unsigned char *)(GPIO_HL);

	if (queHacer==1)
	   {
	    puertoHL= (*(valueGPIO_HL) | (0x20));
	   }
	else
	   {
	    puertoHL= (*(valueGPIO_HL) & (0xDF));
	   }

	   *valueGPIO_HL=puertoHL;

}

int cantidadSegundos=0; //variable global usada para guardar la cantidad de segundos
SerialPort serial(0, 19200L, 64, 64);
char envioHolaMundo[100];

/* Definicion de las Tareas */

void contador(void){
 cantidadSegundos++;
};

void leerDato(void){
  int dato= serial.getChar();
  if(((char)dato)=='a')	toggleLed (1);

  if(((char)dato)=='k') toggleLed(0);

};

void enviarMensaje(void){
  sprintf(envioHolaMundo,"Hola mundo!. Segundos transcurridos :%d\n",cantidadSegundos); 
serial.puts(envioHolaMundo);
};

//Tarea que parpadea el LED ROJO
void led(void){
  //	toggleLed(0);
//	toggleLed (1);

	//delay_ms(200);
	//toggleLed(0);


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
	{NULL, led},
	{NULL, leerDato},
	{NULL, contador},
	{NULL, enviarMensaje}
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
	 toggleInit();

	/* Necesitamos un reloj de software para cada tarea */
    Timer  timer1;
    Timer  timer2;
    Timer  timer3;
    Timer  timer4;


    timer1.start(333, Periodic); //parpadea el led 3 veces por segundo
    timer2.start(500, Periodic); //tarea que leera  un dato dos veces por segundo
		timer3.start(1000, Periodic); //contador de segundos
	  timer4.start(4000, Periodic); //envia un mensaje HOLA MUNDO con cantidad de segundos

    /* Asociamos cada reloj a una tarea*/
    Tasks[0].timer = &timer1;
    Tasks[1].timer = &timer2;
    Tasks[2].timer = &timer3;
    Tasks[3].timer = &timer4;
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

    }

    return 0;
}   /* main() */
