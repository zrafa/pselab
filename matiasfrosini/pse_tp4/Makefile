all:
	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o new.o new.cpp
	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o circbuf.o circbuf.cpp -I .
	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o scc.o scc.cpp -I .
	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o serial.o serial.cpp -I .
	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.cpp
	avr-gcc -mmcu=atmega328p new.o circbuf.o scc.o serial.o main.o -o appserial.elf
	avr-objcopy -O ihex -R .eeprom appserial.elf appserial.hex
	 avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:appserial.hex:i 

clean:
	rm *.o *.hex *.elf
