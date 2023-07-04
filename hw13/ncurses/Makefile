.PHONY: all clean test

all: bin/main
bin/main:
	gcc -w src/main.c -o bin/main -lncurses

clean:
	rm bin/main

test: bin/main
	./bin/main
