#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_error(char *error_msg,int exit_status)
{
    perror(error_msg);
    exit(exit_status);
}

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in addr;
    char *bip;
    unsigned short bport;
    char *sendmsg;
    unsigned int msglen;

	if(argc<4)
		print_error("Input: %s <IP Address> <Port> <Send String>",0);
	bip=argv[1];
	bport=atoi(argv[2]);
	sendmsg=argv[3];

    if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
        print_error("Socket error. Exit.",1);

	int flag=1;
	if(setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(void*)&flag,sizeof(flag))<0)
		print_error("Setsockopt error. Exit.",1);

	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(bip);
	addr.sin_port=htons(bport);

	msglen=strlen(sendmsg);
	for(int i=0;i<3;i++)
    {
         if(sendto(sock,sendmsg,msglen,0,(struct sockaddr*)&addr,sizeof(addr))!=msglen)
             print_error("Sendto error. Exit.",1);

        sleep(3);
    }
    close(sock);
	
	return 0;
}