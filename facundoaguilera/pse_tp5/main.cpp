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

// dpkg -L nombre_del_paquete  (esto me dice todos los archivos del paquete que se instaló) después grep stdio.h por ejemplo

#include <led.h>
#include <timer.h>
#include <stdlib.h>
#include <avr/interrupt.h> //incluyo librería de interrupciones 
#include "serial.h"
#include "scc.h"
extern SCC scc;
/* Definicion de las Tareas */
unsigned int seg=0;

void contador(void){
//	printf("contador \n");

seg++;
};

Led led_Rojo((unsigned char *)DDR_B,(unsigned char *)PUERTO_B,( unsigned char)LED_ROJO);
Led led_pin9((unsigned char *)DDR_D,(unsigned char *)PUERTO_D,( unsigned char)LED_pin9);
char mensaje [100];
void red_Led(void){
led_Rojo.led_ON();
//deberia poner un pequeño delay
led_Rojo.delay_ms(1000);
led_Rojo.led_OFF();
};

SerialPort serial(0, 9600, 100, 100);

void alive (void){
//char cadena  [64] = "Hola mundo!. Segundos transcurridos :"+seg;
//serial.puts("Hola mundo!. Segundos transcurridos :");
//serial.putchar((int) (seg + 48));//seg
sprintf(mensaje,"Hola mundo!. Segundos transcurridos : %i\n",seg);
serial.puts(mensaje);
}

void tarea3 (void){
char caracter;
caracter=serial.getchar();
if(caracter=='a'){
//prender led en el pin 9
led_pin9.led_ON();
				  }
if(caracter=='k'){
//apagar led en el pin 9
led_pin9.led_OFF();
				}
}
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
static TaskType Tasks[N_TAREAS] { //está en el pdf de c declaración (tipo y nombre)  definición (como se ejecuta y creación de espacio en memoria) e inicialización
	{NULL , red_Led},
	{NULL , contador},
	{NULL , alive},
	{NULL , tarea3},

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

    /* tareas cada 1000 milisegundos */
    timer1.start(333, Periodic);
    timer2.start(1000, Periodic);
	timer3.start(4000, Periodic);
	timer4.start(500, Periodic);

    /* Asociamos cada reloj a una tarea*/
    Tasks[0].timer = &timer1;
    Tasks[1].timer = &timer2;
	Tasks[2].timer = &timer3;
	Tasks[3].timer = &timer4;

    int i;
	
	sei();/* Habilito interrupciones globales */
	
	led_Rojo.ledInit();
	led_pin9.ledInit();
    
    serial.puts("Hello, World!");

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


ISR(USART_UDRE_vect ) /*data register empty*/
{
scc.DataReg_intDisable(); /*deshabilito interrupciones por data register empty*/
scc.Transmit_Enable();/*habilito transmisión*/
while(!scc.DataReg_isEmpty(0));
scc.scc_put();         /*mando el dato*/
 
}

ISR(USART_RX_vect  )
{
	//scc.clear_RxFlag(); //esto me estaba jodiendo la recepción, se ve que era como si deshabilitara la interrupción
	//scc.Rx_Int_Disable();
	scc.scc_get();
}

