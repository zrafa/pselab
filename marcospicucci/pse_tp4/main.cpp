#include "serial.h"
//**********************************************************************
int longiptr(char *fname){//devuelve la longitud de un puntero a char
	int i=0;
	while(fname[i] != '\0')
		i++;
		
return i;		
}
//**********************************************************************
int sonIguales(char *p1, char *p2){
	int i;
	int band = 1, sale = 1;
	char c1,c2;
	
	if(longiptr(p1) == longiptr(p2)){
		for(i=0;(i<(longiptr(p1)) && (band==1));i++){
			c1 = *(p1 + i);
			c2 = *(p2 + i);
								
			if(c1 != c2){
				band = 0;
				sale = 0;
			}			
		}
	}
	else
		sale = 0;	
	
	return sale;
} 

//**********************************************************************
int main()
{
    int c;
	char str[10];
	
    SerialPort serial(0, 19200L, 64, 64); //baudrate?
    
    
    serial.puts("Hello, World!");

    while(1) { 

        while ((c = serial.getchar()) <= 0);
        serial.putchar((char)c);

    }

    return 0;
}
