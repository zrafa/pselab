 #include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL 
#endif

#ifndef _LED_H
#define _LED_H

class Led
{	
	public:
	
		Led(volatile uint8_t *regDat, volatile uint8_t *regEst, char ledMask);
		
		void enciende();
		void apaga();
		void delay_ms(int ms);
		void toggle();
		
		volatile uint8_t *rdd;
		volatile uint8_t *rehl;
		char lM;
};

#endif /* _LED_H */
