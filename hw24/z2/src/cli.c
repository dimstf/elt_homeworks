#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int main()
{ 
    char buffer[100];
    char *message="Hello";
    int socket_udp, n;
    struct sockaddr_in addr;

    bzero(&addr,sizeof(addr));

    printf("Input port: ");
    int serv_port=0;
    scanf("%d",&serv_port);
    
    //addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    addr.sin_port=htons(serv_port);
    addr.sin_family=AF_INET;
    socket_udp=socket(AF_INET,SOCK_DGRAM,0);
    
    if(socket_udp<0)
	print_error("Socket error. Exit.",1);

    if(connect(socket_udp,(struct sockaddr *)&addr,sizeof(addr))<0)
	print_error("Connect error. Exit.",1);

    sendto(socket_udp,message,256,0,(struct sockaddr*)NULL,sizeof(addr));

    recvfrom(socket_udp,buffer,sizeof(buffer),0,(struct sockaddr*)NULL,NULL);
    puts(buffer);

    close(socket_udp);
    return 0;
}
