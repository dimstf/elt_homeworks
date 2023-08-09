#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int main(int argc, char *argv[])
{
	int sock, flag=1, length, port;
	struct sockaddr_in addr;
	char *ip_addr,*msg;

	if(argc<4)
	{
		fprintf(stderr,"Usage: %s <IP Address> <Port> <Send String>\n",argv[0]);
		exit(1);
	}

	ip_addr = argv[1];
	port=atoi(argv[2]);
	msg=argv[3];

	if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		print_error("Socket error. Exit.",1);

	if(setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(void *)&flag,sizeof(flag))<0)
		print_error("Setsockopt error. Exit.",1);

	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(ip_addr);
	addr.sin_port=htons(port);

    length = strlen(msg);
	if(sendto(sock,msg,length,0,(struct sockaddr *)&addr,sizeof(addr))!=length)
		print_error("Sendto error. Exit.",1);
	
	return 0;
}