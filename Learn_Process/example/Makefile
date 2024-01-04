.PHONY: all clean

CC:= gcc
%.o: %.c
	$(CC) -c $< -o $@

all: main.o
	$(CC) -o app.exe $<

clean:
	rm -rf *.exe *.o
