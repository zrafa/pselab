
//Evitamos hacer inclusiones recursivas de archivos. 
#ifndef _LED_H
#define _LED_H

#define HABILITAR_SALIDA   0x20

class Led {

	public :
			Led(volatile unsigned char *direccion, volatile unsigned char *led, volatile unsigned char mask);

			void encender();
			void apagar();
			void delay(long milisegundos);

	private :
			volatile unsigned char *puerto;      //PORTB 0x24 --- Registro de direcciones. Contiene la direccion de memoria donde se encuentra mapeado el registro de 													   direcciones.

			volatile unsigned char *led;         //PORTB 0x25 --- Registro de estado. Controla el estado ALTO/BAJO de un pin de salida. 
			
			volatile unsigned char mascara; 	 //Mascara para encender/apagar un led del arduino pro-mini. Se puede usar con el pin 9 de la plataforma HW en una 												   	   protoboard.

};


#endif 
