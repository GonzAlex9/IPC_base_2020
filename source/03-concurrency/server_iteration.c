/*
 * Filename: server_iteration.c
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXPENDING 2    /* maximum number of pending connections on server */
#define BUFFSIZE 20
void err_sys(char *mess) { perror(mess); exit(1); }

void HandleClient(int sock) {
char 	buffer[BUFFSIZE];
int 	received = -1;
int 	contador;

for (contador=0; contador<3; contador++) {
/* new message from client */
	buffer[0]='\0';
	if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
		err_sys("error on reading message");
	}
	buffer[received]='\0';
	/* send back echo */
//	while (received > 0) {
		/* send back echo */
		if (send(sock, buffer, received, 0) != received) {
    		err_sys("error writign echo message");
		}
    	/* quedan datos por recibir */
//   	if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
//   		err_sys("error lectura addicional");
//		}
//	}
	printf("(%d) text : %s", contador, buffer);
}
close(sock);
}

int main(int argc, char *argv[]) {
int serversock, clientsock;
struct sockaddr_in echoserver, echoclient;
int 	procesFill;

if (argc != 2) {
	err_sys("USAGE: server <port>\n");
}
/* create TCP socket*/
if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
	err_sys("error socket creation");
}
/* set sockaddr_in */
memset(&echoserver, 0, sizeof(echoserver));       /* reset memory */
echoserver.sin_family = AF_INET;                  /* Internet/IP */
echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* any addr */
echoserver.sin_port = htons(atoi(argv[1]));       /* server port */
/* Bind  */
if (bind(serversock, (struct sockaddr *) &echoserver,sizeof(echoserver)) < 0) {
	err_sys("error bind");
}
/* Listen  */
if (listen(serversock, MAXPENDING) < 0) {
	err_sys("error listen");
}
/* loop */
while (1) {
	unsigned int clientlen = sizeof(echoclient);
    /* new connection request from client? */
    fprintf(stdout, "PARENT PROCESS: waiting for ACCEPT\n");
    if ((clientsock =
    	accept(serversock, (struct sockaddr *) &echoclient,&clientlen)) < 0) {
		err_sys("error accept");
	}
	if ((procesFill=fork())==-1) err_sys("problems with FORK");
	else if (procesFill>0)
	{
		//parent processº
  		close(clientsock);
    	fprintf(stdout, "PARENT: I have already forked a new child process\n");
	}
	else
	{
		//child process for the communication managing
		close(serversock);
    	fprintf(stdout, "Client: %s\n",inet_ntoa(echoclient.sin_addr));
		HandleClient(clientsock);
		err_sys("end of child process");
	}
}
}


