#include <gpio.h>

Gpio::Gpio()
{
	DDRB |= (1 << PB5);
}

Gpio::~Gpio()
{
}

void Gpio::digitalWrite(int bit, nivel val)
{
	if (val == LOW)	
    	PORTB &= ~(1 << bit);
	else
    	PORTB |= (1 << bit);
}


