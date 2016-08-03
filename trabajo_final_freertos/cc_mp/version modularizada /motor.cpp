#include "FreeRTOS.h"
#include "task.h"
#include "motor.h"

Motor::Motor(){
}

void
Motor::init(){
    DDRB |= (1 << DDB3) | (1 << DDB2) | (1 << DDB1)| (1 << DDB0);// PB3, PB2, PB1, PB0 salida (control del direccion)  
    DDRD |= (1 << DDD4)|(1 << DDD5);// PD4 PD4 salida (control de velocidad) 
    ICR1 = 0xFFFF;// pone TOP al maximo (16bit)
    OCR1A = 0x0000;// pone ciclo de trabajo (16bit) del motor A
    OCR1B = 0x0000;// pone ciclo de trabajo (16bit) del motor B
    TCCR1A |= (1 << COM1A1)|(1 << COM1B1);// Pone modo no invertido
    TCCR1A |= (1 << WGM11);// Pone mode Fast PWM usando ICR1 como TOP
    TCCR1B |= (1 << WGM13)|(1 << WGM12);  
    TCCR1B |= (1 << CS10);	// Inicia el temporizador en modo no prescaler	
}

void
Motor::M_adelante(unsigned int pwm){//cabiar para q avance mas lento con motor izquierdo porq sino dobla solo a la derecha cuando avanza
	PORTB &= ~(1 << MOTA1);	// Direccion motor A:	IN1 = 0
	PORTB |= (1 << MOTA2);	// 						IN2 = 1 
	OCR1A = pwm;  //- (pwm / 3);			// Velocidad motor A
	PORTB &= ~(1 << MOTB1);	// Direccion motor B:	IN3 = 0
	PORTB |=  (1 << MOTB2);// 						IN4 = 1
	OCR1B = pwm - (pwm / 8);			// Velocidad motor B	
}
 
void
Motor::M_atras(unsigned int pwm){
		PORTB |= (1 << MOTA1);// Direccion motor B:		IN1 = 1
		PORTB &= ~(1 << MOTA2);	// 						IN2 = 0
		OCR1A = pwm;			// Velocidad motor A	
		PORTB |=  (1 << MOTB1);	// Direccion motor B:	IN3 = 1
		PORTB &= ~(1 << MOTB2);	// 						In4 = 0
		OCR1B = pwm;			// Velocidad motor B
}

void
Motor::M_izquierda(unsigned int pwm){
		PORTB &= ~(1 << MOTA1);	// Direccion motor A:	IN1 = 0
		PORTB |= (1 << MOTA2);	// 						IN2 = 1 
		OCR1A = pwm;	
		PORTB |=  (1 << MOTB1);	// Direccion motor B:	IN3 = 1
		PORTB &= ~(1 << MOTB2);	// 						In4 = 0
		OCR1B = pwm;			// Velocidad motor B
}

void
Motor::M_derecha(unsigned int pwm){
		PORTB |= (1 << MOTA1);	// Direccion motor B:	IN1 = 1
		PORTB &= ~(1 << MOTA2);	// 						IN2 = 0
		OCR1A = pwm;			// Velocidad motor A		
		PORTB &= ~(1 << MOTB1);	// Direccion motor B:	IN3 = 0
		PORTB |=  (1 << MOTB2);	// 						IN4 = 1
		OCR1B = pwm;			// Velocidad motor B	
}
