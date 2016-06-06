CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
TTY = /dev/ttyUSB0

HFLAGS = -O ihex -R .eeprom
MMCU=atmega328p
CPU_CLK = 16000000UL
CFLAGS = -Os -DF_CPU=$(CPU_CLK) -mmcu=$(MMCU)
SOURCES=new.o circbuf.o scc.o serial.o main.o

MAIN=appserial

all:$(SOURCES) link hex flash

.cpp.o:
	$(CXX) $(CFLAGS) -c -o new.o new.cpp
	$(CXX) $(CFLAGS) -c -o circbuf.o circbuf.cpp -I .
	$(CXX) $(CFLAGS) -c -o scc.o scc.cpp -I .
	$(CXX) $(CFLAGS) -c -o serial.o serial.cpp -I .
	$(CXX) $(CFLAGS) -c -o main.o main.cpp

link:
	$(CC) -mmcu=$(MMCU) $(SOURCES) -o $(MAIN).elf

hex:
	$(OBJCOPY) $(HFLAGS) $(MAIN).elf $(MAIN).hex

flash:
	avrdude -v -v -v -v -p atmega328p -c arduino -P $(TTY) -b 57600 -D -U flash:w:$(MAIN).hex:i

clean:
		-rm *.o *.hex $(MAIN).elf
