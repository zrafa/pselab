#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <avr/io.h>
#include "motor.h"
#include "led.h"
#include "driverSM.h"
#include "driverUS.h"
#include "GPIO.h"
#include <avr/interrupt.h>
													//hay maximo 4 prioridades en frtos.h
#define prioridadChief (tskIDLE_PRIORITY) + 3
#define prioridadUS (tskIDLE_PRIORITY) + 2
#define prioridadMTR (tskIDLE_PRIORITY) + 2
//#define prioridadRF (tskIDLE_PRIORITY) + 2
#define prioridadSM (tskIDLE_PRIORITY) + 2
#define prioridadLED (tskIDLE_PRIORITY) + 1

static void taskChief(void *pvParameters);
static void taskLED(void *pvParameters);
static void taskMTR(void *pvParameters);
static void taskSM(void *pvParameters);
static void taskUS(void *pvParameters);
//static void taskRF(void *pvParameters);


//esto hacerrlo en el cpp correspondiente. ver si hacer una sola clase gpio o led, no ambas(deberia ser gpio)
//Led led((volatile uint8_t *) 0x24,(volatile uint8_t *) 0x25, 0x80);		//Led amarillo en RB7			//Esto seria lo mismo que la linea de arriba (en teoria. Hay que verificarlo)
//GPIO bicolor((volatile uint8_t *) 0x21,(volatile uint8_t *) 0x22, 7);	//Led bicolor en RA7

QueueHandle_t colaRecep, colaMtr;	// !!!!!!!!!!!!!!!!!!!!!!!

//***********************Definicion de Tareas***************************
void taskSM(void *pvParameters){
	DriverSM sensorMovi;
	sensorMovi.init();
	sensorMovi.setCola(&colaRecep);//ver esto
	
	for(;;){} //no hago nada, se queda esperando hasta q se produce interrupcion.
}

void taskUS(void *pvParameters){
	DriverUS ultraSoni;
	ultraSoni.init();
	
	
}
 
//void taskRF(void *pvParameters){

//} 
 
 
void taskChief(void *pvParameters){ 
		 
		 //aca leo de la cola de recepcion y escribo en la cola MTR y LED
		
}

void taskLED(void *pvParameters){
	
}

void taskMTR(void *pvParameters){ 
Motor motores;
int mover = -1;
	
	for(;;){
		xQueueReceive(colaMtr, (void *)&mover, (portTickType)0);//dentro del for? lee la cola para ver q hacer
		
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
	}

}
//********************************************************************** 
int main(void){

TaskHandle_t handleSM, handleUS, handleCR, handleMTR; //ni uso los handles. por ahora
				

colaMtr =  xQueueCreate(1,sizeof(int)); //tamaño de la cola 1. Guarda enteros #1 para mover izq, #2 para mover der.
colaRecep = xQueueCreate(1,sizeof(int));//cola que va leyendo la tarea chief (recibe datos del US, SM y RF)


xTaskCreate(taskMTR, (const char*)"TareaMTR", configMINIMAL_STACK_SIZE, NULL, prioridadMTR, &handleMTR);
xTaskCreate(taskSM, (const char*)"TareaSM", configMINIMAL_STACK_SIZE, NULL, prioridadSM, &handleSM);
xTaskCreate(taskUS, (const char*)"TareaUS", configMINIMAL_STACK_SIZE, NULL, prioridadUS, &handleUS);
//xTaskCreate(taskCR, (const char*)"TareaCR", configMINIMAL_STACK_SIZE, NULL, prioridadCR, &handleCR);

bicolor.direccion(0);	//Pin como entrada
vTaskStartScheduler();

return 1;
}


