main: src/main.c | builds
	@ gcc -o builds/out src/main.c

builds:
	@ mkdir builds
