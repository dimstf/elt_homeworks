#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SERV_PORT 3444
#define SERV_PORT2 3445

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

struct myudpheader
{
    u_short src_port;
    u_short targ_port;
    u_short length;
    u_short checksum;
};

char message[]="hello";
char msgbuf[1024];

int main()
{
    int sock;
    struct sockaddr_in addr;
    struct myudpheader header;

    sock=socket(AF_INET,SOCK_RAW,IPPROTO_UDP);
    if(sock<0)
        print_error("Socket error. Exit.",1);
 
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=htons(INADDR_ANY);
    
    header.targ_port=htons(SERV_PORT);
    header.length=htons(sizeof(header)+sizeof(message));
    header.checksum=0;
    
    memcpy((void *)msgbuf,(void *)&header,sizeof(header));
    memcpy((void *)(msgbuf+sizeof(header)),(void *)message,sizeof(message));
    // Отправка сообщения
    sendto(sock,msgbuf,sizeof(header)+sizeof(message),0,(struct sockaddr*)&addr,sizeof(addr));
    printf("Send: %s\n",message);
    close(sock);
    
    // Приём сообщения от эхо сервера
    char buf[100];
    struct sockaddr_in servaddr,cliaddr;
    bzero(&servaddr,sizeof(servaddr));

    int sock1=socket(AF_INET,SOCK_DGRAM,0);        
    if(sock1<0)
    	print_error("Socket error. Exit.",1);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERV_PORT2);
    servaddr.sin_family=AF_INET; 

    if(bind(sock1,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	print_error("Bind error. Exit.",1);
    int length=sizeof(servaddr);

    int len=sizeof(cliaddr);
    int n=recvfrom(sock1,buf,sizeof(buf),0,(struct sockaddr*)&cliaddr,&len);
    buf[n]='\0';
    printf("Recv: %s\n",buf);
    close(sock1);

    return 0;
}
