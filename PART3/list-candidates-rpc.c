#include "rpc.h"

CLIENT *rpc_setup(char *host);
void list(CLIENT *clnt);

int
main(int argc, char *argv[])
{
	CLIENT *clnt;  /* client handle to server */
	char *host;    /* host */

	if (argc != 2) {
	  fprintf(stderr, "Invalid Arguments, Usage: %s <server_ip_address> \n", argv[0] );
		exit(1);
	}
	host = argv[1];
	if ((clnt = rpc_setup(host)) == 0)
		exit(1);	/* cannot connect */
	list(clnt);
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
list(CLIENT *clnt)
{
	char * *result_4;
	char *list_1_arg;

	result_4 = list_1((void*)&list_1_arg, clnt);
	if (result_4 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else
	{
		printf("%s\n", *result_4);
	}
}
