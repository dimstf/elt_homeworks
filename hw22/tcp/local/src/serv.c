#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MY_SOCK_PATH "/tmp/test_path"
#define LISTEN_BACKLOG 50

int main(int argc, char argv[])
{
	int fd, conn_fd;
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;

	fd=socket(PF_UNIX, SOCK_STREAM, 0);
	if (fd==-1)
	{
		perror("Socket error. Exit.");
		exit(1);
	}

	memset(&my_addr,0,sizeof(struct sockaddr_un));
	my_addr.sun_family=AF_UNIX;
	strncpy(&my_addr.sun_path[1],MY_SOCK_PATH,sizeof(my_addr.sun_path)-1);

	if(bind(fd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr_un))==-1)
	{
		perror("Bind error. Exit.");
		exit(1);
	}

	if(listen(fd, LISTEN_BACKLOG)==-1)
	{
		perror("Listen error. Exit.");
		exit(1);
	}
	
	while(1)
	{
		char buf[255];
		peer_addr_size = sizeof(struct sockaddr_un);
		conn_fd = accept(fd, (struct sockaddr*)&peer_addr,&peer_addr_size);
		if(conn_fd==-1)
		{
			perror("Accept error. Exit.");
			exit(1);
		}

		recv(conn_fd,buf,255,0);
		printf("%s\n",buf);
		close(conn_fd);
		break;
	}
	remove(MY_SOCK_PATH);
	
	return 0;
}