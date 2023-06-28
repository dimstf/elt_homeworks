.PHONY: all clean test

all: bin/main
bin/main: build/main.o build/libcalc.a
	gcc -Wall build/main.o -o bin/main -L. build/libcalc.a
build/libcalc.a: build/interface.o build/calc.o
	ar rc build/libcalc.a build/calc.o build/interface.o
build/main.o: src/main.c
	gcc -Wall -c src/main.c -o build/main.o
build/calc.o: src/calc.c
	gcc -Wall -c src/calc.c -o build/calc.o
build/interface.o: src/interface.c
	gcc -Wall -c src/interface.c -o build/interface.o

clean:
	rm build/main.o build/interface.o build/calc.o bin/main build/libcalc.a

test: bin/main
	./bin/main
