#include "serial.h"
#include "scc.h"
#include <avr/interrupt.h> //incluyo librería de interrupciones 
 extern SCC scc;
//SerialPort serial(0, 9600L, 5, 5);
int main()
{
    char c;
	

sei();/* Habilito interrupciones globales */

    SerialPort serial(0, 9600, 64, 64);
    serial.puts("Hello, World!");

    while(1) { 
		
        while ((c = serial.getchar()) <= 0);
        serial.putchar((char)c);

    }

    return 0;
}


ISR(USART_TX_vect)
{
	
}

ISR(USART_UDRE_vect ) /*data register empty*/
{
scc.DataReg_intDisable(); /*deshabilito interrupciones por data register empty*/
scc.Transmit_Enable();/*habilito transmisión*/
while(!scc.DataReg_isEmpty(0));
scc.scc_put();         /*mando el dato*/
 
}

ISR(USART_RX_vect  )
{
	scc.clear_RxFlag();
	scc.Rx_Int_Disable();
	scc.scc_get();
}



