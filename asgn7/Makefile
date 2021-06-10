CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic -ggdb

all:banhammer

banhammer: banhammer.o parser.o speck.o node.o ll.o ht.o bv.o bf.o
	$(CC) $(CFLAGS) -o banhammer banhammer.o parser.o speck.o node.o ll.o ht.o bv.o bf.o -lm

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *.c
	clang-format -i -style=file *.h
