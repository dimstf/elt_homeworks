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
#include "queue.h"

#define BUFFER_SIZE 1024
#define THR_COUNT 6

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

struct queue *q;
pthread_mutex_t mt=PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void *args)
{
	int *msock=(int *) args;
	int msgLenght, Clientsock;
	char message[BUFFER_SIZE];
	
	pthread_mutex_lock(&mt);
	Clientsock=queue_remove(q);
	pthread_mutex_unlock(&mt);
	while(1)
	{
		if(Clientsock!=0)
		{
			bzero(message, BUFFER_SIZE);
			if((msgLenght = recv(Clientsock,message,BUFFER_SIZE,0))<0)
				print_error("Recv error. Exit.",1); 

			printf("Recv message: %s\n",message);
		
			if(send(Clientsock, message, strlen(message),0)<0)
				print_error("Send error. Exit.",1); 
			close(Clientsock);
			Clientsock=0;
		} else {
			sleep(1);
			pthread_mutex_lock(&mt);
			Clientsock=queue_remove(q);
			pthread_mutex_unlock(&mt);
		}
	}
}

int main()
{
	int Mainsock, Clientsock, length; 
	struct sockaddr_in serverAddr;

	if((Mainsock=socket(AF_INET,SOCK_STREAM,0))<0)
		print_error("Socket error. Exit.",1); 

	bzero((char *) &serverAddr,sizeof(serverAddr)); 
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	serverAddr.sin_port=htons(3437);

	if(bind(Mainsock,(struct sockaddr *)&serverAddr,sizeof(serverAddr)))
		print_error("Bind error. Exit.",1); 
	listen(Mainsock,60);

	pthread_t *tids=malloc(sizeof(*tids)*THR_COUNT);
	if(tids==NULL) 
		print_error("Malloc error. Exit.",1);
	q=(struct queue*)malloc(sizeof(struct queue));
	queue_init(q);
	
	printf("Launching %d threads\n", THR_COUNT);
	for(int i=0;i<THR_COUNT;i++) 
		if(pthread_create(&tids[i],NULL,thread_func,(void *)&Mainsock)!=0) 
			print_error("Thread_create error. Exit.",1);

	for(;;)
	{
		if((Clientsock=accept(Mainsock,0,0))<0)
			print_error("Accept error. Exit.",1);
		pthread_mutex_lock(&mt);
		queue_insert(q,Clientsock);
		pthread_mutex_unlock(&mt);
    }
	
	for(int i=0;i<THR_COUNT;i++)
		pthread_join(tids[i],NULL);
	free(tids);
	free(q);
	return 0;
}
