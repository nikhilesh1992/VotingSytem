Executing - 
Enter directory PART3
1. make clean
2. make
3. Start the server on one terminal. ( ./server-rpc )
4. Invoke various clients in any given order
	Client-1 : ./vote-zero-rpc localhost
	Client-2 : ./add-voter-rpc localhost <VoterID>
	Client-3 : ./vote-rpc localhost <Candidate Name> <VoterID>
	Client-4 : ./list-candidates-rpc localhost
	Client-5 : ./vote-count-rpc localhost <Candidate Name>

Assumptions and Limits on the input variables
1. IP Address - 127.0.0.1 or (localhost)
3. Candidate Name - Name should be less than or equal to 10 characters and no upper bound on the number of candidates Note: Names are case-sensitive
4. Voter ID - Any positive number and no upper bound on the number of voters(Eg. 1,2,3..)
Note: If any of these conditions are not met then a corresponding error message is thrown at the client side while parsing the command line data. Also entering the wrong server IP address, wrong server port number or an invalid IP address then the client times out in 60 sec.	
 
Data structures used in Implementation
1. I have used a linked list to store the data corresponding to the authorised voter. That is because voters can dynamically increase and hence there is no fixed cap on the number of voter. Therefore I have decided to use a linked list. Where every node has a integer value to store the voterID and a pointer pointing to the next node.
2. I have used a linked list to store the data corresponding to the candidates that is the number of votes and also the candidates name. I have chosen a linked list to give the flexibility of increasing the size dynamically whenever required and not restricting the size by using an array. Every node consists of a candidate name, vote count corresponding to that candidate and a pointer pointing to the next candidate.


Network Protocol & System design
In part3 I have used the Remote Procedural Call (RPC) to communicate between the client and server. In this communication protocol I have various clients that call different functions according to their requirements and all the functions implementations are consolidates in the server side. From the client side we make the appropriate function call with the corresponding arguments and then the server side receives the call, implements the function and returns back the return value to the client. All this done with the help of the client and server stub which are created using the rpcgen command. All this function calls are using UDP in their bottom line.
Also the structure that I use to send data to/from the client/server is of the form:
struct intpair {
        char candidateName[12];
        int voterID;
};
The various function that I have implemented in order to carry out the voting functionality is:
program VOTE_PROG {
        version VOTE_VERS {
                string VOTE_ZERO(void) = 1;
                string ADD_VOTER(intpair) = 2;
                string VOTE(intpair) = 3;
                string LIST(void) = 4;
                string VOTE_COUNT(intpair) = 5;
        } = 1;
The xdr that is generated from the rpcgen command is of the form:
bool_t xdr_intpair (XDR *xdrs, intpair *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->candidateName, 12,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->voterID))
		 return FALSE;
	return TRUE;
}

Function calls, Arguments and return values
1. Vote-zero -> Function : VOTE_ZERO, Arguments: NONE, Return Value: String ("TRUE" or "FALSE")
2. Add-voter -> Function : ADD_VOTER, Arguments: int Voter ID, Return Value: String ("OK" or "EXISTS" or "ERROR")
3. Vote      -> Function : VOTE, Arguments: struct intpair( which contains a character array for candidate name and an integer for voter ID), Return Value: String ("NOTAVOTER" or "NEW" or "EXISTS" or "ALREADYVOTED" or "ERROR")
4. List-Candidate -> Function : LIST, Arguments: NONE, Return Value: String ("<Candidate Names>" or "NONE"(If no candidates are present in the system))
5. Vote-Count -> Function : VOTE_COUNT, Arguments: Character array for candidates name, Return Value: String ("<Vote Count>" or "-1")

Note:
I have tested my client/server model over the network and I have observed that there is packet loss in this case which I haven't handled and when having the client/server on the same machine then there is no packet loss.

References : 
CIS-553 (Networked System)
http://stackoverflow.com/questions/20308048/socket-programming-for-multi-clients-with-select-in-c
http://www.binarytides.com/server-client-example-c-sockets-linux/
http://stackoverflow.com/questions/20019786/safe-and-portable-way-to-convert-a-char-to-uint16-t
http://www-01.ibm.com/support/knowledgecenter/ssw_ibm_i_53/rzab6/rzab6xnonblock.htm - Extra Credit
http://stackoverflow.com/questions/16328118/simple-tcp-server-with-multiple-clients-c-unix
http://www.binarytides.com/multiple-socket-connections-fdset-select-linux/
http://www.mapkreke.com/blog/2007/03/09/unix-using-select-with-multiple-sockets-in-c/
http://www.lowtek.com/sockets/select.html
http://www.cs.rutgers.edu/~pxk/rutgers/notes/rpc/step6.html
http://beej.us/guide/bgnet/output/print/bgnet_A4.pdf