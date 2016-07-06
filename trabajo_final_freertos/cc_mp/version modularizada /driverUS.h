#ifndef _DRIVERUS_H
#define _DRIVERSM_H

Class DriverUS{
			
		public:
			DriverUS();
			void init();
			void setCola(QueueHandle_t *hc);
		
		private:
			volatile uint8_t *pcimsk;
			volatile uint8_t *pcicr;
			volatile uint8_t *tmr3crb;
	}
#endif
