
#include "MPU9250.h"

MPU9250::MPU9250(){

//Inicializamos las estructuras asociadas a cada elto. de medicion.

gyro=(giroscopo *) INIT_GYRO;

accel=(acelerometro *) INIT_ACCEL;

sensor_temp=(sensor_temperatura *) INIT_TEMP;

sensor_magnetico=(magnetometro *) INIT_MG;
sensor_magnetico->hzh= (uint8_t) 0x88;

}

giroscopo*
MPU9250::get_gyro(){

return gyro;

}

acelerometro*
MPU9250::get_accel(){

return accel;

}

sensor_temperatura*
MPU9250::get_sensor_temp(){

return sensor_temp;

}

magnetometro*
MPU9250::get_sensor_magnetico(){

return sensor_magnetico;

}
