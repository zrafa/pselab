#include "serial.h"


int main()
{
    int c;

    SerialPort serial(0, 9600, 64, 64);
    serial.puts("Hello, World!"); //Guardamos en txQueue los caracteres de la cadena Hello World! a traves de la funcion putchar. 
								  //Internamente iniciamos el proceso de transmision de cada caracter por medio de txStart. En txStart si el buffer txQueue no esta
								  //vacio llamamos a serial_put_char(char) con el primer caracter de txQueue. Y serial_put_char(char) utiliza el periferico
								  //UART para depositar en el registro de datos (data_es) el caracter transmitido. Guardar el caracter en el registro data_es implica
								  //visualizarlo por consola.
								  //Resumiendo puts agrega en el buffer txQueue la cadena Hello World! caracter por caracter y los transmite automaticamente. Despues 
								  //de esta ejecucion el buffer txQueue queda vacio, porque para pasarle un elto a serial_put_char usamos el metodo remove() de CircBuf.

    while(1) { 

		//Despues de ejecutar serial.puts('Hello World!') el buffer txQueue queda vacio, de esta manera no ejecutamos serial.putchar((char) c), esta funcion se va a 
		//ejecutar cuando se ingrese un caracter por teclado.
		//Cuando ejecutamos serial.getchar() ocurre esto:
		//Si rxQueue no esta completo, en este momento esta vacio, llamamos a rxStart que le agrega a rxQueue el elto que devuelve serial_get_char().
		//serial_get_char hace que el programa quede ciclando si el bit 8 del registro control_a (RXC) no esta activado. Caso contrario devolvemos el contenido
		//del registro data_es. Ese elto se almacena en rxQueue  
        while ((c = serial.getchar()) <= 0); 
        serial.putchar((char)c); 

    }

    return 0;
}
