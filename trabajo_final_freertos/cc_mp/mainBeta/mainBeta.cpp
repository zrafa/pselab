#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <avr/io.h>
#include "motor.h"
#include "led.h"
#include "GPIO.h"
#include <avr/interrupt.h>

//#define prioridadUS (tskIDLE_PRIORITY) + 4
#define prioridadMTR (tskIDLE_PRIORITY) + 3
//#define prioridadCR (tskIDLE_PRIORITY) + 2
#define prioridadSM (tskIDLE_PRIORITY) + 1

static void taskMTR(void *pvParameters);
static void taskSM(void *pvParameters);
//static void taskUS(void *pvParameters);
//static void taskCR(void *pvParameters);

//Led led((uint8_t volatile *)0x21, (uint8_t volatile *)0x22, 0x80);
Led led((volatile uint8_t *) 0x24,(volatile uint8_t *) 0x25, 0x80);		//Led amarillo en RB7			//Esto seria lo mismo que la linea de arriba (en teoria. Hay que verificarlo)
GPIO bicolor((volatile uint8_t *) 0x21,(volatile uint8_t *) 0x22, 7);	//Led bicolor en RA7
//Led led2((uint8_t volatile *)0x24, (uint8_t volatile *)0x25, 0x2);

volatile uint8_t *eicra;
volatile uint8_t *eimsk;

int izquierda = 1, derecha = 2, proximidad = 3, ctr_rmt = 4; //sacar

xQueueHandle handleCola;	// !!!!!!!!!!!!!!!!!!!!!!!

//***********************Definicion de Tareas***************************
void taskSM(void *pvParameters){//sube bandera izq, bandera der .. en las isr
	for(;;){} //no hago nada..por ahora
}

//void taskUS(void *pvParameters){//sube band ultra
	
//}
 
//void taskCR(void *pvParameters){ //sube band cr
	
//}
void taskMTR(void *pvParameters){ //ifs para ver banderas y mover motores
Motor motores;//parentesis??()
int mover = -1;
	
	for(;;){
		xQueueReceive(handleCola, (void *)&mover, (portTickType)0);//dentro del for?
		
		if(mover == 1){
			cli();
			bicolor.direccion(1);	//pin como salida
			bicolor.estado(0);		//enciende el rojo
			motores.M_izquierda(0xFFFF);		
			vTaskDelay(350);
			led.apaga();
			bicolor.direccion(0);	//se pone otra vez como entrada para apagar los dos
			motores.M_izquierda(0);
			mover = -1;
			vTaskDelay(2000);			
			sei();
			
		}
		if(mover == 2){
			cli();
			bicolor.direccion(1);	//pin como salida
			bicolor.estado(1);		//enciende el verde
			motores.M_derecha(0xFFFF);
			vTaskDelay(350);
			led.apaga();
			bicolor.direccion(0);	//se pone otra vez como entrada para apagar los dos
			motores.M_derecha(0);
			mover = -1;
			vTaskDelay(2000);			
			sei();
		}
	/*	if(){
		}
		if(){
		}
	*/
		}

}
//********************************************************************** 
int main(void){




xTaskHandle handleSM, handleUS, handleCR, handleMTR; //ni uso los handles. por ahora
				

handleCola =  xQueueCreate(1,sizeof(int)); //tamaño de la cola 1. Guarda enteros #1 para mover izq, #2 para mover der.

xTaskCreate(taskMTR, (const char*)"TareaMTR", configMINIMAL_STACK_SIZE, NULL, prioridadMTR, &handleMTR);
xTaskCreate(taskSM, (const char*)"TareaSM", configMINIMAL_STACK_SIZE, NULL, prioridadSM, &handleSM);
//xTaskCreate(taskUS, (const char*)"TareaUS", configMINIMAL_STACK_SIZE, NULL, prioridadUS, &handleUS);
//xTaskCreate(taskCR, (const char*)"TareaCR", configMINIMAL_STACK_SIZE, NULL, prioridadCR, &handleCR);

eicra = (uint8_t *) (0x69);
eimsk = (uint8_t *) (0x3D);
*eicra = 0b00001010; //genera interrupcion(INT0/INT1) por falling edge, 00001111 para rising edge
*eimsk = 0b00000011; //activo request 0/1 de inter. ext.
sei();

bicolor.direccion(0);	//Pin como entrada
vTaskStartScheduler();

return 1;
}


ISR(INT0_vect){//isr para interrupcion por int0	
	signed portBASE_TYPE xTaskWokenByPost;
	xTaskWokenByPost = pdFALSE;
	int a = 1;	
	
	xTaskWokenByPost = xQueueSendFromISR(handleCola, &a, &xTaskWokenByPost);
	led.enciende();
	
	if(xTaskWokenByPost)
		taskYIELD();	//fuerza el cambio de contexto
	
}

ISR(INT1_vect){//isr para interrupcion por int1
	signed portBASE_TYPE xTaskWokenByPost;
	xTaskWokenByPost = pdFALSE;
	int b = 2;	
	
	xTaskWokenByPost = xQueueSendFromISR(handleCola, &b, &xTaskWokenByPost);
	led.enciende();
	
	if(xTaskWokenByPost)
		taskYIELD();	//fuerza el cambio de contexto
	
}

