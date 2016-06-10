#include<avr/io.h>


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
   	uint8_t status_control_a;	/* ucsr0a USART Control and Status A (0xc0) */
	uint8_t status_control_b;	/* ucsr0b USART Control and Status B (0xC1) */
	uint8_t status_control_c; 	/* ucsr0c USART Control and Status C (0xC2) */
	uint8_t _reserved;			/* espacio sin utilizar (0xC3) */
	uint8_t baud_rate_l;		/* ubrr0l baud rate low (0xC4)*/
	uint8_t baud_rate_h;		/* ubrr0h baud rate high (0xC5) */
	uint8_t data_es; 			/* udr0 i/o data (0xC6) */

} volatile uart_t;


/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);


#define F_CPU 16000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define recive_transmit_eneable 0x18
#define paridadpar_2bitstop 0x24


void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
		

		
	puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE>>8);
	puerto_serial->baud_rate_l = (unsigned char)BAUD_PRESCALE;

		/* equivalentemente 
			UBRR0H = (unsigned char)(BAUD_PRESCALE>>8);
		  	UBRR0L = (unsigned char)BAUD_PRESCALE; */


	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */

	puerto_serial->status_control_c |= paridadpar_2bitstop;

	// equivalente UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01)|(1<<UPM01)|(0<<UPM00);
	
	/* Activar la recepcion y transmicion */
	
	puerto_serial->status_control_b |= recive_transmit_eneable;

	// equivalente  UCSR0B = (1<<RXEN0)|(1<<TXEN0); 	

}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

	while ( !(( puerto_serial->status_control_a & 0x20) == 0x20) )
		;

    /* Send the character via the serial port. */

	puerto_serial->data_es = outputChar;

}

char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
	while ( !((puerto_serial->status_control_a & 0x80) ==0x80)) 
		;


	/* Get and return received data from buffer */
	return puerto_serial->data_es;

	

}



