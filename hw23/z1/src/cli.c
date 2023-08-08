#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int main()
{
    int cli_sock;
    struct sockaddr_in addr;

    cli_sock=socket(AF_INET,SOCK_STREAM,0);
    if(cli_sock<0)
        print_error("Socket error. Exit.",1);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
    if(connect(cli_sock,(struct sockaddr *)&addr,sizeof(addr))<0)
        print_error("Connect error. Exit.",1);

	char message[] = "Hello";
	char buf[sizeof(message)];

    send(cli_sock,message,sizeof(message),0);
    recv(cli_sock,buf,sizeof(message),0);
    
    printf("%s\n",buf);
    close(cli_sock);

    return 0;
}