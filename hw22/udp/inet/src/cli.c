#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in servAddr,clientAddr ;
	struct hostent *hp;
	if(argc<4)
	{ 
		printf("Input udpclient hostname port message\n");
		exit(1);
	}
	if((sock=socket(AF_INET,SOCK_DGRAM,0))<0)
	{ 
		perror("Socket error. Exit.");
		exit(1);
	}
	bzero((char *) &servAddr,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
	bcopy(hp->h_addr,&servAddr.sin_addr,hp -> h_length);
	servAddr.sin_port=htons(atoi(argv[2]));
	bzero((char *)&clientAddr,sizeof(clientAddr));
	clientAddr.sin_family=AF_INET;
	clientAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	clientAddr.sin_port=0;
	if(bind(sock,(struct sockaddr*)&clientAddr,sizeof(clientAddr)))
	{ 
		printf("Bind error. Exit.");
		exit(1);
	}
	printf("CLIENT: ready.\n");
	int n=3;
	/*argv3 в число*/
	int i=atoi(argv[3]);
	int BUFLEN=strlen(argv[3]);
	for(int j=0;j<n;j++)
	{
		int length=sizeof(servAddr);
		sleep(i);
		if(sendto(sock,argv[3],strlen(argv[3]),0,(struct sockaddr*)&servAddr,sizeof(servAddr))<0)
		{
			perror("Sendto error. Exit.");
			exit(1);
		}
		char buf[BUFLEN];
		if((recvfrom(sock,buf,BUFLEN,0,(struct sockaddr*)&clientAddr,&length))<0)
		{ 
			printf("Recvfrom error. Exit.");
			exit(1);
		}
		printf("Message from the server: %s\n\n",buf);
	}
	printf("CLIENT: finish.\n");
	close(sock);
	return 0;
}