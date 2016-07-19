
//Evitamos hacer inclusiones recursivas de archivos. 
#ifndef _LED_H
#define _LED_H

//Mascaras para encender el led rojo de la placa arduino promini.
#define DDRB           0x24       //Direccion de memoria del registro de direcciones. Se usa habilitar un pin para salida.
#define PORTB          0x25       //Direccion de memoria del registro de estado. Este registro se usa para encender/apagar un led.
#define ENCENDER       0x20       //Mascara para encender/apagar el led rojo del arduino pro-mini.

//Mascaras para encender el led amarillo de la placa duino-bot.
#define ENCENDER_DB    0x80

//Mascaras para encender el led bicolor de la placa duino-bot.
#define DDRA_BI        0x21
#define PORTA_BI       0x22

class Led {

	public :
			/*
				direccion : DDR.
				led       : PORTX.
			*/
			Led(volatile unsigned char *direccion, volatile unsigned char *led, volatile unsigned char mask);

			void encender();
			void apagar();
			void delay(long milisegundos);

	private :
			volatile unsigned char *puerto;      //DDRB 
			volatile unsigned char *led;         //PORTX 
			volatile unsigned char mascara; 	 //Mascara para encender/apagar un led de las placas duino-bot o pro-mini.

};


#endif 
