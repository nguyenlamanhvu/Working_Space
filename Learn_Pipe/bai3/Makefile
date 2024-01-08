# Pipe

CC := gcc

%.o : %.c
	$(CC) -c $< -o $@

all: send.o receive.o
	$(CC) -o send send.o
	$(CC) -o receive receive.o

clean:
	rm -rf  send receive myfifo *.o