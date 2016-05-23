#include "serial.h"
#include "string.h"
char str[100]={};

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

int main()
{
    int c,i=0,cuenta=0;
    //CircBuf *pepe;		//Se declara el puntero hacia el buffer circular
	//pepe = new CircBuf(64);	//Se inicializa un buffer Circ.
    SerialPort serial(UART0, 19200L, 64, 64);
    serial.puts("Hello, World!");

    while(1) {
		while((c = serial.getchar()) <= 0);		//hasta que llegue algo se queda aca
        //serial.putchar((char)c);
		str[i]=c;		//Guarda lo que llego

		if(str[i] == '\r')		//Si llega el enter compara el string que llego con el que espera
		{
			//serial.puts(&str[0]);
			if(strcmp(str,"hello!\r")==0)
			{
				serial.puts("\nyay!");		//Si nos saludan, joya!
			}
			else
			{
				serial.puts("\ntu vieja");	//Sino, andate a la mierda... (?)
			}
			i=0;
			while(str[i]!=0){str[i]=0;i++;}	//Borra todo el string para el siguiente mensaje
			i=-1;
		}
		i++;	//Si no llego el enter, se aumenta el cursor para el prox caracter
		       
        
    }

    return 0;
}
 
