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
	char *mip;
	unsigned short mport;
	char buf[MAXMSGLEN+1];
	struct ip_mreq mreq;

	if(argc!=3)
		print_error("Input: %s <Multicast IP> <Multicast Port>",0);
	mip=argv[1];
	mport=atoi(argv[2]);

	if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		print_error("Socket error. Exit.",1);

	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(mport);
	
	if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))<0)
		print_error("Bind error. Exit.",1);

	mreq.imr_multiaddr.s_addr=inet_addr(mip);
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	if(setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,(void*)&mreq,sizeof(mreq))<0)
		print_error("Setsockopt error. Exit.",1);

    if((recvlen=recvfrom(sock,buf,MAXMSGLEN,0,NULL,0))<0)
        print_error("Recvfrom error. Exit.",1);

    buf[recvlen]='\0';
    printf("Recv: %s\n",buf);
    close(sock);
	
    return 0;;
}