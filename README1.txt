Executing - 
Enter directory PART1
1. make clean
2. make
3. Start the server on one terminal. ( ./server-udp )
4. Invoke various clients in any given order
	Client-1 : ./vote-zero-udp localhost 11632
	Client-2 : ./add-voter-udp localhost 11632 <VoterID>
	Client-3 : ./vote-udp localhost 11632 <Candidate Name> <VoterID>
	Client-4 : ./list-candidates-udp localhost 11632
	Client-5 : ./vote-count-udp localhost 11632 <Candidate Name>

Assumptions and Limits on the input variables
1. IP Address - 127.0.0.1 or (localhost)
2. Port Number - 1024-65536
3. Candidate Name - Name should be less than or equal to 10 characters and no upper bound on the number of candidates Note: Names are case-sensitive
4. Voter ID - Any positive number and no upper bound on the number of voters(Eg. 1,2,3..)
Note: If any of these conditions are not met then a corresponding error message is thrown at the client side while parsing the command line data. Also entering the wrong server IP address, wrong server port number or an invalid IP address then the client times out in 60 sec.	

Port Numbers
1. Server - 11632
2. Client-1(vote-zero-udp) - 11633
3. Client-2(add-voter-udp) - 11634
4. Client-3(vote-udp) - 11635
5. Client-4(list-candidates-udp) - 11636
6. Client-5(vote-count-udp) - 11637
 
Data structures used in Implementation
1. I have used a linked list to store the data corresponding to the authorised voter. That is because voters can dynamically increase and hence there is no fixed cap on the number of voter. Therefore I have decided to use a linked list. Where every node has a integer value to store the voterID and a pointer pointing to the next node.
2. I have used a linked list to store the data corresponding to the candidates that is the number of votes and also the candidates name. I have chosen a linked list to give the flexibility of increasing the size dynamically whenever required and not restricting the size by using an array. Every node consists of a candidate name, vote count corresponding to that candidate and a pointer pointing to the next candidate.

Note:
I have tested my client/server model over the network and I have observed that there is packet loss in this case which I haven't handled and when having the client/server on the same machine then there is no packet loss.

Network Protocol & System design
In part1 I have used the User datagram protocol (UDP) to communicate between the client and server. In this communication there is no virtual pipeline that is created between the client and server. Hence while creating the socket on the client side we bind the given socket to the IP address of the client,port number of client and then attach a message datagram to it and send it across to the server. I used sento and recvfrom system calls to send and receive data from server side ( While sending the sending/receiving data we specify the server IP address and port number in a structure called sockaddr_in). Whereas on the server side I have assigned a specific IP address (127.0.0.1) and a port number (11632) to the socket using the bind function. Also enabled the server to listen to multiple clients using the listen function and it blocks on a function call named accept until and unless there is an incoming request from any of the clients. In this case if the server crashes then all the data that has been stored till then will be lost. 
Client Side(Function Calls) : Create Socket with type SOCK_DGRAM(socket), Bind Socket(bind), Send message to server(sendto), Receive message from server(recvfrom) 
Server Side(Function Calls) : Create Socket with type SOCK_DGRAM(socket), Bind Socket(bind), Listen to client request(listen), Accept client connections(accept), Receive message from client(recvfrom), Send message to client(sendto) 

Message Payloads
1. Vote-zero -> Sending datagram : "1" , Receiving datagram : "TRUE" or "FALSE"
2. Add-voter -> Sending datagram : "2 <VoterID>" , Receiving datagram : "OK" or "EXISTS" or "ERROR"
3. Vote      -> Sending datagram : "3 <Candidate Name> <VoterID>" , Receiving datagram : "NOTAVOTER" or "NEW" or "EXISTS" or "ALREADYVOTED" or "ERROR"
4. List-Candidate -> Sending datagram : "4" Receiving datagram : "<Candidate Names>" or "NONE"
5. Vote-Count -> Sending datagram : "5 <Candidate Name>" , Receiving datagram : "<Vote Count>" or "-1"

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
http://stackoverflow.com/questions/1784136/simple-signals-c-programming-and-alarm-function