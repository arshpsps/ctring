main: run | builds
	@ ./builds/out

memchk: memvar = -g -O0
memchk: run | builds
	@ valgrind --leak-check=yes ./builds/out

run: ./src/main.c ./src/str.c | builds
	@ gcc -Wall -o ./builds/out ./src/main.c ./src/str.c $(memvar)

lib: ./src/str.c ./src/str.h | builds
	@ gcc -Wall -c -o ./builds/str.o ./src/str.c
	@ ar rcs ./builds/str.a ./builds/str.o
	@ echo ".a lib placed in builds/"

builds:
	mkdir -p $@
