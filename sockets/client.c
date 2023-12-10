#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"

void check(int status, char* fn){
	if(status == -1){
		printf("Error calling fuction %s()\n", fn);
		exit(status);
	}	
}

int main(void){
	int sockfd;
	int status;
	ssize_t communication_status;
	char buffer[SOCKET_BUFFER_LEN];
	struct sockaddr_in server_addr;
	socklen_t server_addrlen = sizeof(server_addr);

	// create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	check(sockfd, "socket");

	// configure the server infos
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SOCKET_PORT);
	inet_pton(AF_INET, SOCKET_IP, &server_addr.sin_addr);


	// connect to server
	status = connect(sockfd, (struct sockaddr*) &server_addr, server_addrlen);
	check(status, "connect");
	printf("Socket(client):: Connected to server %s:%d \n", SOCKET_IP, SOCKET_PORT);

	// receive on-connection message
	communication_status = recv(sockfd, buffer, SOCKET_BUFFER_LEN, 0);	
	check(communication_status, "recv");
	printf("Server says: << %s >>\n", buffer);

	// cleanup
	close(sockfd);
	return 0;
}
