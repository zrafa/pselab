
#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

#define MOTA1	PB0			// IN2	
#define MOTA2	PB1			// IN1
#define MOTB1	PB3			// IN3
#define MOTB2	PB2			// IN4
#define PWMA	PD5			// EN_A	(OC1A)
#define PWMB	PD4			// EN_B	(OC1B)

#define RUNSW	PC7			// RUN SWITCH

#define TOP		0xFFFF		

class Motor {

public : 
			Motor();

	        void M_adelante(unsigned char motor, unsigned int pwm);
		    void M_atras(unsigned char motor, unsigned int pwm);
		    void vMotor(void* pvParameters);
			
};

#endif /* MOTOR_H */
