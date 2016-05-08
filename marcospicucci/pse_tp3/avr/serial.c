#include <avr/io.h>

#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define UDREn 0x20
#define TXCn 0x40
#define RXCn 0x80


#define LED_MASK (0x20)
#define REG_DIR_DAT (0x24)
#define REG_ESTADO_HIGH_LOW (0x25) 


typedef struct
{
    uint8_t status_control_a;    // ucsr0a USART Control and Status A  (0xC0)
    uint8_t status_control_b;   // ucsr0b (0xC1)
    uint8_t status_control_c;	// ucsr0c (0xC2)
    uint8_t reserved;           // (0xC3)
    uint8_t baud_rate_l;        // ubrr0l (0xC4)
    uint8_t baud_rate_h;	// ubrr0h (0xC5)
    uint8_t data_es;    // udr0 i/o data (0xC6)

} volatile uart_t;

uart_t *puerto_serial = (uart_t *) (0xc0); //puntero a la estructura de los registros del periferico

//************Para Led******************

uint8_t volatile *rdd = (uint8_t volatile *)REG_DIR_DAT ;
uint8_t volatile *rehl = (uint8_t volatile *)REG_ESTADO_HIGH_LOW ;

void inicializaLed(){
	*rdd = (*rdd) | (LED_MASK) ;
}

void cambiaLed(){
	*rehl = (*rehl) ^ (LED_MASK) ;
}

void delay_ms(int ms){
	long volatile ciclos = ms * 9000;
	while(ciclos != 0){
		ciclos --;	
	}
}


//*****************************
void serial_init() {
	//asincronico (7 en 0, 6 en 0), USBSn(bit 3) en 0 para stop de 1bit, frame 8bits (1 y 2 en 1), paridad par (5 en 1, 4 en 0, lo saqué no hay paridad, 0 y 0)
	puerto_serial->status_control_c = 0b00000110;
	puerto_serial->baud_rate_l = BAUD_PRESCALE; 
	puerto_serial->baud_rate_h = BAUD_PRESCALE>>8;
	puerto_serial->status_control_b = 0b00011000;// Activar la recepcion y transmision(RXENn,TXENn)
}

//podria controlar (pero no) bit 2 del s_c_a,UPEn,en 1 si hay errorde paridad, dice q siempre setear a 0 cuando escriba en el s_c_a no controlo eso ..

/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{    
	
    while(((puerto_serial->status_control_a) & UDREn) == 0){	
		//el buffer de transmision solo puede escribirse cuando el bit 5 (udren) del s_c_a esta en 1, que indica buffer vacio y listo para ser escrito   	
    }  
    // no salia nunca del while con ~ adelante y sin el ==0 ..
     
    
    puerto_serial->data_es = outputChar; // envio dato por puerto serial (lo escribo en el reg de datos de e/s)
  
    while(((puerto_serial->status_control_a) & TXCn) == 0){ //bit 6 (txcn) del s_c_a esta en 1 cuando el frame del transmit shift register se "shifteo" y no hay datos nuevos actualmente en el buffer de transmision (udrn)
	}	
	/*inicializaLed();
	cambiaLed(); llega aca(transmitio??), prende el led.. */
}

char serial_get_char(void)
{
	inicializaLed();
	cambiaLed();
	while(((puerto_serial->status_control_a) & RXCn) == 0){// bit 7 en 0 si buffer d recepcion vacio, ie, no tiene ningun dato que no haya sido leido)	
	
	}// en 1 si hay datos sin leer en el buf de recep (llegó)

   
   return puerto_serial->data_es;
}


