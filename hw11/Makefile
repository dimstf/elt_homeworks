.PHONY: all clean test

all: bin/main
bin/main: build/libcalc.so
	gcc src/main.c -o bin/main -L. build/libcalc.so
build/libcalc.so: build/interface.o build/calc.o
	gcc -shared build/calc.o build/interface.o -o build/libcalc.so
build/calc.o: src/calc.c
	gcc -c src/calc.c -fPIC -o build/calc.o
build/interface.o: src/interface.c
	gcc -c src/interface.c -fPIC -o build/interface.o

clean:
	rm build/interface.o build/calc.o bin/main build/libcalc.so

test: bin/main build/libcalc.so
	LD_LIBRARY_PATH=$PWD/build ./bin/main
