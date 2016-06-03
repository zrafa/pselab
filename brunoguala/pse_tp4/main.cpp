#include "serial.h"
//Importamos esta libreria para poder hacer uso de la funcion sei().
#include <avr/interrupt.h>

int main()
{
    int c;

	//Las interrupciones externas, generadas por un dispositvo de E/S ubicado fuera del chip, tienen un bit individual de habilitacion/deshabilitacion. Ademas existe
	//un bit global de habilitacion/deshabilitacion de interrupciones conocido como I-Bit. El I-Bit se encuentra en el registro de estado SREG y actua como un indicador 	 //global de interrupciones. Poniendo el I-Bit en 1 se activan todas las interrupciones excepto aquellas que tiene un bit individual de habilitacion/deshabilitacion.
	//Las interrupciones externas se habilitan solamente si el I-Bit y los bits individuales estan en 1. Podemos hacer uso de sentencias sei o cli para poner el 
	//I-Bit en 1 o 0, respectivamente. En este caso utilizamos la funcion sei() de la libreria interrupt para activar globalmente interrupciones mediante SW.
	sei();

    SerialPort serial(0, 9600, 64, 64);
    serial.puts("Hello, World!"); //Guardamos en txQueue los caracteres de la cadena Hello World! a traves de la funcion putchar. 
								  //Internamente iniciamos el proceso de transmision de cada caracter por medio de txStart. En txStart si el buffer txQueue no esta
								  //vacio activamos interrupciones de transmision. El proceso de termina cuando la macro ISR(USART_UDRE_vect) deposita en el registro de 									  //datos (data_es) el caracter transmitido. Guardar el caracter en el registro data_es implica visualizarlo por consola.
								
    while(1) { 

		//Despues de ejecutar serial.puts('Hello World!') el buffer txQueue queda vacio, de esta manera no ejecutamos serial.putchar((char) c), esta funcion se va a 
		//ejecutar cuando se ingrese un caracter por teclado.
		//Cuando ejecutamos serial.getchar() ocurre esto:
		//Si rxQueue no esta completo, en este momento esta vacio, llamamos a rxStart que activa interrupciones de recepcion y le agrega a rxQueue el elto que se
		//encuentra en el registro de datos, data_es, mediante la macro ISR(USART_RX_vect).
        while ((c = serial.getchar()) <= 0); 
        serial.putchar((char)c); 

    }

    return 0;
}
