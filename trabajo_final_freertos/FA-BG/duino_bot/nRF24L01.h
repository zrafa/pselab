
#ifndef _RF24_H
#define _RF24_H

#include <avr/io.h>

#define PIPES         0xA0

#define HEIGH         1
#define LOW           0

#define CONF          0x00
#define PRIM_RX       (1<<0)

#define EN_AA         0x01
#define ENAA_P5       (1<<5)
#define ENAA_P4       (1<<4)
#define ENAA_P3       (1<<3)
#define ENAA_P2       (1<<2)
#define ENAA_P1       (1<<1)
#define ENAA_P0       (1<<0)
#define ENAA_ALL      0x3F

#define EN_RXADDR     0x02
#define EN_ALL        0x3F

#define SETUP_RETR    0x04
#define ARD_250US     0x00
#define ARD_500US     0x10
#define ARD_750US     0x20

#define RF            0x06
#define RF_DR_LOW     (1<<5)
#define MBPS1         (0<<3)
#define MBPS2         (1<<3)

#define STATUS        0x07

#define TX_ADDR       0x10

//Direcciones asociadas a canales de datos.
#define RX_ADDR_P0 0x7878787878
#define RX_ADDR_P1 0xB3B4B5B6F1
#define RX_ADDR_P2 0xB3B4B5B6CD
#define RX_ADDR_P3 0xB3B4B5B6A3
#define RX_ADDR_P4 0xB3B4B5B60F
#define RX_ADDR_P5 0xB3B4B5B605

typedef struct {

uint8_t *rx_addr_p0;
uint8_t *rx_addr_p1;
uint8_t *rx_addr_p2;
uint8_t *rx_addr_p3;
uint8_t *rx_addr_p4;
uint8_t *rx_addr_p5;

} data_pipes;

class nRF24L01 {

public :
		   nRF24L01();

		   void Init_TX();
		   void Init_RX();

private :
		   uint8_t 	  *config;
		   uint8_t    *en_aa;
		   uint8_t    *en_rxaddr;
		   uint8_t    *setup_retr;
		   uint8_t 	  *rf_setup;
		   uint8_t 	  *status;
		   uint8_t 	  *tx_addr;
   		   data_pipes *pipes;

};

#endif
