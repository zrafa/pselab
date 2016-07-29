#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
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

int main (){
sei();
spi.SPI_MasterInit();
serial.puts("Hola");

while (1){

mostrar_medicion_imu();

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

spi.cs(0);
uint8_t read_h = ((imu.get_sensor_magnetico())->hzh) ;

volatile uint8_t cr= ((spi.get_registros_spi())->control_register);
volatile uint8_t sr= ((spi.get_registros_spi())->status_register);

uint8_t x=(spi.get_pspi())->ddr_spi;

spi.SPI_MasterTransmit(0x48);
spi.SPI_MasterTransmit(0x01);
uint8_t data_h=spi.SPI_SlaveReceive();

spi.SPI_MasterTransmit(0x01);
uint8_t data_l=spi.SPI_SlaveReceive();

char k[100];
sprintf(k, "Este es el valor de hzh despues de ejecutar el 1 master_transmit : %x ", data_h);
serial.puts(k);

sprintf(k, "Este es el valor de hzl despues de ejecutar el 2 master_transmit : %x ", data_l);
serial.puts(k);

spi.cs(1);

char mensaje[100], men[100];
sprintf(mensaje, "Este es el contenido del registro ddr_spi %x ", x);

//Enviamos el contenido de mensaje al registro de datos.
serial.puts(mensaje);
sprintf(men, "Este es el contenido de SPCR : %x", cr);
serial.puts(men);

}

ISR ( SPI_STC_vect ){

char k[100];
sprintf(k, "Este es el contenido de SPDR dentro de ISR : %x ", (spi.get_registros_spi())->data_register);
serial.puts(k);

}

