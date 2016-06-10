#include "serial.h"
#include "string.h"
#include <util/delay.h>                // for _delay_ms()
#include <avr/io.h>
char str[100]={};

char arriba[5]={0x86,0x66,0xE6,0x98,0x66};
char abajo[5]={0x66,0x66,0x1E,0x66,0xFE};
char derecha[5]={0x66,0x66,0xE6,0x98,0xE6};
char izquierda[5]={0x86,0x66,0x1E,0x66,0xFE};
char menu[5]={0x66,0x66,0x98,0xF8,0xF8};

#define LED 0x20

#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

int main()
{
    int c,n,i=0,cuenta=0;
    char buffer[20]={};
    //CircBuf *pepe;		//Se declara el puntero hacia el buffer circular
	//pepe = new CircBuf(64);	//Se inicializa un buffer Circ.
    SerialPort serial(UART0, 2400UL, 64, 64);
    serial.puts("Hello, World!");
	DDRB=0x20;
	PORTB=0;
	PORTB+=LED;
	_delay_ms(500);
	PORTB-=LED;
    while(1) {
		//while(1)
		//{
			while((c = serial.getchar()) <= 0);
			PORTB+=LED;	
			buffer[i]=c;
			i++;
			if(i==5)
			{
				//serial.putchar(buffer[0]);
				//serial.putchar(buffer[1]);
				//serial.putchar(buffer[2]);
				//serial.putchar(buffer[3]);
				//serial.putchar(buffer[4]);
				//i=0;
			//}
			//PORTB-=LED;
		//}
		//i=0;
		//while(i<5)
		//{
			//while((c = serial.getchar()) <= 0);
			//buffer[i]=c;
			//i++;

		//}
				serial.putchar(buffer[0]);
				serial.putchar(buffer[1]);
				serial.putchar(buffer[2]);
				serial.putchar(buffer[3]);
				serial.putchar(buffer[4]);
		i=0;
		if(strcmp(buffer,arriba)==0)
		{
			serial.puts("Arriba");
			for(i=0;i<1;i++)
			{
				PORTB+=LED;
				_delay_ms(100);
				PORTB-=LED;
				_delay_ms(100);
			}
		}
		if(strcmp(buffer,abajo)==0)
		{
			serial.puts("Abajo");
			for(i=0;i<2;i++)
			{
				PORTB+=LED;
				_delay_ms(100);
				PORTB-=LED;
				_delay_ms(100);
			}
		}
		if(strcmp(buffer,izquierda)==0)
		{
			serial.puts("Izquierda");
			for(i=0;i<3;i++)
			{
				PORTB+=LED;
				_delay_ms(100);
				PORTB-=LED;
				_delay_ms(100);
			}
		}
		if(strcmp(buffer,derecha)==0)
		{
			serial.puts("Derecha");
			for(i=0;i<4;i++)
			{
				PORTB+=LED;
				_delay_ms(100);
				PORTB-=LED;
				_delay_ms(100);
			}
		}
		if(strcmp(buffer,menu)==0)
		{
			serial.puts("Menu");
			for(i=0;i<5;i++)
			{
				PORTB+=LED;
				_delay_ms(100);
				PORTB-=LED;
				_delay_ms(100);
			}
		}
  
        
    }
}
    return 0;
}
 
