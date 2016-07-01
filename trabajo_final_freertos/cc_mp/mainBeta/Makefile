CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
TTY = /dev/ttyUSB0

INCLUDES = -I. -I../FreeRTOS/Source/portable/GCC/ATMega1284p -I../FreeRTOS/Source/include
 
SOURCES =	../FreeRTOS/Source/list.o \
			../FreeRTOS/Source/queue.o \
			../FreeRTOS/Source/tasks.o \
			../FreeRTOS/Source/portable/MemMang/heap_1.o \
			../FreeRTOS/Source/portable/GCC/ATMega1284p/port.o \
			led.o \
			motor.o \
			$(MAIN).o

MMCU = atmega1284p
CPU_CLK = 16000000UL
CFLAGS = -Os -DF_CPU=$(CPU_CLK) -mmcu=$(MMCU) 
HFLAGS = -O ihex -R .eeprom

MAIN = mainBeta

all: $(SOURCES) link hex

clean:
	-rm *.o *.hex $(MAIN) \
		../FreeRTOS/Source/*.o \
		../FreeRTOS/Source/portable/MemMang/heap_1.o \
		../FreeRTOS/Source/portable/GCC/ATMega1284p/port.o 

link: 
	$(CC) -mmcu=$(MMCU) -o $(MAIN) $(SOURCES)

hex:
	$(OBJCOPY) $(HFLAGS) $(MAIN) $(MAIN).hex

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

.cpp.o:
	$(CXX) -c $(CFLAGS) $(INCLUDES) -fno-exceptions $< -o $@

flash:
	avrdude -F -V -c arduino -p ATMEGA1284P -P $(TTY) -b 115200 -U flash:w:$(MAIN)
	



