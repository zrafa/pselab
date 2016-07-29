#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <avr/io.h>
#include "motor.h"
#include "led.h"
#include "driverSM.h"
#include "driverUS.h"
#include "serial.h"
#include "GPIO.h"
#include <avr/interrupt.h>//sacar?
													
#define prioridadChief (tskIDLE_PRIORITY) + 3 //la de mayor prioridad
#define prioridadUS (tskIDLE_PRIORITY) + 3
#define prioridadMTR (tskIDLE_PRIORITY) + 2
#define prioridadRF (tskIDLE_PRIORITY) + 2
#define prioridadSM (tskIDLE_PRIORITY) + 2
#define prioridadLED (tskIDLE_PRIORITY) + 2

static void taskChief(void *pvParameters);
static void taskLED(void *pvParameters);
static void taskMTR(void *pvParameters);
static void taskSM(void *pvParameters);
static void taskUS(void *pvParameters);
static void taskRF(void *pvParameters);

SerialPort serial(0, 9600L, 64, 64);
GPIO bicolor((volatile uint8_t *) 0x21,(volatile uint8_t *) 0x20, 7);	//Led bicolor en RA7

QueueHandle_t colaRecep, colaMtr, colaLED;
TaskHandle_t handleMTR, handleCHF, handleLED, handleRF, handleSM, handleUS;

DriverSM sensorMovi;
//**********************************************************************  
//***********************DEFINICION DE TAREAS***************************
//______________________________________________________________________

void taskSM(void *pvParameters){//hacerle un delay? bajarle la prioridad?
portTickType xLastWakeTime;
sensorMovi.init();
sensorMovi.scanOff();

xLastWakeTime = xTaskGetTickCount();
	for(;;){
		vTaskDelayUntil(&xLastWakeTime, 3000);
	} //no hago nada, se queda esperando hasta q se produce interrupcion.
}
//______________________________________________________________________

void taskUS(void *pvParameters){//ver si hacerla periodica
DriverUS ultraSoni;
volatile float distancia;
int dist;
int para = 5, sigue = 6;
ultraSoni.init();
//bicolor.direccion(0);
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
	
	for(;;){
		vTaskDelayUntil(&xLastWakeTime, 100);
		
		distancia = ultraSoni.calculaDistancia();
		bicolor.direccion(1);
	bicolor.estado(1);
		//serial.puts("_xe_");
		if(distancia > -1 && distancia < 25){
			bicolor.estado(0);		//enciende el rojo
			bicolor.direccion(1);	//pin como salida	
			xQueueSend(colaRecep,(void *)&para,(portTickType)2000);//poner en colaRecep para que lo lea chief y no le permita avanzar (hacia adelante) a motores
			//dist = (int)distancia;
			//dist
			
		}
		else{
			xQueueSend(colaRecep,(void *)&sigue,(portTickType)2000);//esta permitido avanzar hacia adelante, ie hay lugar para moverse
			bicolor.direccion(0);
		}
		
	//vTaskDelay(50);
	}
}
//______________________________________________________________________

void taskRF(void *pvParameters){
int c=0 , w = 1, s = 2, a = 3, d = 4, o = 7, p = 8;

	
	for(;;){	
	
	bicolor.direccion(1);
	bicolor.estado(1);
	c = serial.getcharr(); //leo y prendo led- es para probar. desp deberia poner en la cola de recep, para q chief le avise a motores
	
		if(c != -1){
			
				
			switch(c){
				
				case 'p':
					vTaskSuspend(handleLED);
					break;
				case 'l':
					vTaskResume(handleLED);
					break;
				case 'w':
					xQueueSend(colaMtr, (void *)&w, (portTickType)2000);
					break;
				case 's':
					xQueueSend(colaMtr, (void *)&s, (portTickType)2000);
					break;	
				case 'a':
					xQueueSend(colaMtr, (void *)&a, (portTickType)2000);
					break;
				case 'd':
					xQueueSend(colaMtr, (void *)&d, (portTickType)2000);
					break;	
				//case:'o'			//activo modo autónomo
					//xQueueSend(colaMtr, (void *)&o, (portTickType)2000)
					//break;
				//case:'p'			//desactivo modo autónomo
					//xQueueSend(colaMtr, (void *)&p, (portTickType)2000)
					//break;
				case 'x':
					sensorMovi.scanOff();
					break;
				case 'b':
					sensorMovi.scanOn();
					break;
			}
										
		}
		
		//vTaskDelay(300);
	}
}
//______________________________________________________________________
 
void taskChief(void *pvParameters){ 	 
int comando = -1;
	for(;;){
		xQueueReceive(colaRecep, (void *)&comando, (portTickType)2000);//se bloquea, como maximo, 2k ticks hast q llega un dato (sin un dato no hago nada, asi q se bloquea)
		
		switch(comando){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				xQueueSend(colaMtr, (void *)&comando, (portTickType)2000);//casos en q se recibe info de SM o RF
				break;							
			case 7:
			case 8:
				xQueueSend(colaLED, (void *)&comando, (portTickType)1000);//necesario?? no creo, estaba por si hacia falta una cola para avisarle de q forma parpadear al led
				break;		
		}
	comando = -1;				
	}
		
}
//______________________________________________________________________

void taskLED(void *pvParameters){//hacer q el led amarillo se apague y prenda siempre, mientras q los bicolores solo se prendan en otras circunstancias (cuando dobla o retrocede por ej)
Led led((volatile uint8_t *) 0x24,(volatile uint8_t *) 0x25, 0x80);	
	
	for(;;){
		//xQueueReceive(colaLED, (void *)&comando, (portTickType)20);
		//if(){}//preguntar si dobló para prender verde/amarillo?
		led.toggle();
		vTaskDelay(200);
	}
}
//______________________________________________________________________

void taskMTR(void *pvParameters){ 
Motor motores;
int mover = -1, parar = 0;

	for(;;){
		xQueueReceive(colaMtr, (void *)&mover, (portTickType)2000);
	//1) avanza, 2) retrocede, 3) dobla izquierda, 4) dobla derecha, 5) no avanzar(orden del US), 6) puede avanzar(orden del US)
		switch(mover){
			case 1:
				cli();
				serial.desactivarSerial();
				if(parar == 0){ //cuando el US esta muy cerca de algo, no se puede avanzar(solo hacia adelante) mas, por ejemplo si por RF se le solicita hacerlo
				motores.M_adelante(0xAFFF);
				vTaskDelay(350);
				motores.M_adelante(0);
				mover = -1;// poner una sola vez afuera del switch.
				sei();
				}		
				break;
			case 2:
				cli();
				serial.desactivarSerial();	
				motores.M_atras(0xFFFF);
				vTaskDelay(350);
				motores.M_atras(0);
				mover = -1;
				sei();
				break;
			case 3:
				cli();
				serial.desactivarSerial();		
				motores.M_izquierda(0x8FFF);		
				vTaskDelay(50);
				motores.M_izquierda(0);
				mover = -1;				 
				sei();
				break;
			case 4:
				cli();
				serial.desactivarSerial();
				motores.M_derecha(0x8FFF);
				vTaskDelay(50);
				motores.M_derecha(0);
				mover = -1;		
				sei();	
				break;
			case 5://el us aviso q se esta cerca de la pared por ej
				parar = 1;
				break;	
			case 6://el us dice que se puede seguir moviendo libremente
				parar = 0;
				break;
		
		}
		serial.activarSerial();	
	}
}
//______________________________________________________________________

//*******************************MAIN***********************************
//********************************************************************** 
int main(void){
				
colaLED = xQueueCreate(1,sizeof(int)); // dependiendo del nro q reciba, va a parpadear de una forma u otra con uno u otro led
colaMtr =  xQueueCreate(1,sizeof(int)); // Guarda enteros que se traducen en la direccio o accion q van a realizar los motores
colaRecep = xQueueCreate(1,sizeof(int));//cola que va leyendo la tarea chief (recibe datos del US, SM y RF)

xTaskCreate(taskChief, (const char*)"TareaCHF", configMINIMAL_STACK_SIZE, NULL, prioridadChief, &handleCHF);
xTaskCreate(taskMTR, (const char*)"TareaMTR", configMINIMAL_STACK_SIZE, NULL, prioridadMTR, &handleMTR);
xTaskCreate(taskSM, (const char*)"TareaSM", configMINIMAL_STACK_SIZE, NULL, prioridadSM, &handleSM);
xTaskCreate(taskUS, (const char*)"TareaUS", configMINIMAL_STACK_SIZE, NULL, prioridadUS, &handleUS);
xTaskCreate(taskRF, (const char*)"TareaRF", configMINIMAL_STACK_SIZE, NULL, prioridadRF, &handleRF);
xTaskCreate(taskLED, (const char*)"TareaLED", configMINIMAL_STACK_SIZE, NULL, prioridadLED, &handleLED);

vTaskStartScheduler();

return 1;
}


