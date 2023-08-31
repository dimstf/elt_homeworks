#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <arpa/inet.h>

#define PCKT_LEN 8192
#define SERV_PORT 3475
#define SERV_PORT2 3476

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

int main(int argc,char const *argv[])
{
    if (argc!=4) 
    {
	printf("Error: Invalid parameters!\n");
	printf("Usage: %s <source hostname/IP> <source port> <target hostname/IP>\n", argv[0]);
	exit(1);
    }

    u_int16_t src_port, dst_port;
    u_int32_t src_addr, dst_addr;
    src_addr=inet_addr(argv[1]);
    dst_addr=inet_addr(argv[3]);
    src_port=atoi(argv[2]);
    //dst_port=atoi(argv[4]);

    int sd;
    char buffer[PCKT_LEN];
    struct iphdr *ip=(struct iphdr *)buffer;
    struct udphdr *udp=(struct udphdr *)(buffer+sizeof(struct iphdr));

    struct sockaddr_in sin;
    int one=1;
    const int *val=&one;

    memset(buffer,0,PCKT_LEN);

    sd=socket(PF_INET,SOCK_RAW,IPPROTO_UDP);
    if(sd<0) 
	print_error("Socket error. Exit.",1);

    if(setsockopt(sd,IPPROTO_IP,IP_HDRINCL,val,sizeof(one))<0)
	print_error("Setsockopt error. Exit.",1);

    sin.sin_family=AF_INET;
    sin.sin_port=htons(dst_port);
    sin.sin_addr.s_addr=dst_addr;

    ip->ihl=5;
    ip->version=4;
    ip->tos=16;
    ip->tot_len=htons(sizeof(struct iphdr)+sizeof(struct udphdr)+6);
    ip->id=htons(54321);
    ip->ttl=64;
    ip->protocol=IPPROTO_UDP;
    ip->saddr=src_addr;
    ip->daddr=dst_addr;

    udp->source=htons(src_port);
    udp->dest=htons(SERV_PORT);
    int len=sizeof(struct iphdr)+sizeof(struct udphdr)+6;
    udp->len=htons(sizeof(struct udphdr)+6);
    
    buffer[len-6]='h';
    buffer[len-5]='e';
    buffer[len-4]='l';
    buffer[len-3]='l';
    buffer[len-2]='o';
    buffer[len-1]='\0';

    ip->check=csum((unsigned short *)buffer,sizeof(struct iphdr)+sizeof(struct udphdr)+6);
    // Отправка сообщения
    if(sendto(sd,buffer,sizeof(struct iphdr)+sizeof(struct udphdr)+6,0,(struct sockaddr *)&sin,sizeof(sin))<0)
	print_error("Sendto error. Exit.",1);
    printf("Send: hello\n");
    close(sd);
    
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

    int ln=sizeof(cliaddr);
    int n=recvfrom(sock1,buf,sizeof(buf),0,(struct sockaddr*)&cliaddr,&ln);
    buf[n]='\0';
    printf("Recv: %s\n",buf);
    close(sock1);
    
    return 0;
}
