CC = gcc
CXX = g++

INCLUDES = 
SOURCES = main.o timer.o new.o

CFLAGS = -Os -g -std=c++11 -I.

MAIN = tasks

all: $(SOURCES) link

clean:
	-rm *.o $(MAIN)

link: 
	$(CC) -o $(MAIN) $(SOURCES)

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
.cpp.o:
	$(CXX) -c $(CFLAGS) -fno-exceptions $(INCLUDES) $< -o $@

