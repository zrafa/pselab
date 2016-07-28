#include "FreeRTOS.h"
#include "queue.h"


#ifndef _DRIVERSM_H
#define _DRIVERSM_H

class DriverSM{
	
	public:
		DriverSM();
		void init();
	
	private:
		volatile uint8_t *eicra;
		volatile uint8_t *eimsk;
		
};
#endif /* _DRIVERSM_H */
