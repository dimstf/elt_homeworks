#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

#define SERV_PORT 3510
#define SERV_PORT2 3511

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
    servaddr.sin_port=htons(SERV_PORT);
    servaddr.sin_family=AF_INET; 

    if(bind(socket_udp,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	print_error("Bind error. Exit.",1);
    int length=sizeof(servaddr);

    len=sizeof(cliaddr);
    // Получение сообщения
    int n=recvfrom(socket_udp,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,0);
    buffer[n]='\0';
    printf("Recv (echo-serv): %s\n",buffer);
    // Изменение полученной строки
    strcat(buffer,", world!");
    close(socket_udp);
    
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_port=htons(SERV_PORT2);
    addr.sin_family=AF_INET;
    int socket_udp1=socket(AF_INET,SOCK_DGRAM,0);
    
    if(socket_udp1<0)
	print_error("Socket error. Exit.",1);
    // Отправка измененной строки
    sendto(socket_udp1,buffer,strlen(buffer),0,(struct sockaddr*)&addr,sizeof(addr));
    printf("Send (echo-serv): %s\n",buffer);
    close(socket_udp1);
    
    return 0;
}
