.PHONY: all clean test

all: bin/main
bin/main:
	gcc -w src/main.c -o bin/main

clean:
	rm bin/main bin/test.txt

test: bin/main
	./bin/main
