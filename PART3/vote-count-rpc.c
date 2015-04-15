#include "rpc.h"

CLIENT *rpc_setup(char *host);
void vote_count(CLIENT *clnt,char* buf);

int
main(int argc, char *argv[])
{
	CLIENT *clnt;  /* client handle to server */
	char *host;    /* host */
	int a, b;

	if (argc != 3) {
	  fprintf(stderr, "Invalid Arguments, Usage: %s <server_ip_address> <candidate_name>\n", argv[0] );
		exit(1);
	}
	if( strlen(argv[2]) > 10 )
	{
		fprintf(stderr, "Candidate name should be less than 10 characters");
		exit ( 1 );
	}
	host = argv[1];
	if ((clnt = rpc_setup(host)) == 0)
		exit(1);	/* cannot connect */
	vote_count(clnt,argv[2]);
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
vote_count(CLIENT *clnt,char* buf)
{
	char * *result_5;
	intpair  vote_count_1_arg;

	vote_count_1_arg.voterID = 0;
	strcpy(vote_count_1_arg.candidateName,buf);
	result_5 = vote_count_1(&vote_count_1_arg, clnt);
	if (result_5 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	{
		printf("%s\n", *result_5);
	}
}
