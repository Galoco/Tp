CC := gcc
CFLAGS := -Wall -pedantic -std=c99 -c -g
LFLAGS := -lm -lSDL2

all: peggle


main.o: main.c lista.h fisica.h config.h obstaculos.h pelotita.h
	$(CC) $(CFLAGS) main.c

lecturas.o: lecturas.c lecturas.h
	$(CC) $(CFLAGS) lecturas.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) lista.c

poligono.o: poligono.c poligono.h 
	$(CC) $(CFLAGS) poligono.c

fisica.o: fisica.c fisica.h
	$(CC) $(CFLAGS) fisica.c

obstaculos.o: obstaculos.c obstaculos.h 
	$(CC) $(CFLAGS) obstaculos.c

pelotita.o: pelotita.c pelotita.h
	$(CC) $(CFLAGS) pelotita.c

peggle: main.o lecturas.o lista.o  poligono.o fisica.o  obstaculos.o pelotita.o 
	$(CC) $^ -o peggle $(LFLAGS)

clean:
	rm *.o

