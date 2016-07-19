
#ifndef _SPI_H
#define _SPI_H

#include "spi_config.h"
#include <stdint.h>

#define LOW   0
#define HIGH  1
/* Definimos una enumeracion*/
/*typedef enum {

LOW = 0,
HIGH

} boolean;*/

//Comandos SPI para leer o escribir los buffer FIFO del transceptor.
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0

//typedef enum { LOW, HIGH } bool;

typedef struct {

uint8_t ce; 
uint8_t cs;     //chip select
uint8_t mosi;
uint8_t miso;
uint8_t sck;

} SPI_pines;  //Tipo de dato para los pines.

typedef struct {

uint8_t *control_register; //SPCR 0x4C
uint8_t *status_register; //SPSR 0x4D
uint8_t *data_register; //SPDR 0x4E

} SPI_control;  //Tipo de datos para los registros de control.

//Registros asociados a SPI, donde estan mapeados los pines MOSI, MISO, SCK etc.
typedef struct{

//SPI_pines pines; 			//pines del SPI
uint8_t * DDR_SPI;			//dirección de configuración de pines del SPI, 0x24
uint8_t * pSPI_port;  		//puerto del SPI,   0x25
//SPI_Control * pSPI_Control; //Registros de control del SPI.

} SPI_struct;  

class SPI {

	public  : 
			  //Constructor
			  SPI();

			  void SPI_MasterInit (void);
			  void SPI_MasterTransmit(uint8_t Data);
			  //void SPI_MasterTransmit(const uint8_t* buf, uint8_t len);
			  //uint8_t SPI_MasterRead(void);
			  void cs (int chipselect);

			  void SPI_SlaveInit(void);
			  //void SPI_SlaveTransmit(unsigned char Data);
			  //void SPI_SlaveTransmit(const uint8_t* buf, uint8_t len);
			  uint8_t SPI_SlaveReceive(void);
			  void MasterImuReceive(uint8_t x);
			  
	private :
			  //Registros del PORTB asociados al SPI.
			  SPI_struct *pSPI_struct; 

			  //Registros para configurar SPI.
			  SPI_control *registros_spi; 

			  SPI_pines *pines; 

};

#endif
