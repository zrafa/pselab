
#include "spi.h"
#include "avr/io.h"

SPI::SPI(){

pines.ce = CE;
pines.cs = CS;
pines.mosi = MOSI;
pines.miso = MISO;
pines.sck = SCK;

registros_spi = (SPI_control *) SPCR_;
//registros_spi->control_register = (uint8_t) 0x4C;
// En estos registros se encuentran mapeadas las lineas MISO, MOSI, SCK. 
pSPI_struct = (SPI_struct *) DDR_B;


}

/* Configura al procesador del sistema embebido como maestro, la linea MISO se encuentra establecida como entrada */
void
SPI::SPI_MasterInit (void){

/* Set MOSI, SCK and CS or ~SS and CE as output, all others input 0010 1110 = 0x2e*/
pSPI_struct->ddr_spi |= (MOSI | SCK | CS | CE); //| CE 

/* Enable SPI, Master, set clock rate fck/16 0101 0001 = 0x51*/
registros_spi->control_register = 0x51;//(SPE |MSTR |SPR0);


}

void
SPI::SPI_MasterTransmit(uint8_t data){

/* Start transmission */
registros_spi->data_register = data;
/* Wait for transmission complete */
//while(!(((registros_spi->status_register)) & SPIF))
//	;

}

/*void
SPI::SPI_MasterTransmit(const uint8_t* buf, uint8_t len){

cs(LOW);

while(len--){
	(pSPI_struct->pSPI_Control->data_register) = *buf++;	

	while(!((pSPI_struct->pSPI_Control->status_register) & SPIF));
}

cs(HIGH);


};*/

/* La lectura de la imu se lleva a cabo en la funcion SlaveReceive(). 
uint8_t
SPI::SPI_MasterRead(void){

return registros_spi->data_register;

};*/

//CS = PB2.
//PORTB = CS
//Salida = 1.
//Entrada = 0.
//Con esta funcion hacemos transiciones LOW - HIGH y viceversa, para transmitir o recibir datos.
void
SPI::cs(int chipselect){

switch(chipselect){
	/* CS down */
	case 0:
			  pSPI_struct->SPI_port &= (0 << 2);// lo pongo a 0
			  break;

	case 1:
	/* CS up */
			  pSPI_struct->SPI_port |= CS;  // lo pongo a 1
			  break;
}

}

void
SPI::SPI_SlaveInit(void){

/* Set MISO output, all others input */
(pSPI_struct->ddr_spi) = MISO;
/* Enable SPI */
(registros_spi->control_register) = SPE;

}

//Con esta funcion obtenemos, en el maestro, el dato leido por el sensor.
uint8_t
SPI::SPI_SlaveReceive(void){

/* Wait for reception complete */
while(!((registros_spi->status_register) & SPIF))
	;

/* Return Data Register */
return (registros_spi->data_register);

}

void
SPI::MasterImuReceive(uint8_t x){


}

SPI_control *
SPI::get_registros_spi(){

return registros_spi;

}

SPI_struct *
SPI::get_pspi(){

return pSPI_struct;

}

