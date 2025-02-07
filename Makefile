main: run | builds
	@ ./builds/out

memchk: memvar = -g -O0
memchk: run | builds
	@ valgrind --leak-check=yes ./builds/out

run: ./src/main.c ./src/str.c | builds
	@ gcc -o ./builds/out ./src/main.c ./src/str.c $(memvar)

builds:
	mkdir -p $@
