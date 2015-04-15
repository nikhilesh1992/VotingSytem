CC=gcc
CFLAGS=-g

all:
	make vote-zero-tcp-nonblocking
	make add-voter-tcp-nonblocking
	make vote-tcp-nonblocking
	make list-candidates-tcp-nonblocking
	make vote-count-tcp-nonblocking
	make server-tcp-nonblocking

vote-zero-tcp-nonblocking: vote-zero-tcp-nonblocking.o
	$(CC) -o vote-zero-tcp-nonblocking $(CFLAGS) vote-zero-tcp-nonblocking.o 

add-voter-tcp-nonblocking: add-voter-tcp-nonblocking.o
	$(CC) -o add-voter-tcp-nonblocking $(CFLAGS) add-voter-tcp-nonblocking.o
	
vote-tcp-nonblocking: vote-tcp-nonblocking.o
	$(CC) -o vote-tcp-nonblocking $(CFLAGS) vote-tcp-nonblocking.o 

list-candidates-tcp-nonblocking: list-candidates-tcp-nonblocking.o
	$(CC) -o list-candidates-tcp-nonblocking $(CFLAGS) list-candidates-tcp-nonblocking.o
	
vote-count-tcp-nonblocking: vote-count-tcp-nonblocking.o
	$(CC) -o vote-count-tcp-nonblocking $(CFLAGS) vote-count-tcp-nonblocking.o 

server-tcp-nonblocking: server-tcp-nonblocking.o
	$(CC) -o server-tcp-nonblocking $(CFLAGS) server-tcp-nonblocking.o
	
vote-zero-tcp-nonblocking.o: vote-zero-tcp-nonblocking.c
	$(CC) -c vote-zero-tcp-nonblocking.c $(CFLAGS)

add-voter-tcp-nonblocking.o: add-voter-tcp-nonblocking.c
	$(CC) -c add-voter-tcp-nonblocking.c $(CFLAGS)
	
vote-tcp-nonblocking.o: vote-tcp-nonblocking.c
	$(CC) -c vote-tcp-nonblocking.c $(CFLAGS)

list-candidates-tcp-nonblocking.o: list-candidates-tcp-nonblocking.c
	$(CC) -c list-candidates-tcp-nonblocking.c $(CFLAGS)
	
vote-count-tcp-nonblocking.o: vote-count-tcp-nonblocking.c
	$(CC) -c vote-count-tcp-nonblocking.c $(CFLAGS)

server-tcp-nonblocking.o: server-tcp-nonblocking.c
	$(CC) -c server-tcp-nonblocking.c $(CFLAGS)
	
clean:
	rm -f *.o *.exe add-voter-tcp-nonblocking vote-count-tcp-nonblocking vote-tcp-nonblocking vote-zero-tcp-nonblocking list-candidates-tcp-nonblocking server-tcp-nonblocking

	