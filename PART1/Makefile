CC=gcc
CFLAGS=-g

all:
	make vote-zero-udp
	make add-voter-udp
	make vote-udp
	make list-candidates-udp
	make vote-count-udp
	make server-udp

vote-zero-udp: vote-zero-udp.o
	$(CC) -o vote-zero-udp $(CFLAGS) vote-zero-udp.o 

add-voter-udp: add-voter-udp.o
	$(CC) -o add-voter-udp $(CFLAGS) add-voter-udp.o
	
vote-udp: vote-udp.o
	$(CC) -o vote-udp $(CFLAGS) vote-udp.o 

list-candidates-udp: list-candidates-udp.o
	$(CC) -o list-candidates-udp $(CFLAGS) list-candidates-udp.o
	
vote-count-udp: vote-count-udp.o
	$(CC) -o vote-count-udp $(CFLAGS) vote-count-udp.o 

server-udp: server-udp.o
	$(CC) -o server-udp $(CFLAGS) server-udp.o
	
vote-zero-udp.o: vote-zero-udp.c
	$(CC) -c vote-zero-udp.c $(CFLAGS)

add-voter-udp.o: add-voter-udp.c
	$(CC) -c add-voter-udp.c $(CFLAGS)
	
vote-udp.o: vote-udp.c
	$(CC) -c vote-udp.c $(CFLAGS)

list-candidates-udp.o: list-candidates-udp.c
	$(CC) -c list-candidates-udp.c $(CFLAGS)
	
vote-count-udp.o: vote-count-udp.c
	$(CC) -c vote-count-udp.c $(CFLAGS)

server-udp.o: server-udp.c
	$(CC) -c server-udp.c $(CFLAGS)
	
clean:
	rm -f *.o *.exe add-voter-udp vote-count-udp vote-udp vote-zero-udp list-candidates-udp server-udp