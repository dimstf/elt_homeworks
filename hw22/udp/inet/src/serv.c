#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netdb.h> 
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>

#define BUFLEN 81
int sockMain;

void TimeOut(int var)
{
	printf("Timeout 90 seconds. Close socket and exit.\n");
	close(sockMain);
	exit(0);
}

int main() 
{
	int length,msglength;
	struct sockaddr_in servAddr,clientAddr;
	char buf[BUFLEN];
	if((sockMain=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("Socket error. Exit.");
		exit(1);
	}
	bzero((char *) &servAddr,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=0;
	if(bind(sockMain,(struct sockaddr*)&servAddr,sizeof(servAddr)))
	{ 
		perror("Bind error. Exit.");
		exit(1);
	}
	length=sizeof(servAddr);
	if(getsockname(sockMain,(struct sockaddr*)&servAddr,&length))
	{ 
		perror("getsockname error. Exit.");
		exit(1);
	}
	printf("Server: port number - % d\n",ntohs(servAddr.sin_port ));
	signal(SIGALRM,TimeOut);
	alarm(90);
	for(int k=0;k<3;k++) 
	{
		length=sizeof(clientAddr) ;
		bzero(buf,sizeof(BUFLEN));
		if((msglength=recvfrom(sockMain,buf,BUFLEN,0,(struct sockaddr*)&clientAddr,&length))<0)
			exit(1);

		printf("SERVER: IP adress: %s\n",inet_ntoa(clientAddr.sin_addr));
		printf("SERVER: PORT client: %d\n",ntohs(clientAddr.sin_port)) ;
		printf("SERVER: Message: %s\n\n",buf);
		
		if(sendto(sockMain,buf,strlen(buf),0,(struct sockaddr*)&clientAddr,sizeof(clientAddr))<0)
		{
			perror("Sendto error. Exit.");
			exit(1);
		}
	}
	printf("Finish.\n");
	
	return 0;
}