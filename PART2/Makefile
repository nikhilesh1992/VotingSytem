CC=gcc
CFLAGS=-g

all:
	make vote-zero-tcp
	make add-voter-tcp
	make vote-tcp
	make list-candidates-tcp
	make vote-count-tcp
	make server-tcp

vote-zero-tcp: vote-zero-tcp.o
	$(CC) -o vote-zero-tcp $(CFLAGS) vote-zero-tcp.o 

add-voter-tcp: add-voter-tcp.o
	$(CC) -o add-voter-tcp $(CFLAGS) add-voter-tcp.o
	
vote-tcp: vote-tcp.o
	$(CC) -o vote-tcp $(CFLAGS) vote-tcp.o 

list-candidates-tcp: list-candidates-tcp.o
	$(CC) -o list-candidates-tcp $(CFLAGS) list-candidates-tcp.o
	
vote-count-tcp: vote-count-tcp.o
	$(CC) -o vote-count-tcp $(CFLAGS) vote-count-tcp.o 

server-tcp: server-tcp.o
	$(CC) -o server-tcp $(CFLAGS) server-tcp.o
	
vote-zero-tcp.o: vote-zero-tcp.c
	$(CC) -c vote-zero-tcp.c $(CFLAGS)

add-voter-tcp.o: add-voter-tcp.c
	$(CC) -c add-voter-tcp.c $(CFLAGS)
	
vote-tcp.o: vote-tcp.c
	$(CC) -c vote-tcp.c $(CFLAGS)

list-candidates-tcp.o: list-candidates-tcp.c
	$(CC) -c list-candidates-tcp.c $(CFLAGS)
	
vote-count-tcp.o: vote-count-tcp.c
	$(CC) -c vote-count-tcp.c $(CFLAGS)

server-tcp.o: server-tcp.c
	$(CC) -c server-tcp.c $(CFLAGS)
	
clean:
	rm -f *.o *.exe add-voter-tcp vote-count-tcp vote-tcp vote-zero-tcp list-candidates-tcp server-tcp