#include "FreeRTOS.h"
#include "queue.h"
#include "task.h" //para taskYIELD
#include <avr/io.h>
#include <avr/interrupt.h>
#include "driverSM.h" 

xQueueHandle handleCola;// esta bien? ponerlo como variable de instancia mejor en el .h?

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
DriverSM::setCola(QueueHandle_t *hc){//mmmm..?
	handleCola = *hc;
}

//**********************************************************************

ISR(INT0_vect){//isr para interrupcion por int0
	signed portBASE_TYPE xTaskWokenByPost; 
	xTaskWokenByPost = pdFALSE;
	int a = 1;	// 1 para doblar izq
	
	xTaskWokenByPost = xQueueSendFromISR(handleCola, &a, &xTaskWokenByPost);
	
	if(xTaskWokenByPost) // != pdFALSE
		taskYIELD();	//forza el cambio de contexto	
}

ISR(INT1_vect){//isr para interrupcion por int1
	signed portBASE_TYPE xTaskWokenByPost;
	xTaskWokenByPost = pdFALSE;
	int b = 2;	// 2 para doblar derecha
	
	xTaskWokenByPost = xQueueSendFromISR(handleCola, &b, &xTaskWokenByPost);
	
	if(xTaskWokenByPost)
		taskYIELD();	//forza el cambio de contexto
}
//**********************************************************************
