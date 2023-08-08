#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define THR_COUNT 5

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int gdata;

void *thread_func()
{
	int Mainsock=gdata;
	int Clientsock;
	
	for(;;)
	{
		char message[BUFFER_SIZE]; 
		int msgLenght;
		if((Clientsock=accept(Mainsock,0,0))<0)
			print_error("Accept error. Exit.",1); 

		bzero(message, BUFFER_SIZE);
		if((msgLenght = recv(Clientsock,message,BUFFER_SIZE,0))<0)
			print_error("Recv error. Exit.",1); 

		printf("Recv message: %s\n",message);
		
		if(send(Clientsock, message, strlen(message),0)<0)
			print_error("Send error. Exit.",1); 
		close(Clientsock); 
    }
}

int main()
{
	int Mainsock, Clientsock, length; 
	struct sockaddr_in serverAddr;

	if((Mainsock=socket(AF_INET,SOCK_STREAM,0))<0)
		print_error("Socket error. Exit.",1); 
	gdata=Mainsock;

	bzero((char *) &serverAddr,sizeof(serverAddr)); 
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	serverAddr.sin_port=htons(3424);

	if(bind(Mainsock,(struct sockaddr *)&serverAddr,sizeof(serverAddr)))
		print_error("Bind error. Exit.",1); 
	listen(Mainsock,5);

	pthread_t *tids=malloc(sizeof(*tids)*THR_COUNT);
	if(tids==NULL) 
		print_error("Malloc error. Exit.",1);

	printf("Launching %d threads\n", THR_COUNT);
	for(int i=0;i<THR_COUNT;i++) 
		if(pthread_create(&tids[i],NULL,thread_func, NULL) != 0) 
			print_error("Thread_create error. Exit.",1);
	
	for(;;)
	{
		char message[BUFFER_SIZE]; 
		int msgLenght;
		if((Clientsock = accept(Mainsock,0,0))<0)
			print_error("Accept error. Exit.",1); 

		bzero(message,BUFFER_SIZE);
		if((msgLenght=recv(Clientsock,message,BUFFER_SIZE,0))<0)
			print_error("Recv error. Exit.",1); 

		printf("Recv message: %s\n",message);
		
		if(send(Clientsock,message,strlen(message),0)<0)
			print_error("Send error. Exit.",1);
		close(Clientsock); 
    }
	
	for(int i=0;i<THR_COUNT;i++)
		pthread_join(tids[i],NULL);
	free(tids);
	
	return 0;
}
