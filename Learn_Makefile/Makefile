.PHONY: tong hieu run clean

CC := gcc
INC_FILE := ./inc/hieu.h
INC_FILE += ./inc/tong.h

%.o: $(INC_FILE)
	$(CC) -c src/tong.c -o obj/tong.o -I./inc	
	$(CC) -c src/hieu.c -o obj/hieu.o -I./inc
	$(CC) -c main.c -o obj/main.o -I./inc

tong: obj/tong.o obj/main.o
	$(CC) -o bin/app.exe obj/tong.o obj/main.o

hieu: obj/hieu.o obj/main.o
	$(CC) -o bin/app.exe obj/hieu.o obj/main.o

run:
	./bin/app.exe

clean:
	rm ./obj/*.o
	rm ./bin/*.exe
