 #include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL 
#endif

#ifndef _GPIO_H
#define _GPIO_H

class GPIO
{	
	public:
	
		GPIO(volatile uint8_t *regDat, volatile uint8_t *regEst, char Mask);
		
		void direccion(int dir);
		void estado(int est);
		int  leer();
		void delay_ms(int ms);
		
		volatile uint8_t *rdd;
		volatile uint8_t *rehl;
		char lM;
};

#endif /* _LED_H */
