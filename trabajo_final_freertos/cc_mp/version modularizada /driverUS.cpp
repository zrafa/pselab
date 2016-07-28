#include "FreeRTOS.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "driverUS.h"
#include "GPIO.h"

volatile float tiempo = 0,distancia = 0; //ver si hace falta q sean volatile
volatile char bandera =  0;


volatile uint8_t *pcimask;
volatile uint8_t *timer3crb;
//**********************************************************************
DriverUS::DriverUS(void){
}
//**********************************************************************
void
DriverUS::init(){
	tmr3crb = (uint8_t *) (0x91);		//Registro del TMR3 para seleccionar Clock Source     tccrnb????
	pcimsk = (uint8_t *) (0x6B);		//Registro para habilitar la interrup en PCINT5 (pcmsk0)
	pcicr = (uint8_t *) (0x68);		//Activar interrupciones para PCINT7 al PCINT0	
	tifr3= (uint8_t *) (0x38);		//Registro de banderas del timer3
	timsk3= (uint8_t *) (0x71);		//Registro de enable de interrupciones por timer3 (Solo para asegurarse de ponerlos en cero)
	
	pcimask = pcimsk;
	timer3crb = tmr3crb;
	
	*tmr3crb=0x02;		 //Clock= Fosc/8 (tiempo de desborde=32.76 mS, tiempo unitario=500 nS)     
	*pcimsk=0x20;		//Interrupcion en PCINT5;
	*pcicr=0x01;		//Habilita interrpciones por PCINT
	*timsk3 = 0;
}
//**********************************************************************

float //volatile float?
DriverUS::calculaDistancia(){//dist <30 stop, 
/* El esquematico dice que SENSOR_0 esta conectado al ADC5, sin embargo, esta conectado al SENSOR_5.
 * Por lo tanto, el sensor de ultrasonido esta conectado en el S5 del robot */
GPIO ultrasonido((volatile uint8_t *) 0x21,(volatile uint8_t *) 0x20, 5);	//Sensor ultrasonido RA5	
volatile uint8_t aux1tmr3, aux2tmr3;

	cli();
	ultrasonido.direccion(1);
	ultrasonido.estado(0);
	_delay_us(2);
	ultrasonido.estado(1);		//Se le da el pulso inicial
	_delay_us(10);
	ultrasonido.estado(0);
	ultrasonido.direccion(0);	//Se pone como entrada para leer la longitud del pulso
	bandera=0;
	
	*pcimsk = 0x20;
	*pcicr = 0x01;
	sei();
	
	while(bandera==0);		//Espera a que se interrumpa

	bandera=2;	//Si vale 1 ahora la ponemos en 2 para que pueda entrar a la parte de la interrupcion que queremos
		
	while(bandera==2);	//Espera a la segunda interrupcion
	
	if( (*tifr3 & 0x01) != 0 )	//Si hubo desborde del timer3 entonces no se prende ningun led
	{
		cli();
		*tifr3=0x01;	//Pone un uno en el bit TOV3 para bajar la bandera
		distancia = 400;
	}
	else
	{
		cli();
		aux1tmr3=TCNT3L;		//Se tiene que leer primero el LSB
		aux2tmr3=TCNT3H;
		tiempo= (float)((aux2tmr3*256 + aux1tmr3) * 0.5);	//Se obtiene la cuenta del timer en uS
		
		distancia=tiempo / 58;	//Distancia en cm	

	}
return distancia;
}
//**********************************************************************
ISR(PCINT0_vect){
	
	if(bandera==0)
	{
		TCNT3H=0;
		TCNT3L=0;		//Se pone la cuenta en cero
		*timer3crb=0x02;		//Clock= Fosc/8 (tiempo de desborde=32.76 mS, tiempo unitario=500 nS)
		bandera=1;
	}
	if(bandera==2)
	{
		*pcimask &= 0xDF;	//Deshabilita interrupciones por PCINT2
		*timer3crb=0;		 	//Clock= 0 (contador parado)
		bandera=0;
	}
}
