
//#ifndef _CONF_H
//#define _CONF_H

/* Pines de SPI para placa Arduino Pro-mini atmega328p */ 
#define CE         (1<<1)  //PB1
#define CS         (1<<2)  //PB2
#define MOSI       (1<<3)  //PB3
#define MISO       (1<<4)  //PB4
#define SCK        (1<<5)  //PB5


#define DDR_B      (0x24) /* DDR B para el led rojo*/
#define PUERTO_B   (0x25) /* direccion de PUERTO B donde esta el led rojo*/


/* Pines de SPI para placa Arduino-bot atmega1284p */
#define CS_A       (1<<4) //PB4
#define MOSI_A     (1<<5) //PB5
#define MISO_A     (1<<6) //PB6
#define SCK_A      (1<<7) //PB7 


/* SPI Control Register */
#define SPCR_   0x4C //– SPI Control Register 
#define spie  (1<<7)// SPI Interrupt Enable
#define spe   (1<<6)// – SPE: SPI Enable
#define DORD  (1<<5)// – DORD: Data Order
#define mstr  (1<<4)//– MSTR: Master/Slave Select
#define CPOL  (1<<3)//  CPOL: Clock Polarity
#define CPHA  (1<<2)//CPHA: Clock Phase	

#define spr1  (1<<1)//Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0
#define spr0  (1<<0)//Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0

/* SPI Status Register */
#define SPSR    0x4D  //– SPI Status Register
#define SPIF   (1<<7)// SPI Interrupt Flag
#define WCOL   (1<<6)// Write COLlision Flag
#define spi2x  (1<<5)// Double SPI Speed Bit


/* SPI Data Register */
#define SPDR    0x4E // SPI Data Register

//#endif
