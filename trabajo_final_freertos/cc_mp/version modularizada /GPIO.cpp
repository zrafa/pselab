#include <stdio.h>
#include <avr/io.h>
#include <GPIO.h>


//Esta clase tiene la diferencia que en lugar de darle la direccion del bit, se le da el numero del bit.
//Es decir, en lugar de poner 0x20 se pone 3, o en lugar de 0x80 se pone 7.
GPIO::GPIO(volatile uint8_t *regDat, volatile uint8_t *regEst, char Mask)
{
	rdd = regDat;
	rehl = regEst;
	lM = Mask; 
}

void
GPIO::direccion(int dir)
{
	if(dir==0)
		*rdd &= ~(1 << lM);
	else if(dir==1)
		*rdd |= (1 << lM);
}

void
GPIO::estado(int est)
{
	if(est==0)
		*rehl &= ~(1 << lM);
	else if(est==1)
		*rehl |= (1 << lM);
}

int
GPIO::leer()
{
	return (*rehl & (1 << lM));
}

void
GPIO::delay_ms(int ms)
{
	long volatile ciclos = ms * 9000;
	while(ciclos != 0){
		ciclos --;	
	}
}
