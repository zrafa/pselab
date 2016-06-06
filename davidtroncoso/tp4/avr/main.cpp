#include "serial.h"
#include <avr/interrupt.h>
#include <avr/io.h>



int main()
{



    int c;

    SerialPort serial(0, 9600L, 64, 64);

		sei();		//Habilito interrupciones globales

    //serial.puts("Hello, World!");



    while(1) { 

        while ((c = serial.getchar()) <= 0);
        serial.putchar((char)c);

    }

    return 0;
}


