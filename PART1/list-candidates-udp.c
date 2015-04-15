#include "definations.h"

void handle(int sig) {
    printf("Unable to connect to server : Time out\n");
	exit(0);
}

int main( int argc, char *argv[] )
{
  char buf[BUFSIZE];
  int sockfd, recvlen, len;
  struct sockaddr_in servaddr,clientaddr;
  char addr[50];
  extern int close();

	if( argc != 3 )
	{
	  fprintf(stderr, "Invalid Arguments, Usage: %s <server_ip_address> <server_port>\n", argv[0] );
	  exit ( 1 );
	}
	else
	{
		if(strcmp(argv[1],"localhost") == 0)
		{
			strcpy(addr, "127.0.0.1");
		}
		else
		{
			strcpy(addr, argv[1]);
		}
	}
	
	if( atoi (argv[2]) < 1024 || atoi (argv[2]) > 65536)
	{
		fprintf(stderr, "Invalid port number, Port Number lies between [ 1024 , 65536 ]");
		exit ( 1 );
	}
  
  if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0 )) < 0 )
    {
      perror( "Unable to open a socket" );
      exit( ERR_SOCKET );
    }
  
  bzero( &servaddr, sizeof(servaddr ));
  bzero( &clientaddr, sizeof(clientaddr ));
  
  servaddr.sin_family = AF_INET;
  clientaddr.sin_family = AF_INET;
  //AF_INET is  is the address family that is used for the socket you're creating (in this case an Internet Protocol address). 
  
  servaddr.sin_port = htons(atoi (argv[2]));
  clientaddr.sin_port = htons( 11636 );
  //htons() function converts the unsigned short integer hostshort from host byte order to network byte order.

  clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  /* convert address, e.g., 127.0.0.1, to the right format, convert IPv4 and IPv6 addresses from text to binary form, int inet_pton(int af, const char *src, void *dst); */
  
  if( inet_pton( AF_INET, addr, &servaddr.sin_addr ) <= 0 )
    {
      perror( "Unable to convert address to inet_pton \n" );
      exit( 99 );
    }

	if (bind(sockfd, (SA *)&clientaddr, sizeof(clientaddr)) < 0) {
		perror("Binding failed");
		return 0;
	}

   len = sizeof(servaddr);
   signal(SIGALRM, handle);
   
   strcpy (buf,"4");
   
    if( sendto(sockfd, buf, BUFSIZE, 0, (SA *)&servaddr, sizeof(servaddr)) < 0 )
	{
	  perror( "Sending message to server failed" );
	}
   alarm(60);
   strcpy (buf,"");
   if( (recvlen=recvfrom(sockfd,buf,BUFSIZE,0,(SA *) &servaddr,&len)) < 0 )
	{
	  perror( "Response from the server failed");
	}
	
	fputs( buf, stdout );

    close( sockfd); 

  exit( 0 );
}
