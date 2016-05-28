#all:
#	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o new.o new.cpp
#	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o circbuf.o circbuf.cpp -I .
#	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o scc.o scc.cpp -I .
#	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o serial.o serial.cpp -I .
#	avr-g++ -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.cpp
#	avr-gcc -mmcu=atmega328p new.o circbuf.o scc.o serial.o main.o -o appserial.elf
#	avr-objcopy -O ihex -R .eeprom appserial.elf appserial.hex
	# avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:appserial.hex:i 

#clean:
#	rm *.o *.hex *.elf



CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
TTY = /dev/ttyUSB0

INCLUDES = -I .
SOURCES = new.o circbuf.o scc.o serial.o main.o

MMCU = atmega328p
CPU_CLK = 16000000UL
CFLAGS = -Os -DF_CPU=$(CPU_CLK) -mmcu=$(MMCU)
HFLAGS = -O ihex -R .eeprom

MAIN = main

all: $(SOURCES) link hex

clean:
	-rm *.o *.hex $(MAIN)

link: 
	$(CC) -mmcu=$(MMCU) -o $(MAIN) $(SOURCES)

hex:
	$(OBJCOPY) $(HFLAGS) $(MAIN) $(MAIN).hex

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

flash:
	avrdude -F -V -c arduino -p ATMEGA328P -P $(TTY) -b 57600 -U flash:w:$(MAIN)

.cpp.o:
	$(CXX) -c $(CFLAGS) -fno-exceptions $(INCLUDES) $< -o $@

