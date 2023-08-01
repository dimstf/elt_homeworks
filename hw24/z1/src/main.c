#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <sys/types.h>
#include <arpa/inet.h>

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int main()
{
	int socket_raw, count=1;
	unsigned char buffer[65536];
	socket_raw=socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(socket_raw<0)
		print_error("Socket error. Exit.",1);

	memset(buffer,0,65536);
	struct sockaddr addr;
	int buflen=0,addr_len=sizeof(addr);

	while(count<20)
	{
		buflen=recvfrom(socket_raw,buffer,65536,0,&addr,&addr_len);
		if(buflen<0)
			print_error("Recvfrom error. Exit.",1);
		printf("count = %d\n",count++);
	}
	close(socket_raw);
	return 0;
}
