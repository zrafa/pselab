#include "FreeRTOS.h"
#include "task.h"
#include "motor.h"

Motor::Motor()// Rutina de inicialización control de motores (CONSTRUCTOR)
{				//hacer asi o dejar el constructor vacio y dejar el init como estaba?
	
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
Motor::M_adelante(unsigned int pwm)
{
		PORTB &= ~(1 << MOTA2);	// Direccion motor A:	IN1 = 0
		PORTB |= (1 << MOTA1);	// 						IN2 = 1 
		OCR1A = pwm;			// Velocidad motor A
	
		PORTB &= ~(1 << MOTB1);	// Direccion motor B:	IN3 = 0
		PORTB |=  (1 << MOTB2);	// 						IN4 = 1
		OCR1B = pwm;			// Velocidad motor B	
}
 
void
Motor::M_atras(unsigned int pwm)
{
		PORTB |= (1 << MOTA2);	// Direccion motor B:	IN1 = 1
		PORTB &= ~(1 << MOTA1);	// 						IN2 = 0
		OCR1A = pwm;			// Velocidad motor A
	
		PORTB |=  (1 << MOTB1);	// Direccion motor B:	IN3 = 1
		PORTB &= ~(1 << MOTB2);	// 						In4 = 0
		OCR1B = pwm;			// Velocidad motor B
	
}

void
Motor::M_izquierda(unsigned int pwm)
{
		PORTB &= ~(1 << MOTA1);	// Direccion motor A:	IN1 = 0
		PORTB |= (1 << MOTA2);	// 						IN2 = 1 
		OCR1A = pwm;
		
		PORTB |=  (1 << MOTB1);	// Direccion motor B:	IN3 = 1
		PORTB &= ~(1 << MOTB2);	// 						In4 = 0
		OCR1B = pwm;			// Velocidad motor B
}

void
Motor::M_derecha(unsigned int pwm)
{
		PORTB |= (1 << MOTA1);	// Direccion motor B:	IN1 = 1
		PORTB &= ~(1 << MOTA2);	// 						IN2 = 0
		OCR1A = pwm;			// Velocidad motor A
		
		PORTB &= ~(1 << MOTB1);	// Direccion motor B:	IN3 = 0
		PORTB |=  (1 << MOTB2);	// 						IN4 = 1
		OCR1B = pwm;			// Velocidad motor B	
}

//hacer para que soble izq-derech retrocediendo??(para doblar, hasta ahora, lo hace avanzando)habria q usar 2 botones mas del CR..

/*
void
Motor::vMotor(void* pvParameters)//usar algun parametro para decidir si avanzar, retroceder ,etc
{
	
 	//motors_init();
	Motor motor();
	
	motor.M_adelante(0, 0xFFFF);
	motor.M_atras(1, 0xFFFF);

	for ( ;; )
	{
	}
}*/
