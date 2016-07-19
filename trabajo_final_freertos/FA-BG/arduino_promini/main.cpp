#include <avr/io.h>
#include <stdlib.h>
#include "spi.h"
//#include "nRF24L01.h"
//#include "scc.h"
#include "serial.h"
#include "led.h"
#include "MPU9250.h"

SPI spi;
MPU9250 imu;
//nRF24L01 transceptor;

Led led_rojo((volatile unsigned char *) DDRB, (volatile unsigned char *) PORTB, ENCENDER);
SerialPort serial(0, 9600, 50, 50);

//void leer_caracter (void *pvParameters);
void mostrar_medicion_imu ();
void delay(int milisegundos);

int main (){

spi.SPI_MasterInit();
//serial.putchar('H');
while (1){
//serial.puts("Hola");
//delay(1000);
mostrar_medicion_imu();
//delay(1000);
/*led_rojo.encender();
led_rojo.delay(1000);
led_rojo.apagar();
led_rojo.delay(1000);
*/
}

return 1;

}

/*void leer_caracter (void *pvParameters){

// Obtenemos el caracter ingresado mediante la funcion get_char.
int c;

switch (c){

case 115 :
case 97  :
case 114 :
case 100 :
case 105 : //Inicializamos el tr en modo PTX.
		   //Escribimos el caracter en el buffer TX FIFO
		   break;
 
}

}*/

void mostrar_medicion_imu (){

//Si pin IRQ esta en low => esperar.
spi.cs(LOW);
// Obtenemos la medicion realizada por la imu.
spi.SPI_MasterTransmit((imu.get_sensor_magnetico())->hzh);

//uint8_t medicion=spi.SPI_SlaveReceive();
//int medicion=10;
//char mensaje[100];
//sprintf(mensaje, "Esta es la medicion del sensor magnetico : %d ", medicion);
//Enviamos el contenido de mensaje al registro de datos.
//serial.puts("Hola");

led_rojo.encender();

}

void delay (int milisegundos){

int n=(100*milisegundos);
int i;
for(i=0; i<n; i++)
	;

}
