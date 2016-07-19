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
SerialPort serial(0, 9600, 120, 120);

//void leer_caracter (void *pvParameters);
void mostrar_medicion_imu ();
void delay(int milisegundos);

int main (){

spi.SPI_MasterInit();
serial.puts("Hola");

while (1){

//delay(1000);
mostrar_medicion_imu();
delay(7000);
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
uint8_t read_h = ((imu.get_sensor_magnetico())->hzh) ;

// Obtenemos la medicion realizada por la imu.
spi.SPI_MasterTransmit(read_h);
//uint8_t *read = (uint8_t *)0x88;
uint8_t read = 0x88;
//uint8_t medicion_h=spi.SPI_SlaveReceive();
uint8_t medicion_h = 12;
//uint8_t read_l = ((imu.get_sensor_magnetico())->hzl) | 0x80;
//spi.SPI_MasterTransmit(read_l);

//uint8_t medicion_l=spi.SPI_SlaveReceive();

spi.cs(HIGH);
//int medicion=10;
char mensaje[100];
sprintf(mensaje, "Esta es la medicion del sensor magnetico : %x ", read_h);
//Enviamos el contenido de mensaje al registro de datos.
serial.puts(mensaje);

led_rojo.encender();

}

void delay (int milisegundos){

int n=(100*milisegundos);
int i;
for(i=0; i<n; i++)
	;

}
