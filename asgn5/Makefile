CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

all: encode decode

encode: encode.o hamming.o bm.o bv.o
	$(CC) -o encode encode.o hamming.o bm.o bv.o -lm

decode: decode.o hamming.o bm.o bv.o
	$(CC) -o decode decode.o hamming.o bm.o bv.o -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c 

hamming.o: hamming.c 
	$(CC) $(CFLAGS) -c hamming.c

clean:
	rm -f encode *.o
	rm -f decode *.o

format:
	clang-format -i -style=file *.c
