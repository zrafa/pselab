#include <avr/io.h>


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */		//Tienen que estar en el mismo orden de la memoria!
    uint8_t status_control_b;    /* ucsr0a USART Control and Status B */		//    (Ver datasheet pag 612)
    uint8_t status_control_c;    /* ucsr0a USART Control and Status C */
	uint8_t reserved;			//Este tiene que estar para que el baudrate y siguientes esten bien ubicados en la memoria
	uint8_t baudrate_l;			 /* UBRRLn USART Baud Rate Registers */
	uint8_t baudrate_h;			 /* UBRRLn USART Baud Rate Registers */
    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);


#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define UDREn 0x20		//Bit de buffer vacio en status_control_a
#define TXCn  0x40		//Bit de transmision terminada en status_control_a
#define RXCn  0x80		//Bit de recepcion completa en status_control_a

void serial_init() 
{
	//Como la estructura no es una variable sino un puntero, para acceder a los bytes dentro de la estructura se usa el "->" en lugar de punto.
	puerto_serial->status_control_c=0b00000110;	/* Configurar un frame de 8bits, sin bit de paridad y bit de stop */

	puerto_serial->baudrate_l= BAUD_PRESCALE;
	puerto_serial->baudrate_h=(BAUD_PRESCALE >> 8);		/* Configurar los registros High y Low con BAUD_PRESCALE */
	
	puerto_serial->status_control_b=0b00011000;	/* Activar la recepcion y transmision */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */
}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    while((puerto_serial->status_control_a & UDREn)==0);/* Wait until the transmitter is ready for the next character. */
    puerto_serial->data_es=outputChar;    /* Send the character via the serial port. */
	while((puerto_serial->status_control_a & TXCn)==0);	/*Wait until the transmitter flushed all the data */

}


char serial_get_char(void)
{
    while((puerto_serial->status_control_a & RXCn)==0);/* Wait for the next character to arrive. */
	return puerto_serial->data_es;  /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
}



