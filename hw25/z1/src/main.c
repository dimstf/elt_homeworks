#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

char message[] = "hello";
char msgbuf[1024];

int main()
{
    int sock;
    struct sockaddr_in addr;
    struct myudpheader header;

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(sock<0)
        print_error("Socket error. Exit.",1);
 
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    header.targ_port = htons(3426);
    header.length = htons(sizeof(header)+sizeof(message));
    header.checksum = 0;
    
    memcpy((void *)msgbuf, (void *)&header, sizeof(header));
    memcpy((void *)(msgbuf+sizeof(header)), (void *)message, sizeof(message));

    sendto(sock, msgbuf, sizeof(header)+sizeof(message), 0,
           (struct sockaddr *)&addr, sizeof(addr));
	   
    char buf[1024];
    socklen_t len=sizeof(addr);
    if(recvfrom(sock,buf,1024,0,(struct sockaddr*)&addr,&len)<0)
	print_error("Recvfrom error. Exit.",1);

    printf("Message: %s\n\n",buf);

    close(sock);

    return 0;
}
