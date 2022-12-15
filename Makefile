CC=gcc -std=c99

smallsh.out: main.o inarg.o gettok.o procline.o userin.o
	$(CC) -o smallsh.out main.o inarg.o gettok.o procline.o userin.o

main.o: main.c smallsh.h
	$(CC) -o main.o -c main.c
inarg.o: smallsh.h inarg.c
	$(CC) -o inarg.o -c inarg.c
gettok.o: smallsh.h gettok.c
	$(CC) -o gettok.o -c gettok.c
procline.o: smallsh.h procline.c
	$(CC) -o procline.o -c procline.c
userin.o: smallsh.h userin.c
	$(CC) -o userin.o -c userin.c

clean:
	rm main.o inarg.o gettok.o procline.o userin.o

