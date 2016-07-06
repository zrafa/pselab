#ifndef _DRIVERSM_H
#define _DRIVERSM_H

#include "queue.h"

Class DriverSM{
	
	public:
		DriverSM();
		void init();
		void setCola(QueueHandle_t *hc);//mmmmm
	
	private:
		volatile uint8_t *eicra;
		volatile uint8_t *eimsk;
		
}
#endif /* _DRIVERSM_H */
