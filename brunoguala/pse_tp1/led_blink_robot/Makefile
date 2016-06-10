
#all:
#	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led_blink.o led_blink.c
#	avr-gcc -mmcu=atmega328p led_blink.o -o led_blink.elf
#	avr-objcopy -O ihex -R .eeprom led_blink.elf led_blink.hex
#   avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:led.hex:i 

robot: 
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega1284p -c -o led_blink_robot.o led_blink_robot.c

	avr-gcc -mmcu=atmega1284p led_blink_robot.o -o led_blink_robot.elf

	avr-objcopy -O ihex -R .eeprom led_blink_robot.elf led_blink_robot.hex

	./hiduploader -mmcu=atmega1284p - v -usb=0x2842,0x0001 led_blink_robot.hex

clean:
	rm led_blink_robot.elf led_blink_robot.o led_blink_robot.hex
