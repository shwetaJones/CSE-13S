CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

all: encode decode

encode: encode.o 
	$(CC) -o encode encode.o -lm

decode: decode.o 
	$(CC) -o decode decode.o -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c 

huffman.o: huffman.c 
	$(CC) $(CFLAGS) -c huffman.c

stack.o: stack.c 
	$(CC) $(CFLAGS) -c stack.c

code.o: code.c 
	$(CC) $(CFLAGS) -c code.c

node.o: node.c 
	$(CC) $(CFLAGS) -c node.c

clean:
	rm -f encode *.o
	rm -f decode *.o

format:
	clang-format -i -style=file *.c
