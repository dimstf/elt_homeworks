#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define MY_SOCK_PATH "/tmp/test_path"
#define LISTEN_BACKLOG 50

int main(int argc, char argv[])
{
	int fd;
	struct sockaddr_un serv_addr;

	fd=socket(PF_UNIX,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("Socket error. Exit.");
		exit(1);
	}

	memset(&serv_addr,0,sizeof(struct sockaddr_un));
	serv_addr.sun_family=AF_UNIX;
	strncpy(&serv_addr.sun_path[1],MY_SOCK_PATH,sizeof(serv_addr.sun_path)-1);

	if(connect(fd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
	{
		perror("Connect error. Exit.");
		exit(1);
	}
	char str[]="Hello, world!";
	send(fd,str,sizeof(str),0);

	close(fd);
}