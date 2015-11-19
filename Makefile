CC=gcc
COPTS=-Wall

SRCFILES=src/prompt.c src/tokenize.c src/tokenize.h

melisp: $(SRCFILES)
	$(CC) $(COPTS) -o melisp src/*.c

clean:
	rm -rf *.o melisp
