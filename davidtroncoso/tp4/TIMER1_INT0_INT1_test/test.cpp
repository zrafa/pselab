#include <gpio.h>
#include <timer.h>
#include <avr/interrupt.h>

Gpio pb;
Timer  timer;


#define LED_ROJO 5

volatile int status;
volatile int old_status;
extern "C" void delay(unsigned int);

void blink(int n)
{
	int count;

	count = n;
	while(count--)
	{
		pb.digitalWrite(LED_ROJO, HIGH);
		delay(500);
		pb.digitalWrite(LED_ROJO, LOW);
		delay(500);
	}
}

int main(void)
{
    timer.start(500, Periodic);		// Start a periodic 500-ms timer.
 
// Configuración PCINT0
    DDRD &= ~(1 << DDD2);				// Clear the PD2 pin, PD2 (PCINT0 pin) is now an input
    PORTD |= (1 << PORTD2);   			// turn On the Pull-up, PD2 is now an input with pull-up enabled
    EICRA |= (1 << ISC00);				// set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);				// Turns on INT0

// Configuración PCINT1
    DDRD &= ~(1 << DDD3);				// Clear the PD3 pin, PD3 (PCINT1 pin) is now an input
    PORTD |= (1 << PORTD3);   			// turn On the Pull-up, PD3 is now an input with pull-up enabled
    EICRA |= (1 << ISC01);				// set INT1 to trigger on ANY logic change
    EIMSK |= (1 << INT1);				// Turns on INT1

//	Habilita interrupciones
	sei();

	blink(4);

    while(1)
    {
		if (status != old_status) {
			blink(status);
			status = 0;
		}
    }

	return 0;
}   /* main() */

ISR(INT0_vect)
{
	status = 2;
}

ISR(INT1_vect)
{
	status = 4;
}


