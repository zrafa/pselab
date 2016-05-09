#include<avr/io.h>


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */
    uint8_t baud_rate_h; /* ubrr0h baud rate high */
    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);


#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define RECEIVER_ENABLE 0x10 /* RXEN0 Habilitar la recepcion */
#define TRANSMITTER_ENABLE 0x08 /* TXEN0 Habilitar la transmicion */
#define CHARACTER_SIZE_0 0x20 /* UCSZ00 Numero de bits del dato de e/s */
#define CHARACTER_SIZE_1 0x40 /* UCSZ01 Numero de bits del dato de e/s */
#define READY_TO_READ 0x80 /* RXC0 Dato listo para leer */
#define READY_TO_WRITE 0x20 /* UDRE0 Buffer vacio listo para escribir */




void serial_init() {
	/*Set baud rate */
	puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE>>8);
	puerto_serial->baud_rate_l = (unsigned char)(BAUD_PRESCALE);
	/*Enable receiver and transmitter */
	
	/* Set frame format: 8data, 2stop bit */
	

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	puerto_serial->status_control_c = (unsigned char)0x06;
	/* Activar la recepcion y transmicion */
	puerto_serial->status_control_b = (unsigned char)((RECEIVER_ENABLE)|(TRANSMITTER_ENABLE));

}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
	while(!((puerto_serial->status_control_a)&(READY_TO_WRITE))){
	};
	puerto_serial->data_es = outputChar;
	
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada (pooling)*/
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir 
	se debe verificar si el reg d datos esta disponible-->bucle y leer bits del reg d estadps q me indican si puedo escribir*/

    // while ( /* completar con E/S programada */ )
    //     ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */

}


char serial_get_char(void)
{
	while(!((puerto_serial->status_control_a)&(READY_TO_READ)));
	
	return(puerto_serial->data_es);
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;

    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */

}



