#include "serial.h"


int main()
{
    int c;

    SerialPort serial(0, 19200L, 64, 6);
    serial.puts("Hello, World!");
    serial.puts("123456");
    while(1) {

        while ((c = serial.getchar()) <= 0);
        serial.putchar((char)c);

    }

    return 0;
}
