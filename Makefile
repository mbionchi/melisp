CC=gcc
COPTS=-Wall -Wextra

melisp:
	$(CC) $(COPTS) -o melisp src/*.c

clean:
	rm -rf *.o melisp
