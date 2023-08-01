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
    int socket_udp,len;
    struct sockaddr_in servaddr,cliaddr;
    bzero(&servaddr,sizeof(servaddr));

    socket_udp=socket(AF_INET,SOCK_DGRAM,0);        
    if(socket_udp<0)
    	print_error("Socket error. Exit.",1);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=0;
    servaddr.sin_family=AF_INET; 

    if(bind(socket_udp,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	print_error("Bind error. Exit.",1);
    int length=sizeof(servaddr);
    if(getsockname(socket_udp,(struct sockaddr*)&servaddr,&length))
	print_error("getsockname error. Exit.",1);

    printf("Server port: %d\n",ntohs(servaddr.sin_port));
    
    len=sizeof(cliaddr);
    int n=recvfrom(socket_udp,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
    buffer[n]='\0';
    puts(buffer);
    strcat(buffer,", world!");
    sendto(socket_udp,buffer,256,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    close(socket_udp);
    return 0;
}
