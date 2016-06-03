#ifndef _LED_H
#define _LED_H

#define LED_ROJO  (0x20) /* 0b00100000 */
#define DDR_B     (0x24) /* DDR B para el led rojo*/
#define PUERTO_B  (0x25) /* direccion de PUERTO B donde esta el led rojo*/

#define DDR_D     (0x2A) 
#define PUERTO_D  (0x2B)
#define LED_pin9  (1<<5)
/* Number of decrement-and-test cycles. */
#define CYCLES_PER_MS (9000)




class Led
{
public:
	void ledToggle();
	void ledInit();
	void led_ON ();
	void led_OFF();
	void delay_ms(int milliseconds);
	Led (unsigned char * DDR_dir,unsigned char * Port_dir,unsigned char Port_pin);
private:
volatile unsigned char * DDR_X;   /* direccion de DDRX */
volatile unsigned char * PUERTO_X; /* direccion de PUERTO X*/
volatile unsigned char led_mask;           /* máscara del led*/

};



#endif /* _LED_H */
