#include <avr/io.h>
#include <avr/interrupt.h>
#include <led.h>

//***************Este es el fuente de prueba que usamos para probar los sensores de movimiento************************

Led led((uint8_t volatile *)0x24, (uint8_t volatile *)0x25, 0x20);
Led led2((uint8_t volatile *)0x24, (uint8_t volatile *)0x25, 0x2);

int main(void){

volatile uint8_t *eicra, *eimsk;//external interrupt control registerA, external interrupt mask register

eicra = (uint8_t *) (0x69);
eimsk = (uint8_t *) (0x3D);
*eicra = 0b00001010; //genera interrupcion(INT0/INT1) por falling edge, 00001111 para rising edge
*eimsk = 0b00000011; //activo request 0/1 de inter. ext.
sei();

	while(1){
		
	}

}


ISR(INT0_vect){//isr para interrupcion por int0
led.enciende();
led.delay_ms(1000);		//cuiao
led.apaga();
}

ISR(INT1_vect){//isr para interrupcion por int1
led2.enciende();
led2.delay_ms(1000);
led2.apaga();
}
