#include <stdio.h>
#include <avr/io.h>
#include <led.h>


Led::Led(volatile uint8_t *regDat, volatile uint8_t *regEst, char ledMask)
{
	//rdd = (uint8_t volatile *)REG_DIR_DAT; //guarda, sino hacerlo en el .h?
	//rehl = (uint8_t volatile *)REG_ESTADO_HIGH_LOW;
	//*rdd |= LED_MASK;
	
	rdd = regDat;
	rehl = regEst;
	lM = ledMask; 
	*rdd |= lM;
}

void
Led::enciende()
{
	//*rehl |= LED_MASK;
	*rehl |= lM;
}

void 
Led::apaga()
{
	//*rehl &= (~LED_MASK);
	*rehl &= (~lM);
}

void
Led::delay_ms(int ms)
{
	long volatile ciclos = ms * 9000;
	while(ciclos != 0){
		ciclos --;	
	}
}
