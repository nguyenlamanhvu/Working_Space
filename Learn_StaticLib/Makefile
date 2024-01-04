.PHONY: all static link clean

all:
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c src/hello.c -o obj/hello.o -I./inc
	gcc -c src/anhvu.c -o obj/anhvu.o -I./inc

static:
	ar rcs lib/static/libhello.a obj/hello.o obj/anhvu.o

link:
	gcc obj/main.o -Llib/static -lhello -o bin/app

clean:
	rm -rf obj/* bin/*