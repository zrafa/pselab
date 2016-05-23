#include "serial.cpp"
#include "circbuf.cpp"

int main()
{
    char c;

    SerialPort serial(0, 19200L, 64, 64);
    serial.puts("Hello, World!");

    while(1) { 
		
        while ((c = serial.getchar()) <= 0);
        serial.putchar((char)c);

    }

    return 0;
}
