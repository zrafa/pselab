CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy

INCLUDES = 
SOURCES = main.o timer.o new.o circbuf.o scc.o led.o serial.o

MMCU = atmega328p
CPU_CLK = 16000000UL
CFLAGS = -Os -DF_CPU=$(CPU_CLK) -mmcu=$(MMCU) -std=c++11 -I.
HFLAGS = -O ihex -R .eeprom


MAIN = tasks

all: $(SOURCES) link hex

clean:
	-rm *.o *.hex $(MAIN)

link: 
	$(CXX) -mmcu=$(MMCU) -o $(MAIN) $(SOURCES)

hex:
	$(OBJCOPY) $(HFLAGS) $(MAIN) $(MAIN).hex
	 avrdude -v -v -v -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:tasks.hex:i 

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
.cpp.o:
	$(CXX) -c $(CFLAGS) $(INCLUDES) $< -o $@

