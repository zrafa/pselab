#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define	PORTB	(*(volatile uint8_t *)0x25)
#define	DDRB	(*(volatile uint8_t *)0x24)

#define	PB5	5

enum nivel {LOW, HIGH};

class Gpio
{
    public:
        Gpio();
        ~Gpio();		
		void digitalWrite(int bit, nivel);		

};

#endif /* GPIO_H */

