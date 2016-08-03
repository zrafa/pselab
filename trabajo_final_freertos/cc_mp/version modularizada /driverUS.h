#include "FreeRTOS.h"
#include "queue.h"

#ifndef _DRIVERUS_H
#define _DRIVERSM_H

class DriverUS{
			
		public:
			DriverUS();
			void init();
			float calculaDistancia();
		
		private:
			volatile uint8_t *pcimsk;
			volatile uint8_t *pcicr;
			volatile uint8_t *tmr3crb;
			volatile uint8_t *tifr3;
			volatile uint8_t *timsk3;
};

#endif
