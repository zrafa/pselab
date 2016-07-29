
#ifndef _MPU_H
#define _MPU_H

#include <avr/io.h>

#define INIT_GYRO     0x43
#define INIT_ACCEL    0x3B
#define INIT_TEMP     0x41
#define INIT_MG       0x43 //read = 1.

typedef struct {

//Eje x.
uint8_t gyro_xout_h;
uint8_t gyro_xout_l;

//Eje y.
uint8_t gyro_yout_h;
uint8_t gyro_yout_l;

//Eje z.
uint8_t gyro_zout_h;
uint8_t gyro_zout_l;

} giroscopo;

typedef struct {

uint8_t accel_xout_h;
uint8_t accel_xout_l;

uint8_t accel_yout_h;
uint8_t accel_yout_l;

uint8_t accel_zout_h;
uint8_t accel_zout_l;

} acelerometro;

typedef struct {

uint8_t temp_out_h;
uint8_t temp_out_l;

} sensor_temperatura;

//La lectura de la IMU devuelve un numero decimal de 16 bits.
typedef struct {

uint8_t hxl;
uint8_t hxh;

uint8_t hyl;
uint8_t hyh;

uint8_t hzl;
uint8_t hzh;

} magnetometro;

class MPU9250 {

public :
		 MPU9250();

		 giroscopo           *get_gyro();
		 acelerometro        *get_accel();
   		 sensor_temperatura  *get_sensor_temp();
		 magnetometro        *get_sensor_magnetico();

private :
		 giroscopo           *gyro;
		 acelerometro        *accel;
		 sensor_temperatura  *sensor_temp;
		 magnetometro        *sensor_magnetico;
		 
};

#endif
