#all:
	# Compilar cada archivo fuente
#	g++ -c -o new.o new.cpp
#	g++ -c -o circbuf.o circbuf.cpp -I .
#	g++ -c -o scc.o scc.cpp -I .
#	g++ -c -o serial.o serial.cpp -I .
#	g++ -c -o main.o main.cpp -I .
#	g++ -c -o test.o test.cpp -I .
	# Vincular
#	g++ new.o circbuf.o scc.o serial.o main.o -o main.elf
#	g++ new.o circbuf.o scc.o serial.o test.o -o test.elf

#clean:
#	rm *.o *.elf

CXX = g++


INCLUDES = -I .
SOURCES = new.o circbuf.o scc.o serial.o main.o
TESTE = new.o circbuf.o scc.o serial.o test.o
MAIN = main
MEIN = test

all:	$(SOURCES) link $(TESTE) linc

clean:
	-rm *.o *.elf

link: 
	$(CXX) $(SOURCES) -o $(MAIN).elf

linc:
	$(CXX) $(TESTE) -o $(MEIN).elf	

.cpp.o:
	$(CXX) -c -fno-exceptions $(INCLUDES) $< -o $@


