
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 4096

//Queue definitions
struct QueueNode
{
	char buf[4096];
	struct QueueNode *next;
}*head,*tail;

typedef struct QueueNode queueNode;

int isEmpty();
void enqueue(char *buf);
char * dequeue();

//Voter Id Link list definitions
struct voter
{
	int voterId;
	int hasVoted;
	struct voter *next;
}*headV,*tailV;

typedef struct voter voterNode;

void addVoter(int Id);
int isListEmpty();
void clearList();
voterNode* searchVoter(int id);
int hasVotedOrNot(int id);

//Candidate link list definitions
struct CandidateNode
{
	char candidateName[12];
	int numVotes;
	struct CandidateNode *next;
}*headC,*tailC;

typedef struct CandidateNode candidateNode;

void addCandidate(char *);
int searchCandidate(char *);
void voteForCandidate(char *);
int voteCount(char *);
char* listOfCandidates(char *);
void clearCandidates();

//Controller and its definitions
struct BufferIncoming
{
	char tokens[10];
};
typedef struct BufferIncoming BufferIncoming;
char bufSend[BUFSIZE];
char voteCounts[100];

