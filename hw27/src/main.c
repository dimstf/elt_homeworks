#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#define MY_DEST_MAC0 0x00
#define MY_DEST_MAC1 0x00
#define MY_DEST_MAC2 0x00
#define MY_DEST_MAC3 0x00
#define MY_DEST_MAC4 0x00
#define MY_DEST_MAC5 0x00

#define DEFAULT_IF "enp5s0"
#define BUF_SIZE 1024

void print_error(char *error_msg,int exit_status)
{
    perror(error_msg);
    exit(exit_status);
}

int main(int argc,char *argv[])
{
    int sock;
    struct ifreq if_idx;
    struct ifreq if_mac;
    int tx_len=0;
    char buf[BUF_SIZE];
    struct ether_header *eh=(struct ether_header *)buf;
    struct iphdr *iph=(struct iphdr *)(buf + sizeof(struct ether_header));
    struct sockaddr_ll addr;
    char ifName[IFNAMSIZ];

    if(argc>1)
	strcpy(ifName,argv[1]);
    else
	strcpy(ifName,DEFAULT_IF);

    if((sock=socket(AF_PACKET,SOCK_RAW,IPPROTO_RAW))==-1)
	print_error("Socket error. Exit.",1);

    memset(&if_idx,0,sizeof(struct ifreq));
    strncpy(if_idx.ifr_name,ifName,IFNAMSIZ-1);
    if(ioctl(sock, SIOCGIFINDEX, &if_idx)<0)
	print_error("Ioctl error 1. Exit",1);

    memset(&if_mac,0,sizeof(struct ifreq));
    strncpy(if_mac.ifr_name,ifName,IFNAMSIZ-1);
    if(ioctl(sock,SIOCGIFHWADDR,&if_mac)<0)
	print_error("Ioctl error 2. Exit",1);

    memset(buf,0,BUF_SIZE);

    eh->ether_shost[0]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
    eh->ether_shost[1]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
    eh->ether_shost[2]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
    eh->ether_shost[3]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
    eh->ether_shost[4]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
    eh->ether_shost[5]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];
    eh->ether_dhost[0]=MY_DEST_MAC0;
    eh->ether_dhost[1]=MY_DEST_MAC1;
    eh->ether_dhost[2]=MY_DEST_MAC2;
    eh->ether_dhost[3]=MY_DEST_MAC3;
    eh->ether_dhost[4]=MY_DEST_MAC4;
    eh->ether_dhost[5]=MY_DEST_MAC5;
    eh->ether_type=htons(ETH_P_IP);
    tx_len+=sizeof(struct ether_header);
	
    buf[tx_len++] = 0xde;
    buf[tx_len++] = 0xad;
    buf[tx_len++] = 0xbe;
    buf[tx_len++] = 0xef;
    
    addr.sll_ifindex=if_idx.ifr_ifindex;
    addr.sll_halen=ETH_ALEN;

    addr.sll_addr[0]=MY_DEST_MAC0;
    addr.sll_addr[1]=MY_DEST_MAC1;
    addr.sll_addr[2]=MY_DEST_MAC2;
    addr.sll_addr[3]=MY_DEST_MAC3;
    addr.sll_addr[4]=MY_DEST_MAC4;
    addr.sll_addr[5]=MY_DEST_MAC5;

    if(sendto(sock,buf,tx_len,0,(struct sockaddr*)&addr,sizeof(struct sockaddr_ll))<0)
	print_error("Sendto error. Exit.",1);

    return 0;
}
