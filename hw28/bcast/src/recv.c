#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXMSGLEN 255

void print_error(char *error_msg,int exit_status)
{
    perror(error_msg);
    exit(exit_status);
}

int main(int argc,char *argv[])
{
	int sock,recvlen;
	struct sockaddr_in addr;
	unsigned short bport;
	char buf[MAXMSGLEN+1];

	if(argc!=2)
		print_error("Input: %s <Broadcast Port>",0);
	bport=atoi(argv[1]);

	if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		print_error("Socket error. Exit.",1);

    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port=htons(bport);

	if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0)
		print_error("Bind error. Exit.",1);

    if((recvlen=recvfrom(sock,buf,MAXMSGLEN,0,NULL,0))<0)
        print_error("Recvfrom error. Exit.",1);

    buf[recvlen]='\0';
    printf("Recv: %s\n",buf);
    
    close(sock);
    exit(0);
}