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

//SIEMPRE debemos incluir los archivos .h, ya que estos contienen definiciones que el compilador utiliza para hacer chequeo de tipos. No es necesario incluir los 
//archivos .cpp o .c porque generamos una unidad de traduccion muy grande.
//Para solucionar problemas relacionados a la inclusion de archivos hay que modificar el makefile, simplemente agregamos las palabras que hacen referencia a programas
//objetos, en este caso serial.o scc.o led.o circbuf.o
#include <timer.h>
#include <stdlib.h>
#include <led.h>
#include "serial.h"

#define PORTB       0x25       //Direccion de memoria del registro de estado. Este registro se usa para encender/apagar un led.
#define DDRB        0x24       //Direccion de memoria del registro de direcciones. Se usa habilitar un pin para salida.
#define ENCENDER    0x20       //Mascara para encender/apagar el led rojo del arduino pro-mini.

//Creamos dos mascaras similares pero con distintos usos.
#define PCB         0x20       //Mascara para activar el bit 5 del registro de estado del PORTD. De esta manera usamos el pin 9 del arduino pro-mini en una protoboard.
#define PORTD       0x2B       //Direccion donde se encuentra ubicado el registro de estado del pin 9, se necesita para encender o apagar un led conectado al pin 9.
							   //Para que esto ultimo ocurra debemos activar el bit 5, porque en el esquematico se observa la siguiente expresion en el pin 9 PD5 que 									 significa 'Port D bit 5'.
#define DDRD	    0x2A       //Direccion donde se encuentra ubicado el registro de direcciones del pin 9. Se usa para activarlo como salida.




/* Definicion de las Tareas */

//Definicion global de un objeto de tipo Led. Se usa en la tarea 1.
Led led_rojo((volatile unsigned char *) DDRB, (volatile unsigned char *) PORTB, ENCENDER);

//Definicion global de un objeto Led. Se usa en la tarea 3 para apagar/encender un led conectado en el pin 9 del arduino promini, a traves de una protoboard.
Led led_pcb((volatile unsigned char *) DDRD, (volatile unsigned char *) PORTD, PCB);

//Definicion global de una variable para mantener la cantidad de segundos transcurridos. Se usa en la tarea 2.
int segundos=0;

//Definicion global de un objeto SerialPort. Se usa en la tarea 3.
SerialPort serial(0, 9600, 120, 120);

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
void leer_caracter (void){
//Cuando pulsamos una tecla la vemos en la consola mientras se ejecuta el programa minicom, porque este al ser un emulador de puerto serial deposita el dato ingresado
//en el registro de datos del periferico USART.
char c;

//Para que funcionen los timers no hay que utilizar un while infinito.
c = (char) serial.getchar();

switch(c){

case 'a' : {//Encendemos el led conectado al pin 9 del pcb.
			led_pcb.encender();
			break;
		   }

case 'k' : {//Apagamos el led conectado al pin 9 del pcb.
			led_pcb.apagar();
			break;
		   }
}

};

/* Ejercicio 4 */
void segundos_transcurridos (void){

char mensaje[100];
//En la variable mensaje guardamos la concatenacion de una cadena con un numero entero. Como el mensaje tiene una longitud total de 100 bytes en necesario 
//aumentar el tamanio del buffer circular.
sprintf(mensaje, "Hola Mundo!. Segundos transcurridos : %d ", segundos);
//Enviamos el contenido de mensaje a periferico USART.
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

//Macro donde se debe especificar la cantidad de tareas.
#define N_TAREAS 4

/* Arreglo que mantiene un listado de tareas con sus respectivos
 * relojes de software
 */
static TaskType Tasks[N_TAREAS] {
	{NULL , contador},
	{NULL , led},
	{NULL, leer_caracter},
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
	Timer  timer3;  //Se corresponde con la tarea numero 3: leer un dato desde el driver serial dos veces por segundo.
	Timer  timer4;  //Se corresponde con la tarea numero 4: mostrar un mensaje con los segundos transcurridos.

    /* tareas cada x microsegundos */
    timer1.start(1000, Periodic);
    timer2.start(333,  Periodic);
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

