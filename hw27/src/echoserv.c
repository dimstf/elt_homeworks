#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>

#define SERV_PORT2 3610
#define DEST_MAC0	0x00
#define DEST_MAC1	0x00
#define DEST_MAC2	0x00
#define DEST_MAC3	0x00
#define DEST_MAC4	0x00
#define DEST_MAC5	0x00
#define ETHER_TYPE	0x0800
#define DEFAULT_IF	"enp5s0"
#define BUF_SIZ		1024

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int main(int argc, char *argv[])
{   
    int sockfd,sockopt;
    ssize_t numbytes;
    struct ifreq ifopts;
    struct ifreq if_ip;
    struct sockaddr_storage their_addr;
    uint8_t buf[BUF_SIZ];
    char ifName[IFNAMSIZ];

    if(argc>1)
	strcpy(ifName,argv[1]);
    else
	strcpy(ifName,DEFAULT_IF);

    struct ether_header *eh=(struct ether_header*)buf;
    struct iphdr *iph=(struct iphdr*)(buf+sizeof(struct ether_header));
    struct udphdr *udph=(struct udphdr*)(buf+sizeof(struct iphdr)+sizeof(struct ether_header));

    memset(&if_ip,0,sizeof(struct ifreq));

    if((sockfd=socket(PF_PACKET,SOCK_RAW,htons(ETHER_TYPE)))==-1) 
	print_error("Socket error. Exit.",1);	

    strncpy(ifopts.ifr_name,ifName,IFNAMSIZ-1);
    ioctl(sockfd,SIOCGIFFLAGS,&ifopts);
    ifopts.ifr_flags|=IFF_PROMISC;
    ioctl(sockfd,SIOCSIFFLAGS,&ifopts);
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&sockopt,sizeof sockopt)==-1)
	print_error("Setsockopt error. Exit.",1);

    if(setsockopt(sockfd,SOL_SOCKET,SO_BINDTODEVICE,ifName,IFNAMSIZ-1)==-1)
	    print_error("Setsockopt error. Exit.",1);

    numbytes=recvfrom(sockfd,buf,BUF_SIZ,0,NULL,NULL);
    printf("listener: got packet %lu bytes\n",numbytes);
    char buffer[100];
    memcpy(buffer,buf+42,6);
    printf("Recv (echo-serv): %s\n",buffer);
    // Изменение полученной строки
    strcat(buffer,", world!");
    close(sockfd);
    
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
