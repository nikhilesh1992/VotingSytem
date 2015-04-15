#include "rpc.h"

CLIENT *rpc_setup(char *host);
void add_voter(CLIENT *clnt,int ID);

int
main(int argc, char *argv[])
{
	CLIENT *clnt;  /* client handle to server */
	char *host;    /* host */

	if (argc != 3) {
		fprintf(stderr, "Invalid Arguments, Usage: %s <server_ip_address> <voter_id>\n", argv[0] );
		exit(1);
	}
	if( atoi (argv[2]) <= 0 )
	{
		fprintf(stderr, "Voter Id must be a positive number greater than 0");
		exit ( 1 );
	}
	host = argv[1];
	if ((clnt = rpc_setup(host)) == 0)
		exit(1);	/* cannot connect */
	add_voter(clnt,atoi(argv[2]));
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
add_voter(CLIENT *clnt,int ID)
{
	char * *result_2;
	intpair  add_voter_1_arg;

	add_voter_1_arg.voterID = ID;
	strcpy(add_voter_1_arg.candidateName,"");
	result_2 = add_voter_1(&add_voter_1_arg, clnt);
	if (result_2 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	} else {
		printf("%s\n", *result_2);
	}
}
