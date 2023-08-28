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
	char *mip;
	unsigned short mport;
	char *sendmsg;
	unsigned char mttl;
	unsigned int msglen;

	if((argc<4)||(argc>5))
		print_error("Input: %s <Multicast Address> <Port> <Message> <TTL>",0);
	mip=argv[1];
	mport=atoi(argv[2]);
	sendmsg=argv[3];

	if(argc==5)
		mttl=atoi(argv[4]);
	else
		mttl = 2;

	if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))<0)
		print_error("Socket error. Exit.",1);

	if(setsockopt(sock,IPPROTO_IP,IP_MULTICAST_TTL,(void *)&mttl,sizeof(mttl))<0)
		print_error("Setsockopt error. Exit.",1);

	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(mip);
	addr.sin_port=htons(mport);

	msglen=strlen(sendmsg);
	for (int i=0;i<3;i++)
	{
		if(sendto(sock,sendmsg,msglen,0,(struct sockaddr*)&addr,sizeof(addr))!=msglen)
			print_error("Sendto error. Exit.",1);
		sleep(3);
	}
	close(sock);
	
	return 0;
}