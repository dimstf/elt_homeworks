#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define EXAMPLE_PORT 3434
#define EXAMPLE_GROUP "225.0.0.1"

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int main(int argc)
{
	struct sockaddr_in addr;
	int addrlen,sock,cnt;
	struct ip_mreq mreq;
	char msg[50];

	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
		print_error("Socket error. Exit.",1);

	bzero((char *)&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);
	addr.sin_port=htons(EXAMPLE_PORT);
	addrlen=sizeof(addr);

	if(argc>1) 
	{
		addr.sin_addr.s_addr = inet_addr(EXAMPLE_GROUP);
		while(1)
		{
			cnt=sendto(sock,msg,sizeof(msg),0,(struct sockaddr *) &addr, addrlen);
			if(cnt<0)
				print_error("Sendto error. Exit.",1);
		}
	} else {
		if(bind(sock,(struct sockaddr *)&addr,sizeof(addr))<0)       
			print_error("Bind error. Exit.",1);
   
		mreq.imr_multiaddr.s_addr = inet_addr(EXAMPLE_GROUP);         
		mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
		if(setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0) 
			print_error("Setsockopt error. Exit.",1);
	}
	close(sock);
	
	return 0;
}