CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
TTY = /dev/ttyUSB0

INCLUDES = -I .
SOURCES = test.o gpio.o timer.o delay.o

MMCU = atmega328p
CPU_CLK = 16000000UL
CFLAGS = -Os -DF_CPU=$(CPU_CLK) -mmcu=$(MMCU)
HFLAGS = -O ihex -R .eeprom

MAIN = test

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
	avrdude -F -V -c arduino -p ATMEGA328P -P $(TTY) -b 115200 -U flash:w:$(MAIN)

.cpp.o:
	$(CXX) -c $(CFLAGS) -fno-exceptions $(INCLUDES) $< -o $@
