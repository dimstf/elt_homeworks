#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5

int main()
{
	int Mainsock, Clientsock, length; 
	struct sockaddr_in serverAddr;
	char message[BUFFER_SIZE]; 

	if((Mainsock =socket(AF_INET, SOCK_STREAM,0))<0)
	{
		perror("Socket error. Exit."); 
		exit(1);
	}
	
	bzero((char *) &serverAddr, sizeof(serverAddr)); 
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	serverAddr.sin_port=0;

	if(bind(Mainsock,(struct sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		perror("Bind error. Exit.");
		exit(1);
	}
	
	length=sizeof(serverAddr);
	if(getsockname(Mainsock,(struct sockaddr*)&serverAddr, &length))
	{
		perror("Getsockname error. Exit."); 
		exit(1);
	}
	printf("Server port - % d\n",ntohs(serverAddr.sin_port));
	listen(Mainsock, 3) ;
	int msgLenght;

	if((Clientsock=accept(Mainsock,0,0)) < 0)
	{
		perror("Accept error. Exit.");
		exit(1);
	}

	bzero(message,sizeof(message));
		
	if((msgLenght = recv(Clientsock, message, BUFFER_SIZE, 0))<0)
	{
		perror("Recieve error. Exit.");
		exit(1);
	}
	printf("Recieved Message:  %s\n",message);
		
	if(send(Clientsock, message, strlen(message),0)<0)
	{
		perror("Send error. Exit."); 
		exit(1);
	}

	close(Clientsock);
	close(Mainsock);
	
	return 0;
}