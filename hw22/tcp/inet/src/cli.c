#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 5

int main(int argc, char* argv[ ])
{ 
	int sock;
	struct sockaddr_in serverAddr;
	struct hostent *hp;

/* Входные аргументы: 0 - имя_программы,   1 - имя_хоста,  
2 - порт,  3 - сообщение */

	if(argc<4){
		printf("Too few arguments. Exit.\n"); 
		exit(1) ;
	}
	if((sock=socket(AF_INET,SOCK_STREAM, 0))<0){
		perror("Socket error. Exit."); 
		exit(1);
	}
	bzero((char *)&serverAddr,sizeof(serverAddr)); 
	serverAddr.sin_family=AF_INET; 
	hp=gethostbyname(argv[1]);
	bcopy(hp->h_addr,&serverAddr.sin_addr, hp->h_length);
	serverAddr.sin_port=htons(atoi(argv[2]) );

	if(connect(sock,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){ 
		perror("Connect error. Exit.");
		exit(1);
	}

	int n=3;
	/*argv3 в число*/
	int i=atoi(argv[3]);
	
	if(send(sock, argv[3], strlen(argv[3]),0)<0)
	{
		perror("Send error. Exit."); 
		exit(1);
	}
	
	char message[BUFFER_SIZE];
	int msgLenght;
	if((msgLenght = recv(sock, message, BUFFER_SIZE, 0))<0)
	{
		perror("Recieve error. Exit.");
		exit(1);
	}
	printf("Recieved Message:  %s\n",message);
	
	printf("Finish.\n"); 
	close(sock); 
	return 0;
}