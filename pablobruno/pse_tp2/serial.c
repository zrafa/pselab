#include<avr/io.h>

typedef struct
{
 uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
 uint8_t status_control_b;    /* ucsr0a USART Control and Status B */
  uint8_t status_control_c;    /* ucsr0a USART Control and Status C */
     uint8_t reserved;  /* Registro reservado */
    uint8_t baud_rate_l;  /* UBBR0L baud rate low */
     uint8_t baud_rate_h;  /* UBBR0H baud rate high */
   uint8_t data_es;  /* udr0 i/o data */
   

   
} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);


#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define RECEIVER_ENABLE 0x10
#define TRANSMITTER_ENABLE 0x08
#define CHARACTER_SIZE_0 0x20
#define CHARACTER_SIZE_1 0x40
#define READY_TO_READ 0x80
#define READY_TO_WRITE 0x20
#define PARITY_ENABLE_ODD 0x30
#define PARITY_ENABLE_EVEN 0x20
#define TWO_STOP_BITS 0x08

#define CHARACTER_SIZE_EIGHT 0x06

//Rutina de inicializacion
void serial_init() {

 //Activar el modo del USART 
 //En este caso, no es necesario, debido a que deseamos usar el modo ASINCRONICO. Para ello los bits UMSEL01 y UMSEL02 de UCSR0C (status c)
 //deben estar en 0. Por defecto estan en 0, por lo que no es necesario setearlos.

 //QUE PASA CON EL REGISTRO U2X0... el manual dice que si se usa el sincronico dejarlo en 0, sino en 1??

       //El registro UBRRn esta dividido en dos. El low posee los primeros 8 bits y el h los ultimos 4. Asi el registro es de 12 bits.
          puerto_serial ->baud_rate_l= (uint8_t) (BAUD_PRESCALE);
          puerto_serial ->baud_rate_h= (uint8_t) (BAUD_PRESCALE>>8);

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
//un bit de stop, se deja en 0 el bit USBS0, de status c.
//elijo bit de paridad EVEN, es decir 0 si la cant de unos es par y 1 si es impar
//el size del caracter sera 8 bits o 6 bits?? El frame queda de 8 incluyendo el bit de stop y de paridad... pero... esta bien?

          puerto_serial ->status_control_c= (uint8_t) (CHARACTER_SIZE_EIGHT);
   

	/* Activar la recepcion y transmicion */
        puerto_serial ->status_control_b= (uint8_t) (TRANSMITTER_ENABLE | RECEIVER_ENABLE); //(los bits 3 y 4)

}


/* enviar un byte a traves del dispositivo inicializado */
void serial_put_char (char outputChar)
{
    /* Wait until the transmitter is ready for the next character. */
  //que papel juega el bit TXC0 aca????
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

     while ( !((puerto_serial ->status_control_a )& (READY_TO_WRITE) ))
         ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
   
  puerto_serial -> data_es = outputChar;

}


char serial_get_char(void)
{

  while ( !((puerto_serial ->status_control_a )& (READY_TO_READ) ))
         ;

    return (puerto_serial->data_es) ;

}


