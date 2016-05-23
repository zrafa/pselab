#include "serial.h"
//SerialPort serial(0, 9600L, 5, 5);
int main()
{
    char c;

    SerialPort serial(0, 9600, 64, 64);
    serial.puts("Hello, World!");

    while(1) { 
		
        while ((c = serial.getchar()) <= 0);
        serial.putchar((char)c);

    }

    return 0;
}
