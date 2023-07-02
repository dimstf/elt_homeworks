.PHONY: all clean test

all: bin/main
bin/main: build/libadd.so build/libsub.so build/libmul.so build/libdiv.so
	gcc src/main.c src/interface.c -o bin/main -ldl

build/libadd.so: build/add.o
	gcc -shared build/add.o -o build/libadd.so
build/add.o: src/add.c
	gcc -c src/add.c -fPIC -o build/add.o

build/libsub.so: build/sub.o
	gcc -shared build/sub.o -o build/libsub.so
build/sub.o: src/sub.c
	gcc -c src/sub.c -fPIC -o build/sub.o

build/libmul.so: build/mul.o
	gcc -shared build/mul.o -o build/libmul.so
build/mul.o: src/mul.c
	gcc -c src/mul.c -fPIC -o build/mul.o

build/libdiv.so: build/div.o
	gcc -shared build/div.o -o build/libdiv.so
build/div.o: src/div.c
	gcc -c src/div.c -fPIC -o build/div.o

clean:
	rm build/add.o build/sub.o build/mul.o build/div.o bin/main build/libadd.so build/libsub.so build/libmul.so build/libdiv.so

test: bin/main build/libadd.so build/libsub.so build/libmul.so build/libdiv.so
	./bin/main
