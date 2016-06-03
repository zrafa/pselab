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
#include <led.cpp>
#include "serial.h"

#define PORT       0x24       //Direccion de memoria del registro de direcciones.
#define LED        0x25       //Direccion de memoria del registro de estado.
#define ENCENDER   0x20       //Mascara para encender/apagar el led rojo del arduino pro-mini.
#define PCB        0x02       //Mascara para activar el bit 1 del registro de estado del PORTB. De esta manera usamos el pin 9 del arduino pro-mini en una protoboard.


/* Definicion de las Tareas */

//Definicion global de un objeto de tipo Led. Se usa en la tarea 1.
Led led_rojo((volatile unsigned char *) PORT, (volatile unsigned char *) LED, ENCENDER);

//Definicion global de un objeto Led. Se usa en la tarea 3 para apagar/encender un led conectado en el pin 9 del arduino promini, a traves de una protoboard.
//Led led_pcb((volatile unsigned char *) PORT, (volatile unsigned char *) LED, PCB);

//Definicion global de una variable para mantener la cantidad de segundos transcurridos. Se usa en la tarea 2.
int segundos=0;

//Definicion global de un objeto SerialPort. Se usa en la tarea 3.
SerialPort serial(0, 9600, 64, 64);

/* Ejercicio 2 */
void contador(void){
//	printf("contador \n");

segundos++;

};

/* Ejercicio 1 */
void led(void){

//	printf("\t led \n");
led_rojo.encender();
led_rojo.delay(1000);
led_rojo.apagar();

};

/* Ejercicio 3 */
//void leer_dato (void){
//Cuando pulsamos una tecla la vemos en la consola mientras se ejecuta el programa minicom, porque este al ser un emulador de puerto serial deposita el dato ingresado
//en el registro de datos del periferico USART.
//char c;
//while(1){

//c=serial.getchar();

//while(c <= 0);

//switch(c){

//case 'a' : {//Encendemos el led conectado al pin 9 del pcb.
	//		break;
	//	   }

//case 'k' : {//Apagamos el led conectado al pin 9 del pcb.
	//		break;
	//	   }

//}

//};

/* Ejercicio 4 */
void segundos_transcurridos (void){

char mensaje[100];
sprintf(mensaje, "Hola Mundo!. Segundos transcurridos : %i \n", segundos);
serial.puts(mensaje);

};

/* FIN de la definicion Tareas */


/* Tipo de datos para una tarea:
 * Contiene un reloj por software y una funcion (tarea)
 */
typedef struct {
	Timer * timer;
	void (*Func) (void);
} TaskType;

#define N_TAREAS 3

/* Arreglo que mantiene un listado de tareas con sus respectivos
 * relojes de software
 */
static TaskType Tasks[N_TAREAS] {
	{NULL , contador},
	{NULL , led},
	{NULL,  segundos_transcurridos},
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
    Timer  timer1;	//Se corresponde con la tarea numero 2: mantener la cantidad de segundos transcurridos.
    Timer  timer2;  //Se corresponde con la tarea numero 1: parpadear un led rojo tres veces por segundo.
	//Timer  timer3;  //Se corresponde con la tarea numero 3: leer un dato desde el driver serial dos veces por segundo.
	Timer  timer4;  //Se corresponde con la tarea numero 4: mostrar un mensaje con los segundos transcurridos.

    /* tareas cada x microsegundos */
    timer1.start(1000, Periodic);
    timer2.start(333,  Periodic);
	//timer3.start(1000, Periodic);
	timer4.start(4000, Periodic);

    /* Asociamos cada reloj a una tarea*/
    Tasks[0].timer = &timer1;
    Tasks[1].timer = &timer2;
	Tasks[2].timer = &timer4;
	//Tasks[3].timer = &timer4;

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

