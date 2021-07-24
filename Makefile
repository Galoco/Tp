CC := gcc
CFLAGS := -Wall -pedantic -std=c99 -c -g
LFLAGS := -lm -lSDL2

all: peggle

main.o: main.c graficador.h lista.h poligono.h config.h 
	$(CC) $(CFLAGS) main.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) lista.c

graficador.o: graficador.c graficador.h
	$(CC) $(CFLAGS) graficador.c

poligono.o: poligono.c poligono.h 
	$(CC) $(CFLAGS) poligono.c

fisica.o: fisica.c fisica.h
	$(CC) $(CFLAGS) fisica.c


obstaculos.o: obstaculos.c obstaculos.h 
	$(CC) $(CFLAGS) obstaculos.c

pelotita.o: pelotita.c pelotita.h
	$(CC) $(CFLAGS) pelotita.c

peggle: main.o  lista.o graficador.o poligono.o fisica.o  obstaculos.o pelotita.o 
	$(CC) $^ -o peggle $(LFLAGS)

clean:
	rm *.o
