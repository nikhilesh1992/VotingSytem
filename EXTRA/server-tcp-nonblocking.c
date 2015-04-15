#include "definations.h"
#include "functionDef.h"

int main( argc, argv, env )
	int argc;
	char *argv[], *env[];
{
	int server_fd,connection_fd,max_clients = 5,client_socket[5],sd,max_sd,new_socket,i,activity;
	socklen_t len;
	struct sockaddr_in cliaddr;
	char buf[BUFSIZE];
	extern int close();
	head = NULL,tail = NULL, headV = NULL, tailV = NULL, headC = NULL, tailC = NULL;
	server_fd = create_service();
	fd_set readfds;
	for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
	while(1)
	{
		FD_ZERO(&readfds);
  
        //add master socket to set
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;
		for (i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            sd = client_socket[i];
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
    
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("There was an error in selectin gone of the sockets\n");
        }
          
        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(server_fd, &readfds)) 
        {
			len = sizeof( cliaddr );
            if ((new_socket = accept(server_fd, (SA *) &cliaddr, &len))<0)
            {
                perror("Error in accepting a connection");
                exit(ERR_ACCEPT);
            }
			printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(cliaddr.sin_addr) , ntohs(cliaddr.sin_port));
			serviceLayer(new_socket);
			
            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) 
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }
	}
}

void serviceLayer( int fileDes )
{
	char bufSend[BUFSIZE];
	char buf[BUFSIZE];

	read(fileDes, buf, 4096);
	strcpy(bufSend,controller(buf));
	strcat (bufSend,"\n");
	write(fileDes,bufSend,4096);
	strcpy(bufSend,"");
	return;
}
      
int create_service()
{
  int listenfd;
  struct sockaddr_in servaddr;
  int opt = 1;

  listenfd = socket(AF_INET, SOCK_STREAM, 0 );
  if( listenfd < 0 )
    {
      perror( "Failed creating socket for server" );
      exit( ERR_SOCKET );
    }
	if( setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("Setsockopt error");
        exit(EXIT_FAILURE);
    }
  
  bzero( &servaddr, sizeof(servaddr) );
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
  servaddr.sin_port = htons( 11632 );
  printf("Server staring on port : 11632\n");
  if( bind( listenfd, (SA *) &servaddr, sizeof(servaddr) ) < 0 )
  {
    perror( "Failed binding the socket with server address");
    exit( ERR_BIND );
  }

  if( listen( listenfd, LISTENQ ) < 0 )
    {
      perror( "Error in listening on the socket" );
      exit( ERR_LISTEN );
    }
  return( listenfd );
}

char* controller(char* bufIncoming)
{
	//Splitting the incoming string to parse the message
	BufferIncoming bufferIncoming[3];
	int index = 0;
	char* token = strtok(bufIncoming, " ");
	while (token) 
	{
		strcpy((bufferIncoming[index].tokens),token);
		token = strtok(NULL, " ");
		index++;
	}

	if(strcmp((bufferIncoming[0].tokens),"1") == 0)
	{
		clearList();
		clearCandidates();
		if(headV==NULL && tailV==NULL && headC==NULL && tailC==NULL)
			return "TRUE";
		else	
			return "FALSE";
	}
	else if(strcmp((bufferIncoming[0].tokens),"2") == 0)
	{
		int VoterId = atoi(bufferIncoming[1].tokens);
		voterNode* Voter = searchVoter(VoterId);
		if( Voter != NULL )
		{
			return "EXISTS";
		}
		else if( Voter == NULL)
		{
			addVoter(VoterId);
			return "OK";
		}
		else
			return "ERROR";
	}
	else if(strcmp((bufferIncoming[0].tokens),"3") == 0)
	{
		int VoterId = atoi(bufferIncoming[2].tokens);
		char tempCandidate[12];
		strcpy(tempCandidate,(bufferIncoming[1].tokens));
		voterNode* Voter = searchVoter(VoterId);
		if( Voter == NULL )
		{
			return "NOTAVOTER";
		}
		else if( Voter != NULL)
		{
			if((Voter->hasVoted)==1)
				return "ALREADYVOTED";
			else
			{
				if((searchCandidate(tempCandidate))==1)
				{
					voteForCandidate(tempCandidate);
					Voter->hasVoted = 1;
					return "EXISTS";
				}
				else if((searchCandidate(tempCandidate))==0)
				{
					addCandidate(tempCandidate);
					voteForCandidate(tempCandidate);
					Voter->hasVoted = 1;
					return "NEW";
				}
				else
					return "ERROR";
			}	
		}
		else
			return "ERROR";
	}
	else if(strcmp((bufferIncoming[0].tokens),"4") == 0)
	{
		strcpy(bufSend,listOfCandidates(bufSend));
		if( strcmp(bufSend,"")==0)
			return "NONE";
		else
			return (bufSend);
	}
	else if(strcmp((bufferIncoming[0].tokens),"5") == 0)
	{
		char tempCandidate[12];
		strcpy(tempCandidate,(bufferIncoming[1].tokens));
		if(searchCandidate(tempCandidate))
		{
			int votes = voteCount(tempCandidate);
			sprintf(voteCounts, "%d", votes);
			return voteCounts;
		}
		else
		{
			return "-1";
		}
	}
	else
		return "ERROR";
}

int isEmpty()
{
	if( head==NULL && tail==NULL )
		return 1;
	else
		return 0;
}

void enqueue(char *buffer)
{
	queueNode *addNode=NULL;
	addNode = (queueNode *)malloc(1*sizeof(queueNode));
	stpcpy(addNode -> buf,buffer);
	addNode -> next = NULL;
	if( head==NULL && tail==NULL )
	{
		head = addNode;
		tail = addNode;
	}
	else
	{
		tail -> next = addNode;
		tail = addNode;
	}
}

char * dequeue()
{
	queueNode *temp;
	char *buffer;
	if( head==NULL && tail==NULL )
	{
		printf("No client requesting pending in the queue\n");
		return NULL;
	}
	else
	{
		if( head == tail )
		{
			temp = head;
			stpcpy(buffer,temp -> buf);
			head = NULL;
			tail = NULL;
			temp -> next = NULL;
			free(temp);
			return buffer;
		}
		temp = head;
		stpcpy(buffer,temp -> buf);
		temp = temp -> next;
		free(head);
		head = temp;
		return buffer;
	}
}

int isListEmpty()
{
	if(headV == NULL && tailV == NULL)
		return 1;
	else
		return 0;
}

void addVoter(int Id)
{
	voterNode *addNode;
	addNode = (voterNode *)malloc(1*sizeof(voterNode));
	addNode -> voterId = Id;
	addNode -> hasVoted = 0;
	addNode -> next = NULL;
	if( headV == NULL && tailV == NULL)
	{
		headV = addNode;
		tailV = addNode;
	}
	else
	{
		tailV -> next = addNode;
		tailV = addNode;
	}
}

// If voter exists in the list it returns the complete node or else NULL
voterNode* searchVoter(int id)
{
	voterNode *temp;
	temp = headV;
	while(temp != NULL )
	{
		if( temp -> voterId == id )
		{
			return temp;
		}
		temp = temp -> next;
	}
return NULL;
}

// If a given voter has already voted then returns 1 or else 0	
int hasVotedOrNot(int id)
{
	voterNode *temp;
	temp = headV;
	while(temp != NULL )
	{
		if( temp -> voterId == id && temp -> hasVoted == 1 )
		{
			return 1;
		}
		temp = temp -> next;
	}
return 0;
}

//Clears the complete list of voters
void clearList()
{
	voterNode *temp;
	temp = headV;
	if( headV!=NULL && tailV!=NULL)
	{
		while ( temp -> next != NULL )
		{
			temp = headV;
			temp = temp -> next;
			free(headV);
			headV = temp;
		}
		free(temp);
		headV = NULL;
		tailV = NULL;
	}
}

void addCandidate(char *bufC)
{
	candidateNode *addNode;
	addNode = (candidateNode *)malloc(1*sizeof(candidateNode));
	strcpy(addNode->candidateName,bufC);
	addNode -> numVotes = 0;
	addNode -> next = NULL;
	if( headC == NULL && tailC == NULL)
	{
		headC = addNode;
		tailC = addNode;
	}
	else
	{
		tailC -> next = addNode;
		tailC = addNode;
	}
}

// If candidate already exists in the list it returns 1 or else returns 0
int searchCandidate(char *bufC)
{
	candidateNode *temp;
	temp = headC;
	while(temp != NULL )
	{
		if( strcmp(temp->candidateName,bufC) == 0)
		{
			return 1;
		}
		temp = temp -> next;
	}
return 0;
}

//Increments the vote count for a specified candidate based on it name
void voteForCandidate(char *bufC)
{
	candidateNode *temp;
	temp = headC;
	while(temp != NULL )
	{
		if( strcmp(temp->candidateName,bufC) == 0)
		{
			(temp -> numVotes)++;
			break;
		}
		temp = temp -> next;
	}
} 

//Gives the vote count for a given candidate name
int voteCount(char *bufC)
{
	candidateNode *temp;
	temp = headC;
	while(temp != NULL )
	{
		if( strcmp(temp->candidateName,bufC) == 0)
		{
			return (temp->numVotes);
		}
		temp = temp -> next;
	}
return -1;
} 

//Returns a list of candidates with non-zero votes
char* listOfCandidates(char *bufC)
{
	strcpy(bufC,"");
	candidateNode *temp;
	temp = headC;
	int flag=0;
	while(temp != NULL )
	{
		if((flag==0) && (temp->numVotes > 0))
		{
			strcpy(bufC,temp->candidateName);
			//strcat(bufC,",");
			flag = 1;
		}
		else if((flag==1) && (temp->numVotes > 0))
		{
			strcat(bufC,",");
			strcat(bufC,temp->candidateName);
		}

		temp = temp -> next;
	}
	return bufC;
}

//Clears the complete list of candidates
void clearCandidates()
{
	candidateNode *temp;
	temp = headC;
	if( headC!=NULL && tailC!=NULL)
	{
		while ( temp -> next != NULL )
		{
			temp = headC;
			temp = temp -> next;
			free(headC);
			headC = temp;
		}
		free(temp);
		headC = NULL;
		tailC = NULL;
	}
}
