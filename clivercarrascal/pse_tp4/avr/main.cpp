#include "serial.h"

int main()
{
    int c,cuenta=0;
    //CircBuf *pepe;		//Se declara el puntero hacia el buffer circular
	//pepe = new CircBuf(64);	//Se inicializa un buffer Circ.
    SerialPort serial(UART0, 19200L, 64, 64);
    serial.puts("Hello, World!");

    while(1) {

        while((c = serial.getchar()) <= 0);
        serial.putchar((char)c);
    }

    return 0;
}

