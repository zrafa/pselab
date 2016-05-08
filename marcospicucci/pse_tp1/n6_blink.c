#include <stdio.h> 
#include <avr/io.h>
#include <util/delay.h>

#define LED_MASK (0x80)
#define REG_DIR_DAT_B (0x24)
#define REG_ESTADO_B (0x25)
#define REG_DIR_DAT_A (0x21)
#define REG_ESTADO_A (0x22)

uint8_t volatile *rddb = (uint8_t volatile *)REG_DIR_DAT_B ;
uint8_t volatile *reb = (uint8_t volatile *)REG_ESTADO_B ;

void inicializaLed(){
	*rddb = (*rddb) | (LED_MASK) ;
}

void cambiaLed(){
	*reb = (*reb) ^ (LED_MASK) ;
}

void delay_ms(int ms){
	long volatile ciclos = ms * 9000;
	while(ciclos != 0){
		ciclos --;	
	}
}

int main(void)
{
	inicializaLed();
	//printf(" check this\n");
	while (1){
		cambiaLed();
		delay_ms(200);//parpadea a las chapas
	}
