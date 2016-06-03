 #include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

#ifndef _LED_H
#define _LED_H

//#define LED_MASK (0x20)
//#define REG_DIR_DAT (0x24)
//#define REG_ESTADO_HIGH_LOW (0x25)

class Led
{	
	public:
		
		//Led(); //deberia cambiar para q no sea dependendiente d un unico led, ie para distintos puertos etc
		Led(volatile uint8_t *regDat, volatile uint8_t *regEst, char ledMask);
		
		void enciende();
		void apaga();
		void delay_ms(int ms);
		
		volatile uint8_t *rdd;
		volatile uint8_t *rehl;
		char lM;
};

#endif /* _LED_H */
