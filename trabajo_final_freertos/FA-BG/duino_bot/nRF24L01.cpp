
#include <nRF24L01.h>

nRF24L01::nRF24L01(){

config=(uint8_t *) CONF;

en_aa=(uint8_t *) EN_AA;

en_rxaddr=(uint8_t *) EN_RXADDR;

setup_retr=(uint8_t *) SETUP_RETR;

rf_setup=(uint8_t *) RF;

status=(uint8_t *) STATUS;

tx_addr=(uint8_t *) TX_ADDR;

pipes=(data_pipes *) PIPES;

}

void
nRF24L01::Init_TX(){     //Configuracion para el PTX.

//Establecemos el bit PRIM_RX, del registro config, en low. Para que el transceptor pase a modo PTX.
*config |= ~PRIM_RX;

//Guardamos la direccion del nodo receptor. Usamos el canal de datos 0.
*tx_addr=RX_ADDR_P0;

//Guardamos la direccion de recepcion para el canal de datos 0.
*(pipes->rx_addr_p0)=RX_ADDR_P0;

//Activamos el auto-reconocimiento (pipe 0) para que el radio pueda pasar a modo RX y esperar por un paquete ACK.
*en_aa=ENAA_P0;

//Configuramos parametros adecuados para la retransmision, cuando no se recibe un paquete ACK por parte del receptor.
*setup_retr |= ARD_250US;

}

void
nRF24L01::Init_RX(){     //Configuracion para el PRX.

//Establecemos el bit PRIM_RX, del registro config, en heigh. Para que el transceptor ingrese en modo PRX.
*config |= PRIM_RX;

//Activamos todos los canales de datos.
*en_rxaddr= EN_ALL;

//Activamos el auto-reconocimiento para todos los canales de datos.
*en_aa= ENAA_ALL;

//Guardamos la direccion del nodo receptor. Usamos el canal de datos 0.
*tx_addr=RX_ADDR_P0;

//Guardamos la direccion de recepcion para el canal de datos 0.
*(pipes->rx_addr_p0)=RX_ADDR_P0;

}
