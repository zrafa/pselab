#include "FreeRTOS.h"
#include "queue.h"
#include "task.h" //para taskYIELD
#include <avr/io.h>
#include <avr/interrupt.h>
#include "driverSM.h" 

extern QueueHandle_t colaRecep;

//**********************************************************************
DriverSM::DriverSM(void){
}
//**********************************************************************
void
DriverSM::init(){
	eicra = (uint8_t *) (0x69);
	eimsk = (uint8_t *) (0x3D);
	*eicra = 0b00001010; //genera interrupcion(INT0/INT1) por falling edge, 00001111 para rising edge
	*eimsk = 0b00000011; //activo request 0/1 de inter. ext.
	sei();
}
//**********************************************************************
void
DriverSM::scanOff(){
*eimsk = 0b00000000;
}
//**********************************************************************
void
DriverSM::scanOn(){
*eimsk = 0b00000011;	
}
//**********************************************************************
/*
void
DriverSM::apagaIzq(){
*eimsk = 0b00000001;	
}
void
DriverSM::apagaDer(){
*eimsk = 0b00000010;	
}
*/
//**********************************************************************
ISR(INT0_vect){//isr para interrupcion por int0
	cli();
	signed portBASE_TYPE xTaskWokenByPost; 
	xTaskWokenByPost = pdFALSE;
	int a = 33;	// 3 para doblar izq
	
	xTaskWokenByPost = xQueueSendFromISR(colaRecep, &a, &xTaskWokenByPost);
	
	if(xTaskWokenByPost){ // != pdFALSE
		sei();
		taskYIELD();	//forzar el cambio de contexto	
	}
	sei();
}

ISR(INT1_vect){//isr para interrupcion por int1
	cli();
	signed portBASE_TYPE xTaskWokenByPost;
	xTaskWokenByPost = pdFALSE;
	int b = 44;	// 4 para doblar derecha
	
	xTaskWokenByPost = xQueueSendFromISR(colaRecep, &b, &xTaskWokenByPost);
	
	if(xTaskWokenByPost){
		sei();
		taskYIELD();	//forzar el cambio de contexto
	}
	sei();
}
//**********************************************************************
