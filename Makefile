CC = gcc 
CFLAGS = -Wall -std=c99 -g

spellcheck: spellcheck.o wordlist.o document.o

spellcheck.o: spellcheck.c wordlist.h document.h
wordlist.o: wordlist.c 
document.o: document.c wordlist.h

clean:
	rm -f spellcheck.o wordlist.o document.o
	rm -f spellcheck
	rm -f output.*
