CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: lrc

lrc: lrc.o
	$(CC) $(CFLAGS) -o lrc lrc.o

lrc.o: lrc.c
	$(CC) $(CFLAGS) -c lrc.c

clean:
	rm -f lrc lrc.o
