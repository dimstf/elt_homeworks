.PHONY: all clean test

all: bin/main2
bin/main2: build/main2.o build/interface.o build/phbook.o
	gcc -Wall build/main2.o build/interface.o build/phbook.o -o bin/main2
build/interface.o: src/interface.c
	gcc -Wall -c src/interface.c -o build/interface.o
build/phbook.o: src/phbook.c
	gcc -Wall -c src/phbook.c -o build/phbook.o
build/main2.o: src/main2.c
	gcc -Wall -c src/main2.c -o build/main2.o

clean: 
	rm build/main2.o build/interface.o build/phbook.o bin/main2
	
test: bin/main2
	./bin/main2
