/**********************************************************************************
**Author: Kevin Allen
**CS 372 Program 1
**Description:  Client side of a basic chat program, much of the socket setup was adapted
	from Beej's guide to network programming : https://beej.us/guide/bgnet/
***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

//function to send all bytes in the buffer, takes socket file descriptor, a buffer containing the message, and the size of the buffer
//returns number of bytes sent
int sendAll(int socket, char *mes, int len) {		//fucntion taken from Beej's guide https://beej.us/guide/bgnet/html/multi/advanced.html
	int totalSent = 0;
	int bytesRemain = len;
	int sent;

	while (totalSent < len) {
		sent = send(socket, mes + totalSent, bytesRemain, 0);
		if (sent == -1) {
			return -1;
		}
		totalSent += sent;
		bytesRemain -= sent;
	}
	return totalSent;
}

//function to recieve messages, takes socket file descriptor, a buffer for teh message and the size of the buffer
//returns number of bytes recieved
int recieveMess(int socket, char *buffer, int size) {		
	int bytes;
	memset(buffer, '\0', size);				//clear out buffer
	if ((bytes = recv(socket, buffer, size, 0)) == 0) {		//recieve message
		printf("recieve failed");
		return -1;
	}
	printf("%s", buffer);
	return bytes;
}

//function to connect to server, takes the host name, port number, and a pointer to the struct addrinfo to hold the connection infromation
//returns a socket file descriptor, socket setup was adapted from Beej's guide to network programming : https://beej.us/guide/bgnet/
int connectTo(char* host, char* port, struct addrinfo *gc) {
	struct addrinfo hints;
	struct addrinfo *res;
	int sockFD;

	//setup hints struct
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(host, port, &hints, &res) != 0) {
		fprintf(stderr, "getaddrinfo failed\n");
		return 1;
	}

	for (gc = res; gc != NULL; gc = gc->ai_next) {
		if ((sockFD = socket(gc->ai_family, gc->ai_socktype, gc->ai_protocol)) == -1) {
			fprintf(stderr, "socket error");
			continue;
		}
		if (connect(sockFD, gc->ai_addr, gc->ai_addrlen) == -1) {
			fprintf(stderr, "connection error");
			continue;
		}
		break;
	}
	freeaddrinfo(res);
	return sockFD;
}

int main(int argc, char *argv[]) {
	//struct addrinfo hints;
	struct addrinfo *gc;
	int socketFD;
	char handle[12];		//12 to accomodate null terminator and > 
	char message[501];
	char buffer[513];

	socketFD = connectTo(argv[1], argv[2], gc);		//make the connection

	//get user handle
	printf("Please enter a user handle up to 10 characters\n");
	fgets(handle, sizeof(handle), stdin);
	char* ptr;
	if ((ptr = strchr(handle, '\n')) != NULL) {		//get rid of newline, and add > to handle for prompt
		*ptr = '>';
	}
	//send and recieve messages
	while (1) {
		printf("%s", handle);

		memset(message, '\0', sizeof(message));	//clear message
		fgets(message, sizeof(message), stdin);
		if ((ptr = strchr(message, '\n')) != NULL) {		//get rid of newline
			*ptr = '\0';
		}

		if (strcmp(message, "\\quit")==0) {		//check if client wishes to end connection
			break;
		}
	
		memset(buffer, '\0', sizeof(buffer));  //clear buffer
		strcpy(buffer, handle);					//add handle to message
		strcat(buffer, message);				// complete message
		
		if (sendAll(socketFD, buffer, sizeof(buffer)) == -1) {
			printf("send failed\n");
		}

		recieveMess(socketFD, buffer, sizeof(buffer));

	}

	close(socketFD);
	
	return 0;
}