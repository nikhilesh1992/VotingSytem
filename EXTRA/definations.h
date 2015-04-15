#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define BUFSIZE 4096
#define ERR_SOCKET 1
#define ERR_BIND 2
#define ERR_LISTEN 3
#define ERR_ACCEPT 4
#define SA struct sockaddr
#define LISTENQ 5