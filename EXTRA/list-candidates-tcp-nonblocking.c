#include "definations.h"

int main( int argc, char *argv[] )
{
  char buf[BUFSIZE];
  int sockfd,len;
  struct sockaddr_in servaddr;
  FILE *server_request, *server_reply;
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
  
  if( (sockfd = socket(AF_INET, SOCK_STREAM, 0 )) < 0 )
    {
      perror( "Unable to open a socket" );
      exit( ERR_SOCKET );
    }
  
  bzero( &servaddr, sizeof(servaddr ));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi (argv[2]));
  if( inet_pton( AF_INET, addr, &servaddr.sin_addr ) <= 0 )
    {
      perror( "Unable to convert address to inet_pton \n" );
      exit( 99 );
    }

	if( connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0 )
    {
      perror( "Unable to connect to server" );
      exit( 100 );
    }

   len = sizeof(servaddr);
   
   strcpy (buf,"4");
   
   	write(sockfd,buf,4096);
	read(sockfd, buf, 4096);
	fputs( buf, stdout );
    close( sockfd);
	
  exit( 0 );
}
