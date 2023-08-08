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
    int cli_sock, serv_sock;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    serv_sock=socket(AF_INET, SOCK_STREAM, 0);
    if(serv_sock<0)
        print_error("Socket error. Exit.",1);
	
    addr.sin_family=AF_INET;
    addr.sin_port=htons(3424);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(serv_sock,(struct sockaddr *)&addr,sizeof(addr))<0)
        print_error("Bind error. Exit.",1);

    if(listen(serv_sock,1)<0)
		print_error("Listen error. Exit.",1);
    
    while(1)
    {
        cli_sock=accept(serv_sock, NULL, NULL);
        if(cli_sock<0)
            print_error("Accept error. Exit.",1);
        
        switch(fork())
        {
			case -1:
				print_error("Fork error.",1);
				break;
            
			case 0:
				close(serv_sock);
				while(1)
				{
					bytes_read=recv(cli_sock,buf,1024,0);
					if(bytes_read<=0) 
						break;
					send(cli_sock,buf,bytes_read,0);
				}

				close(cli_sock);
				exit(0);
			default:
				close(cli_sock);
        }
    }
    close(serv_sock);

    return 0;
}