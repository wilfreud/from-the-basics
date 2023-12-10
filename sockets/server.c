#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "socket.h"
#include <unistd.h>
#include <string.h>

void check(int status, char* fn){
	if(status == -1){
		printf("Failed executing function: %s()\n", fn);
		exit(status);
	}
}

int main(void){
	int sockfd, acceptfd;
	char buffer[SOCKET_BUFFER_LEN] = SERVER_MESSAGE;
	int status;
	ssize_t communication_status;
	struct sockaddr_in addr, client_addr;
	socklen_t addrlen = sizeof(addr);
	socklen_t client_addrlen = sizeof(client_addr);

	// create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	check(sockfd, "socket");

	// bind
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SOCKET_PORT);
	inet_pton(AF_INET, SOCKET_IP, &addr.sin_addr);
	status = bind(sockfd, (struct sockaddr*) &addr, addrlen);
	check(status, "bind");

	printf("Socket:: Running on %s:%d \n", SOCKET_IP, SOCKET_PORT);

	// listen
	status = listen(sockfd, SERVER_MAX_CONN);
	check(status, "listen");
	
	// accept
	acceptfd = accept(sockfd, (struct sockaddr*) &addr, (socklen_t*) &addrlen);
	check(acceptfd, "accept");

	// try to get client's IP
	status = getpeername(acceptfd, (struct sockaddr*) &client_addr, &client_addrlen);		
	check(status, "getpeername");
	
	printf("Socket:: Incoming request from: %s\n", inet_ntoa(client_addr.sin_addr));
	
	// send default message
	communication_status = send(acceptfd, buffer, SOCKET_BUFFER_LEN, 0);
	check(communication_status, "send");


	//cleanup
	printf("Closing server...\n");
	close(acceptfd);
	close(sockfd);
	return 0;



}
