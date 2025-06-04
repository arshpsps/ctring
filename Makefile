.PHONY: all main run memchk cpp release clean builds

all: main

main: run
	@ ./builds/out

memchk: memvar = -g -O0
memchk: run
	@ valgrind --leak-check=yes ./builds/out

run: ./builds/out

./builds/out: ./src/main.c ./src/ctring.c | builds
	@ gcc -Wall -o ./builds/out ./src/main.c ./src/ctring.c $(memvar)

cpp: ./src/ctring.c ./src/ctring.h ./src/cpp.cpp liba | builds
	@ g++ -o ./builds/cppout ./src/cpp.cpp -Lbuilds -lctring
	@ LD_LIBRARY_PATH=./builds ./builds/cppout

release: liba libso ./src/ctring.h | builds
	@ tar -czvf ./builds/ctring-$(v)-linux-x86_64.tar.gz ./src/ctring.h ./builds/libctring.a ./builds/libctring.so

liba: ./builds/libctring.a

./builds/libctring.a: ./builds/ctring.o | builds
	@ ar rcs ./builds/libctring.a ./builds/ctring.o
	@ echo ".a static lib placed in builds/"

libso: ./builds/libctring.so

./builds/libctring.so: ./builds/ctring.o | builds
	@ gcc -shared -o ./builds/libctring.so ./builds/ctring.o
	@ echo ".so shared lib placed in builds/"

./builds/ctring.o: ./src/ctring.c ./src/ctring.h | builds
	@ gcc -Wall -fPIC -c -o ./builds/ctring.o ./src/ctring.c

clean: | builds
	@ rm -rdf ./builds/*

builds:
	@ mkdir -p $@
