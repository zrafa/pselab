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
#define prioridadUS (tskIDLE_PRIORITY) + 1
#define prioridadMTR (tskIDLE_PRIORITY) + 2
#define prioridadRF (tskIDLE_PRIORITY) + 1
#define prioridadSM (tskIDLE_PRIORITY) + 1
#define prioridadLED (tskIDLE_PRIORITY) + 1

static void taskChief(void *pvParameters);
static void taskLED(void *pvParameters);
static void taskMTR(void *pvParameters);
static void taskSM(void *pvParameters);
static void taskUS(void *pvParameters);
static void taskRF(void *pvParameters);


GPIO bicolor((volatile uint8_t *) 0x21,(volatile uint8_t *) 0x20, 7);	//Led bicolor en RA7

QueueHandle_t colaRecep, colaMtr, colaLED;	// !!!!!!!!!!!!!!!!!!!!!!!
TaskHandle_t handleMTR, handleCHF, handleLED, handleRF, handleSM, handleUS; 
//***********************Definicion de Tareas***************************
void taskSM(void *pvParameters){
	DriverSM sensorMovi;
	sensorMovi.init();	

	for(;;){} //no hago nada, se queda esperando hasta q se produce interrupcion.
}

void taskUS(void *pvParameters){//hacerla periodica??
	DriverUS ultraSoni;
	ultraSoni.init();
	bicolor.direccion(0);	//Apaga el bicolor
	volatile float distancia;
	
	int para = 5, sigue = 6;
	for(;;){
		
		distancia = ultraSoni.calculaDistancia();
	
		if(distancia>2 && distancia<15)
		{
			//vTaskSuspend(handleLED);
			bicolor.estado(0);		//enciende el rojo
			bicolor.direccion(1);	//pin como salida
			//poner en colaRecep para q pare
			xQueueSend(colaRecep,(void *)&para,(portTickType)1000);
		}
		else{
			xQueueSend(colaRecep,(void *)&sigue,(portTickType)1000);
			//avisarle pa q siga
			bicolor.direccion(0);
			}
		
		vTaskDelay(200);
	}
}
 
void taskRF(void *pvParameters){
SerialPort serial(0, 19200L, 64, 64);
int c;

	for(;;){
	c = serial.getcharr(); //leo y prendo led- es para probar. desp deberia poner en la cola de recep, para q chief le avise a motores
	
		if(c != -1){
			if(c == 'p')
				vTaskSuspend(handleLED);
			if(c == 'a')
				vTaskResume(handleLED);
		}
		vTaskDelay(300);
	}
}

 
 
 
void taskChief(void *pvParameters){ 	 
	int comando = -1;
	for(;;){
		xQueueReceive(colaRecep, (void *)&comando, (portTickType)50);//se bloquea, como maximo, 50 ticks hast q llega un dato (sin un dato no hago nada, asi q se bloquea)
		
		switch(comando){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
					xQueueSend(colaMtr, (void *)&comando, (portTickType)10 );//casos en q se recibe info de SM o RF
					break;					
			
			case 7:
			case 8:
					xQueueSend(colaLED, (void *)&comando, (portTickType)10 );//necesario?? no creo, estaba por si hacia falta una cola para avisarle de q forma parpadear al led
					break;
			
			//default necesario?
		}					
	}
		
}

void taskLED(void *pvParameters){//hacer q el led amarillo se apague y prenda siempre, mientras q los bicolores solo se prendan en otras circunstancias (cuando dobla o retrocede por ej)
Led led((volatile uint8_t *) 0x24,(volatile uint8_t *) 0x25, 0x80);	
	
	for(;;){
		//xQueueReceive(colaLED, (void *)&comando, (portTickType)20);
		//if(){}//preguntar si dobló para prender verde/amarillo?
		led.toggle();
		vTaskDelay(100);
	}
}

void taskMTR(void *pvParameters){ 
Motor motores;
int mover = -1, parar = 0;

	for(;;){
		xQueueReceive(colaMtr, (void *)&mover, (portTickType)10);
	//1 avanza, 2 retrocede, 3 dobla izquierda, 4 dobla derecha, 5 frena(orden del US)
		switch(mover){
			case 1:
				if(parar =! 1){ //cuando el US esta muy cerca de algo, no se puede avanzar(solo hacia adelante) mas, por ejemplo si por RF se le solicita hacerlo
				motores.M_adelante(0xFFFF);
				vTaskDelay(350);
				motores.M_adelante(0);
				mover = -1;
				}		
				break;
			case 2:			
				motores.M_atras(0xFFFF);
				vTaskDelay(350);
				motores.M_atras(0);
				mover = -1;
				break;
			case 3:
				cli();		
				motores.M_izquierda(0xFFFF);		
				vTaskDelay(350);
				motores.M_izquierda(0);
				mover = -1;		
				sei();		 
				break;
			case 4:
				cli();
				motores.M_derecha(0xFFFF);
				vTaskDelay(350);
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
	}
}
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


