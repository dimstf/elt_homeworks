#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define CLI_COUNT 60

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

void *msgsendrecv(void *args)
{
	int cli_sock;
    struct sockaddr_in addr;

    cli_sock=socket(AF_INET,SOCK_STREAM,0);
    if(cli_sock<0)
        print_error("Socket error. Exit.",1);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3437);
    addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
    if(connect(cli_sock,(struct sockaddr *)&addr,sizeof(addr))<0)
        print_error("Connect error. Exit.",1);

	char message[] = "Hello";
	char buf[sizeof(message)];

    send(cli_sock,message,sizeof(message),0);
    recv(cli_sock,buf,sizeof(message),0);
    
    printf("%s\n",buf);
    close(cli_sock);
}

int main()
{
	int i=0;
	pthread_t cli_index[CLI_COUNT];
	
	for(i=0;i<CLI_COUNT;i++)
		if(pthread_create(&cli_index[i],NULL,msgsendrecv,&cli_index[i])!=0)
			print_error("Pthread_create error. Exit.",1);
	
	for(i=0;i<CLI_COUNT;i++)
		if(pthread_join(cli_index[i],NULL)==-1)
			print_error("Pthread_join error. Exit.",2);

    return 0;
}