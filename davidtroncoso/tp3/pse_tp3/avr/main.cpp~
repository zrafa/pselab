#include "serial.h"

int main()
{
    int c;

    SerialPort serial(0, 19200L, 64, 64);
    serial.puts("Hello, World!");

    while(1) { 

        while ((c = serial.getchar()) <= 0);
        serial.putchar((char)c);

    }

    return 0;
}
