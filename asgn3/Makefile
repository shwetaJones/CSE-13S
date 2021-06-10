CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: sorting

sorting: sorting.o counts.o set.o stack.o queue.o quick.o shell.o bubble.o 
	$(CC) -o sorting sorting.o counts.o set.o stack.o queue.o quick.o shell.o bubble.o 

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

counts.o: counts.c
	$(CC) $(CFLAGS) -c counts.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c
