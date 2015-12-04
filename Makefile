CC=gcc
COPTS=-Wall -g

SRCFILES=src/prompt.c src/tokenize.c src/tokenize.h src/list.c src/list.h src/parse.c src/parse.h src/eval.c src/eval.h

melisp: $(SRCFILES)
	$(CC) $(COPTS) -o melisp src/*.c

clean:
	rm -rf *.o melisp
