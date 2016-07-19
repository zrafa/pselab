
#include "motor.h"

Motor::Motor(){

	// PB3, PB2, PB1, PB0 salida (control del direccion)
    DDRB |= (1 << DDB3) | (1 << DDB2) | (1 << DDB1)| (1 << DDB0);

    // PD4 PD4 salida (control de velocidad)
    DDRD |= (1 << DDD4)|(1 << DDD5);

    // pone TOP al maximo (16bit)
    ICR1 = 0xFFFF;

    // pone ciclo de trabajo (16bit) del motor A
    OCR1A = 0x0000;

    // pone ciclo de trabajo (16bit) del motor B
    OCR1B = 0x0000;
 
    // Pone modo no invertido
    TCCR1A |= (1 << COM1A1)|(1 << COM1B1);

    // Pone mode Fast PWM usando ICR1 como TOP
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13)|(1 << WGM12);
    
    // Inicia el temporizador en modo no prescaler
    TCCR1B |= (1 << CS10);

}

void
Motor::M_adelante(unsigned char motor, unsigned int pwm){

	if (motor == 0) {
		PORTB &= ~(1 << MOTA2);	// Direccion motor A:	IN1 = 0
		PORTB |= (1 << MOTA1);	// 						IN2 = 1 

		OCR1A = pwm;			// Velocidad motor A
	}
	else if (motor == 1) {
		PORTB &= ~(1 << MOTB1);	// Direccion motor B:	IN3 = 0
		PORTB |=  (1 << MOTB2);	// 						IN4 = 1

		OCR1B = pwm;			// Velocidad motor B
	}

}

void
Motor::M_atras(unsigned char motor, unsigned int pwm){

	if (motor == 0) {
		PORTB |= (1 << MOTA2);	// Direccion motor B:	IN1 = 1
		PORTB &= ~(1 << MOTA1);	// 						IN2 = 0

		OCR1A = pwm;			// Velocidad motor A
	}
	else if (motor == 1) {
		PORTB |=  (1 << MOTB1);	// Direccion motor B:	IN3 = 1
		PORTB &= ~(1 << MOTB2);	// 						In4 = 0

		OCR1B = pwm;			// Velocidad motor B
	}

}

void
Motor::vMotor(void* pvParameters){

	//motors_init();

	M_adelante(0, 0xFFFF);
	M_atras(1, 0xFFFF);

	for ( ;; )
	{
	}

}

