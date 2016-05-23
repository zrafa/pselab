#include<avr/io.h>


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
uint8_t status_control_a;	/* ucsr0a USART Control and Status A */
uint8_t status_control_b;	/* ucsr0b USART Control and Status B */
uint8_t status_control_c;	/* ucsr0c USART Control and Status C */
uint8_t _reserved;			/* espacio sin utilizar */
uint8_t baud_rate_l;		/* ubrr0l baud rate low */;
uint8_t baud_rate_h;		/* ubrr0h baud rate high */
uint8_t data_es; 			/* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 9600
#define F_CPU 16000000UL 
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)


void serial_init() {
/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	/* Activar la recepcion y transmicion */

puerto_serial->baud_rate_h= (uint8_t) (BAUD_PRESCALE>>8);
puerto_serial->baud_rate_l= (uint8_t) (BAUD_PRESCALE);
//paridad desabilitada , 1 bit de stop y 8 bit de longitud y habilito transmisión y recepción
puerto_serial->status_control_b = (uint8_t) 0x18;

puerto_serial->status_control_c = (uint8_t) 0x06;

}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */
  /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    // while ( /* completar con E/S programada */ )
    //     ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
/*if((puerto_serial->status_control_a & (1<<5))==0x20){
puerto_serial->data_es = outputChar;
  
	}*/
while(!(puerto_serial->status_control_a & (1<<5)))
puerto_serial->data_es = outputChar;
}


char serial_get_char(void)
{
char lectura;
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;

    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
/*if((puerto_serial->status_control_a & (1<<8))==0x80){
return puerto_serial->data_es;
}*/
while(!(puerto_serial->status_control_a & (0x80)))//if((puerto_serial->status_control_a & (0x80))); en que cambia? porque lo repite mil veces al valor leido?
lectura=puerto_serial->data_es;
return lectura;

}



