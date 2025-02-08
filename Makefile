main: run | builds
	@ ./builds/out

memchk: memvar = -g -O0
memchk: run | builds
	@ valgrind --leak-check=yes ./builds/out

run: ./src/main.c ./src/ctring.c | builds
	@ gcc -Wall -o ./builds/out ./src/main.c ./src/ctring.c $(memvar)

liba: ./src/ctring.c ./src/ctring.h | builds
	@ gcc -Wall -c -o ./builds/ctring.o ./src/ctring.c
	@ ar rcs ./builds/ctring.a ./builds/ctring.o
	@ echo ".a static lib placed in builds/"

libso: ./src/ctring.c ./src/ctring.h | builds
	@ gcc -Wall -c -fPIC -o ./builds/ctring.o ./src/ctring.c
	@ gcc -shared -o ./builds/ctring.so ./builds/ctring.o
	@ echo ".so shared lib placed in builds/"

clean: | builds
	rm -rdf ./builds/*

builds:
	mkdir -p $@
