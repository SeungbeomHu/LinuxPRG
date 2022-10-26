CC=gcc

smallsh.out: main.o inarg.o gettok.o procline.o runcommand.o userin.o
	$(CC) -o smallsh.out main.o inarg.o gettok.o procline.o runcommand.o userin.o

main.o: main.c smallsh.h
	$(CC) -o main.o -c main.c
inarg.o: smallsh.h inarg.c
	$(CC) -o inarg.o -c inarg.c
gettok.o: smallsh.h gettok.c
	$(CC) -o gettok.o -c gettok.c
procline.o: smallsh.h procline.c
	$(CC) -o procline.o -c procline.c
runcommand.o: smallsh.h runcommand.c
	$(CC) -o runcommand.o -c runcommand.c
userin.o: smallsh.h userin.c
	$(CC) -o userin.o -c userin.c

clean:
	rm main.o inarg.o gettok.o procline.o runcommand.o userin.o

