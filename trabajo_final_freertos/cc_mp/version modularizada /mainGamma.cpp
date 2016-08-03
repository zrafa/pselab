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
#include <avr/interrupt.h>
#include <util/delay.h>
													
#define prioridadChief (tskIDLE_PRIORITY) + 3
#define prioridadUS (tskIDLE_PRIORITY) + 2
#define prioridadMTR (tskIDLE_PRIORITY) + 2
#define prioridadRF (tskIDLE_PRIORITY) + 2
#define prioridadSM (tskIDLE_PRIORITY) + 2
#define prioridadLED (tskIDLE_PRIORITY) + 2

#define ADELANTE 1
#define ATRAS 2
#define IZQUIERDA 3
#define DERECHA 4
#define PARAR 5
#define SEGUIR 6
#define IZQSENSOR 33
#define DERSENSOR 44
#define ROJO 66
#define APAGAR 77

static void taskChief(void *pvParameters);
static void taskLED(void *pvParameters);
static void taskMTR(void *pvParameters);
static void taskSM(void *pvParameters);
static void taskUS(void *pvParameters);
static void taskRF(void *pvParameters);

SerialPort serial(0, 9600L, 64, 64);

GPIO bicolor((volatile uint8_t *) 0x21, (volatile uint8_t *) 0x20, 7);//Led bicolor en RA7
Led led((volatile uint8_t *) 0x24, (volatile uint8_t *) 0x25, 0x80);//led amarillo

QueueHandle_t colaRecep, colaMtr, colaLED;
TaskHandle_t handleMTR, handleCHF, handleLED, handleRF, handleSM, handleUS;

DriverSM sensorMovi;
DriverUS ultraSoni;
Motor motores;
//**********************************************************************  
//***********************DEFINICION DE TAREAS***************************
//______________________________________________________________________

void taskSM(void *pvParameters){
portTickType xLastWakeTime;

sensorMovi.init();
sensorMovi.scanOff();
xLastWakeTime = xTaskGetTickCount();
	
	for(;;){
		vTaskDelayUntil(&xLastWakeTime, 1000);
		sensorMovi.scanOn();
		_delay_ms(50);//se queda esperando hasta q se produce interrupcion.
		sensorMovi.scanOff();
		sei();		
	}
}
//______________________________________________________________________

void taskUS(void *pvParameters){
float distancia;
int dist, centena, decena, unidad, para = 5, sigue = 6, red = 66, apagar = 77;
char str[5];
portTickType xLastWakeTime;

ultraSoni.init();
xLastWakeTime = xTaskGetTickCount();
	
	for(;;){
		vTaskDelayUntil(&xLastWakeTime, 50);		
		distancia = ultraSoni.calculaDistancia();
		
		if(distancia > 0 && distancia < 100){
			dist = (char)(distancia);
			centena = (int)(dist / 100);
			dist = dist - (centena * 100);
			decena = (int)(dist / 10);
			dist = dist - (decena * 10);
			unidad = (int)(dist);
			str[0] = centena + 0x30;
			str[1] = decena + 0x30;
			str[2] = unidad + 0x30;
			str[3] = 0;
			serial.puts(str);
			//serial.putchar('\r');
			if(distancia < 25){
				serial.puts(" Alerta!\r");
			}
			else{
				serial.puts("        \r");
			}
			
		}
		else{
			serial.puts(">99 \r");
		}

		if(distancia > -1 && distancia < 25){	
			xQueueSend(colaRecep, (void *)&red, (portTickType)100);
			xQueueSend(colaRecep, (void *)&para, (portTickType)2000);//poner en colaRecep para que lo lea chief y no le permita avanzar (hacia adelante) a motores		
		}
		else{
			xQueueSend(colaRecep, (void *)&apagar, (portTickType)100);
			xQueueSend(colaRecep, (void *)&sigue, (portTickType)2000);//esta permitido avanzar hacia adelante, ie hay lugar para moverse
		}	
	}
}
//______________________________________________________________________

void taskRF(void *pvParameters){
int c = 0 , w = 1, s = 2, a = 3, d = 4;

	for(;;){	
		bicolor.direccion(1);
		bicolor.estado(1);
		c = serial.getcharr();
	
		if(c != -1){
							
			switch(c){
				
				case 'p':
				case 'P':
					vTaskSuspend(handleLED);
					break;
				case 'l':
				case 'L':
					vTaskResume(handleLED);
					break;
				case 'w':
				case 'W':
					xQueueSend(colaMtr, (void *)&w, (portTickType)2000);
					break;
				case 's':
				case 'S':
					xQueueSend(colaMtr, (void *)&s, (portTickType)2000);
					break;	
				case 'a':
				case 'A':
					xQueueSend(colaMtr, (void *)&a, (portTickType)2000);
					break;
				case 'd':
				case 'D':
					xQueueSend(colaMtr, (void *)&d, (portTickType)2000);
					break;	
				case 'x':
				case 'X':
					vTaskSuspend(handleSM);
					break;
				case 'b':
				case 'B':
					vTaskResume(handleSM);
					break;
			}									
		}
	}
}
//______________________________________________________________________
 
void taskChief(void *pvParameters){ 	 
int comando = -1;

vTaskSuspend(handleSM);

	for(;;){
		xQueueReceive(colaRecep, (void *)&comando, (portTickType)2000);//se bloquea, como maximo, 2k ticks hast q llega un dato (sin un dato no hago nada, asi q se bloquea)
		
		switch(comando){
			case ADELANTE:
			case ATRAS:
			case IZQUIERDA:
			case DERECHA:
			case PARAR:
			case SEGUIR:
			case IZQSENSOR:
			case DERSENSOR:
				xQueueSend(colaMtr, (void *)&comando, (portTickType)2000);//casos en q se recibe info de SM o RF
				break;
			case ROJO:
			case APAGAR:
				xQueueSend(colaLED, (void *)&comando, (portTickType)2000);
				break;
		}
	comando = -1;				
	}		
}
//______________________________________________________________________

void taskLED(void *pvParameters){	
portTickType xLastWakeTime;
int color = -1;

xLastWakeTime = xTaskGetTickCount();

	for(;;){
		vTaskDelayUntil(&xLastWakeTime, 200);
		xQueueReceive(colaLED, (void *)&color, (portTickType)0);
		
		switch(color){
		
		case ROJO:
			bicolor.estado(0);//prendo rojo
			bicolor.direccion(1);//pin como salida
			break;
		case APAGAR:	
			bicolor.direccion(0);//pin como salida
			break;
		}
		color = -1;
		led.toggle();
	}
}
//______________________________________________________________________

void taskMTR(void *pvParameters){ 
int mover = -1, parar = 0;

motores.init();

	for(;;){
		xQueueReceive(colaMtr, (void *)&mover, (portTickType)500);

		switch(mover){
			case ADELANTE:
				if(parar == 0){ //cuando l US esta muy cerca de algo, no se puede avanzar(solo hacia adelante) mas, por ejemplo si por RF se le solicita hacerlo
					cli();
					serial.desactivarSerial();
					motores.M_adelante(0xAFFF);
					vTaskDelay(350);
					motores.M_adelante(0);
					sei();
				}		
				break;
			case ATRAS:
				cli();
				serial.desactivarSerial();	
				motores.M_atras(0xFFFF);
				vTaskDelay(350);
				motores.M_atras(0);
				sei();
				break;
			case IZQUIERDA:
				cli();
				serial.desactivarSerial();		
				motores.M_izquierda(0xFFFF);		
				vTaskDelay(120);
				motores.M_izquierda(0);	 
				sei();
				break;
			case DERECHA:
				cli();
				serial.desactivarSerial();
				motores.M_derecha(0xFFFF);
				vTaskDelay(120);
				motores.M_derecha(0);	
				sei();	
				break;
			case PARAR://el us aviso q se esta cerca de la pared por ej
				parar = 1;
				break;	
			case SEGUIR://el us dice que se puede seguir moviendo libremente
				parar = 0;
				break;
			case IZQSENSOR:
				cli();
				serial.desactivarSerial();		
				motores.M_izquierda(0xAFFF);	
				vTaskDelay(80);
				motores.M_izquierda(0);			 
				sei();
				break;
			case DERSENSOR:
				cli();
				serial.desactivarSerial();
				motores.M_derecha(0xAFFF);
				vTaskDelay(80);
				motores.M_derecha(0);	
				sei();
				break;		
		}
		mover = -1;	
		serial.activarSerial();	
	}
}
//______________________________________________________________________

//*******************************MAIN***********************************
//********************************************************************** 
int main(void){
				
colaMtr =  xQueueCreate(1,sizeof(int)); // Guarda enteros que se traducen en la direccio o accion q van a realizar los motores
colaRecep = xQueueCreate(1,sizeof(int));//cola que va leyendo la tarea chief (recibe datos del US, SM y RF)
colaLED =  xQueueCreate(1,sizeof(int));//cola led para avisarle al led bicolor que prenda el verde o que se apague

xTaskCreate(taskChief, (const char*)"TareaCHF", configMINIMAL_STACK_SIZE, NULL, prioridadChief, &handleCHF);
xTaskCreate(taskMTR, (const char*)"TareaMTR", configMINIMAL_STACK_SIZE, NULL, prioridadMTR, &handleMTR);
xTaskCreate(taskSM, (const char*)"TareaSM", configMINIMAL_STACK_SIZE, NULL, prioridadSM, &handleSM);
xTaskCreate(taskUS, (const char*)"TareaUS", configMINIMAL_STACK_SIZE, NULL, prioridadUS, &handleUS);
xTaskCreate(taskRF, (const char*)"TareaRF", configMINIMAL_STACK_SIZE, NULL, prioridadRF, &handleRF);
xTaskCreate(taskLED, (const char*)"TareaLED", configMINIMAL_STACK_SIZE, NULL, prioridadLED, &handleLED);

vTaskStartScheduler();

return 1;
}


