#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#define MY_DEST_MAC0 0x00
#define MY_DEST_MAC1 0x00
#define MY_DEST_MAC2 0x00
#define MY_DEST_MAC3 0x00
#define MY_DEST_MAC4 0x00
#define MY_DEST_MAC5 0x00

#define DEFAULT_IF "lo"
#define SERV_PORT 3601
#define SERV_PORT2 3610

void print_error(char *error_msg,int exit_status)
{
    perror(error_msg);
    exit(exit_status);
}

unsigned short csum(unsigned short *buf, int nwords)
{
    unsigned long sum;
    for(sum=0;nwords>0;nwords--)
    sum+=*buf++;
    sum=(sum >> 16)+(sum &0xffff);
    sum+=(sum>>16);
    return (unsigned short)(~sum);
}

int main(int argc, char *argv[])
{
    int sock;
    struct ifreq if_idx;
    struct ifreq if_mac;
    struct ifreq ifreq_ip;
    int len=0;
    unsigned char* buf;
    buf=(unsigned char*)malloc(64); 
    memset(buf,0,64);

    struct ether_header *eh=(struct ether_header*)buf;
    struct iphdr *iph=(struct iphdr*)(buf+sizeof(struct ether_header));
    struct udphdr *uph=(struct udphdr*)(buf+sizeof(struct ether_header)+sizeof(struct iphdr));
    struct sockaddr_ll addr;
    char ifName[IFNAMSIZ];
    
    if(argc>1)
        strcpy(ifName,argv[1]);
    else
        strcpy(ifName,DEFAULT_IF);

    if((sock=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)))==-1)
        print_error("Socket error. Exit.",1);

    memset(&if_idx,0,sizeof(struct ifreq));
    strncpy(if_idx.ifr_name,ifName,IFNAMSIZ-1);
    if(ioctl(sock,SIOCGIFINDEX,&if_idx)<0)
	print_error("Ioctl 1 error. Exit.",1);

    memset(&if_mac,0,sizeof(struct ifreq));
    strncpy(if_mac.ifr_name,ifName,IFNAMSIZ-1);
    if(ioctl(sock,SIOCGIFHWADDR,&if_mac)<0)
	print_error("Ioctl 2 error. Exit.",1);

    memset(&ifreq_ip,0,sizeof(ifreq_ip));
    strncpy(ifreq_ip.ifr_name,ifName,IFNAMSIZ-1);
    if(ioctl(sock,SIOCGIFADDR,&ifreq_ip)<0)
	print_error("Ioctl 3 error. Exit.",1);

    /*eh->ether_shost[0]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
    eh->ether_shost[1]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
    eh->ether_shost[2]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
    eh->ether_shost[3]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
    eh->ether_shost[4]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
    eh->ether_shost[5]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];*/
    eh->ether_shost[0]=MY_DEST_MAC0;
    eh->ether_shost[1]=MY_DEST_MAC1;
    eh->ether_shost[2]=MY_DEST_MAC2;
    eh->ether_shost[3]=MY_DEST_MAC3;
    eh->ether_shost[4]=MY_DEST_MAC4;
    eh->ether_shost[5]=MY_DEST_MAC5;
    eh->ether_dhost[0]=MY_DEST_MAC0;
    eh->ether_dhost[1]=MY_DEST_MAC1;
    eh->ether_dhost[2]=MY_DEST_MAC2;
    eh->ether_dhost[3]=MY_DEST_MAC3;
    eh->ether_dhost[4]=MY_DEST_MAC4;
    eh->ether_dhost[5]=MY_DEST_MAC5;
    /*eh->ether_dhost[0]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[0];
    eh->ether_dhost[1]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[1];
    eh->ether_dhost[2]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[2];
    eh->ether_dhost[3]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[3];
    eh->ether_dhost[4]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[4];
    eh->ether_dhost[5]=((uint8_t *)&if_mac.ifr_hwaddr.sa_data)[5];*/
    eh->ether_type=htons(ETH_P_IP);
    len+=sizeof(struct ether_header);

    iph->ihl=5;
    iph->version=4;
    iph->tos=0;
    iph->tot_len=htons(sizeof(struct iphdr)+sizeof(struct udphdr)+6);
    iph->id=htons(54321);
    iph->frag_off=0;
    iph->ttl=64;
    iph->protocol=IPPROTO_UDP;
    iph->check=0;
    //iph->saddr=inet_addr(inet_ntoa((((struct sockaddr_in*)&(ifreq_ip.ifr_addr))->sin_addr)));    
    iph->saddr=inet_addr("127.0.0.1");    
    iph->daddr=inet_addr("127.0.0.1");
    
    iph->check=csum((unsigned short *)buf,iph->tot_len);
    len+=sizeof(struct iphdr);

    uph->source=htons(7777);
    uph->dest=htons(SERV_PORT);
    uph->check=0;

    len+=sizeof(struct udphdr);
    buf[len++]='h';
    buf[len++]='e';
    buf[len++]='l';
    buf[len++]='l';
    buf[len++]='o';
    buf[len++]='\0';
    uph->len=htons((len-sizeof(struct iphdr)-sizeof(struct ethhdr)));
    //uph->len=htons(sizeof(struct udphdr)+6);

    addr.sll_ifindex=if_idx.ifr_ifindex;
    addr.sll_halen=ETH_ALEN;
    addr.sll_addr[0]=MY_DEST_MAC0;
    addr.sll_addr[1]=MY_DEST_MAC1;
    addr.sll_addr[2]=MY_DEST_MAC2;
    addr.sll_addr[3]=MY_DEST_MAC3;
    addr.sll_addr[4]=MY_DEST_MAC4;
    addr.sll_addr[5]=MY_DEST_MAC5;
	
    int len_ll=sizeof(struct sockaddr_ll);
    // Отправка сообщения
    if(sendto(sock,buf,len,0,(struct sockaddr*)&addr,len_ll)<0)
	print_error("Send error. Exit.",1);
    printf("Send: hello\n");
    close(sock);
    
    // Приём сообщения от эхо сервера
    char msg[100];
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

    int ln=sizeof(cliaddr);
    int n=recvfrom(sock1,msg,sizeof(msg),0,(struct sockaddr*)&cliaddr,&ln);
    msg[n]='\0';
    printf("Recv: %s\n",msg);
    close(sock1);
	
    return 0;
}
