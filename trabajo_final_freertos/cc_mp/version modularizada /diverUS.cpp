#include <avr/io.h>
#include <avr/interrupt.h>
#include "driverUS.h"

DriverUS::DriverUS(void){
}
//**********************************************************************
void
DriverUS::init(){
	tmr3crb = (uint8_t *) (0x91);		//Registro del TMR3 para seleccionar Clock Source     tccrnb????
	pcimsk = (uint8_t *) (0x6B);		//Registro para habilitar la interrup en PCINT5 (pcmsk0)
	pcicr = (uint8_t *) (0x68);		//Activar interrupciones para PCINT7 al PCINT0	
	*tmr3crb=0x02;		 //Clock= Fosc/8 (tiempo de desborde=32.76 mS, tiempo unitario=500 nS)     ???
	*pcimsk=0x20;		//Interrupcion en PCINT5;
	*pcicr=0x01;		//Habilita interrpciones por PCINT

}



ISR(PCINT0_vect){
	
	//calculo distancia??
}
