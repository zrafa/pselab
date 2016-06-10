all:
	# Compilar cada archivo fuente
	g++ -c -o circbuf.o circbuf.cpp
	g++ -c -o main.o main.c
	# Vincular
	g++ circbuf.o main.o -o main.elf

clean:
	rm *.o *.elf
