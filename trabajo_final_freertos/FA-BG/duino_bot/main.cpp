#include "FreeRTOS.h"
#include "task.h"
#include "motor.h"
#include "led.h"
#include "spi.h"
#include "MPU9250.h"
#include "nRF24L01.h"
#include "queue.h"

#define mainLED_TASK_PRIORITY   (tskIDLE_PRIORITY)

//Almacenamos el dato extraido de la imu.
xQueueHandle buffer_imu = xQueueCreate(20, sizeof(uint8_t));

//Almacenamos el dato proveniente del tr2.
//xQueueHandle buffer_rx = xQueueCreate(20, sizeof(uint8_t));

SPI spi;

Motor motor; //definimos un objeto estatico, no se usa new

MPU9250 imu;

nRF24L01 transceptor;

Led led_bicolor((volatile unsigned char *) DDRA_BI, (volatile unsigned char *) PORTA_BI, ENCENDER_DB);
Led led_amarillo((volatile unsigned char *) DDRB, (volatile unsigned char *) PORTB, ENCENDER_DB);

static void mover_motores(void* pvParameters);

static void leer_imu(void* pvParameters);

static void imu_control(void* pvParameters);

static void rx(void* pvParameters);

static void blink_led(void* pvParameters);

int main (){

//Inicializamos el Arduino-Bot como maestro SPI.
spi.SPI_MasterInit();

xTaskHandle handle;
xTaskCreate
   (
        mover_motores,
        (const char*)"Motores",
        configMINIMAL_STACK_SIZE,
        NULL,
        mainLED_TASK_PRIORITY,
        &handle
   );

/*xTaskHandle handle;
xTaskCreate
   (
        mover_motores,
        (const char*)"Motores",
        configMINIMAL_STACK_SIZE,
        NULL,
        mainLED_TASK_PRIORITY,
        &handle
   );*/

vTaskStartScheduler();

return 0;

}


static void mover_motores(void* pvParameters){

for( ;; )
	motor.vMotor(pvParameters);

}

static void leer_imu(void* pvParameters){

spi.cs(LOW);

spi.SPI_MasterTransmit((imu.get_sensor_magnetico())->hzh);

uint8_t valor = spi.SPI_SlaveReceive();

spi.cs(HIGH);

xQueueSend(buffer_imu, &valor, (portTickType) 0);

}

static void imu_control(void* pvParameters){

uint8_t medicion;
while(!xQueueReceive(buffer_imu, &medicion, (portTickType) 10) )
	;

//Escribir en el transceptor.
//Debemos seleccionar el transceptor, porque comparte pines con la imu. Para ello podriamos usar el pin CS???. Quizas hay que hacer algo con CE???.

//Configuramos los registros del transceptor para pasarlo a modo PTX.
transceptor.Init_TX();

//Escribimos la medicion realizada por la imu en el buffer TX FIFO del transceptor.
spi.SPI_MasterTransmit(medicion);

//La transmision inicia con el pin CE en heigh.

}

static void rx_control(void* pvParameters){

//Mientras el pin IRQ este en low => esperar 

//Debemos seleccionar el transceptor, porque comparte pines con la imu. Para ello podriamos usar el pin CS???. Quizas hay que hacer algo con CE???.

spi.SPI_MasterTransmit(R_RX_PAYLOAD);

uint8_t control = spi.SPI_SlaveReceive();

switch((int)control){

// s.
case 115 : { // Detenemos los motores del robot.

		   }
// a.
case 97 : { // Avanzamos hacia adelante.
			motor.M_adelante(0, 0xFFFF);
			motor.M_adelante(1, 0xFFFF);
			break;
		  }

// r.
case 114 : { // Retrocedemos.
			 motor.M_atras(0, 0xFFFF);
			 motor.M_atras(1, 0xFFFF);
			 break;
		   }

// d.
case 100 : { //Giramos a la derecha.

		   }

// i.
case 105 : { // Giramos a la izquierda.

		   }

default : for( ;; ){
			  led_bicolor.encender();
			  led_bicolor.delay(1000);
			  led_bicolor.apagar();
		  }

}

}

static void blink_led(void* pvParameters){

led_amarillo.encender();
led_amarillo.delay(1000);
led_amarillo.apagar();

}

