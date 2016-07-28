#include <stdio.h>
#include <avr/io.h>
#include <led.h>


Led::Led(volatile uint8_t *regDat, volatile uint8_t *regEst, char ledMask)
{
	rdd = regDat;
	rehl = regEst;
	lM = ledMask; 
	*rdd |= lM;
}

void
Led::enciende()
{
	*rehl |= lM;
}

void 
Led::apaga()
{
	*rehl &= (~lM);
}
void
Led::toggle()
{
	*rehl ^= lM;
}

void
Led::delay_ms(int ms)
{
	long volatile ciclos = ms * 9000;
	while(ciclos != 0){
		ciclos --;	
	}
}
