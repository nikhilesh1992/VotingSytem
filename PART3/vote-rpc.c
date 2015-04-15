#include "rpc.h"

CLIENT *rpc_setup(char *host);
void vote(CLIENT *clnt,char* buf,int ID);

int
main(int argc, char *argv[])
{
	CLIENT *clnt;  /* client handle to server */
	char *host;    /* host */

	if (argc != 4) {
		fprintf(stderr, "Invalid Arguments, Usage: %s <server_ip_address> <candidate_name> <voter_id>\n", argv[0] );
		exit(1);
	}
	if( atoi (argv[3]) <= 0 )
	{
		fprintf(stderr, "Voter Id must be a positive number greater than 0");
		exit ( 1 );
	}
	
	if( strlen(argv[2]) > 10 )
	{
		fprintf(stderr, "Candidate name should be less than 10 characters");
		exit ( 1 );
	}
	host = argv[1];
	if ((clnt = rpc_setup(host)) == 0)
		exit(1);	/* cannot connect */
	vote(clnt,argv[2],atoi(argv[3]));
	clnt_destroy(clnt);
	exit(0);
}

CLIENT *
rpc_setup(char *host)
{
	CLIENT *clnt = clnt_create(host, VOTE_PROG, VOTE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		return 0;
	}
	return clnt;
}

void
vote(CLIENT *clnt,char* buf,int ID)
{
	char * *result_3;
	intpair  vote_1_arg;

	vote_1_arg.voterID = ID;
	strcpy(vote_1_arg.candidateName,buf);
	result_3 = vote_1(&vote_1_arg, clnt);
	if (result_3 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else 
	{
		printf("%s\n", *result_3);
	}
}
