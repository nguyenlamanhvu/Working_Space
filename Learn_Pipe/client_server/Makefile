# Pipe

CC := gcc

%.o : %.c
	$(CC) -c $< -o $@

all: client.o server.o
	$(CC) -o client client.o
	$(CC) -o server server.o

clean:
	rm -rf  server client fifo_client fifo_server *.o