CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic 

all: tsp

tsp: tsp.o
	$(CC) -o tsp tsp.o

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f tsp *.o

format: 
	clang-format -i -style=file *.c
