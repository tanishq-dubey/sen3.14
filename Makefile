HEADERS = cpu.h

default: nes

nes: main.o
	gcc -o nes main.o

main.o: main.c
	gcc -c main.c

clean:
	rm nes *.o
