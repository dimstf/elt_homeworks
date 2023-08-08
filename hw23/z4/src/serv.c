#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define PORT 3438

int master_socket;

void print_error(char *error_msg,int exit_status)
{
	perror(error_msg);
	exit(exit_status);
}

int main(int argc,char *argv[])
{
    int opt=1;
    int addrlen,new_socket,client_socket[60],max_clients=60,activity,valread;
    int max_sd,i,sd;

    struct sockaddr_in address;
    char buffer[6];
    fd_set readfds;

    // инициализируем все client_socket [] в 0, чтобы не проверялось
    for(i=0;i<max_clients;i++)
        client_socket[i]=0;

    if((master_socket=socket(AF_INET,SOCK_STREAM,0))==0)
        print_error("Socket error. Exit.",1);

    if(setsockopt(master_socket,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(opt))<0)
        print_error("Setsockopt error. Exit.",1);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    if(bind(master_socket,(struct sockaddr *)&address,sizeof(address))<0)  
        print_error("Bind error. Exit.",1);

    // Указываем максимум 3 ожидающих соединения для мастер сокета
    if (listen(master_socket,60)<0)
        print_error("Listen error. Exit.",1);

    // принять входящее соединение
    addrlen=sizeof(address);

    while(1)
    {
        // очистка наборов сокетов
        FD_ZERO(&readfds);

        // добавление мастер сокета для установки
        FD_SET(master_socket,&readfds);
        max_sd=master_socket;

        // добавляем дочерние сокеты для установки
        for (i=0;i<max_clients;i++)
        {
            // дескриптор сокета
            sd=client_socket[i];

            // если действительный дескриптор сокета, то добавить в список чтения
            if(sd>0)
                FD_SET(sd,&readfds);

            // наибольший номер дескриптора файла
            if(sd>max_sd)
                max_sd=sd;
        }
        // ожидание активности на одном из сокетов, время ожидания равно NULL,
        activity=select(max_sd+1,&readfds,NULL,NULL,NULL);

        if((activity<0)&&(errno!=EINTR))
            print_error("Select error. Exit.",1);

        // Если что-то случилось с мастер-сокетом, тогда это входящее соединение
        if(FD_ISSET(master_socket,&readfds))
        {  
            if((new_socket=accept(master_socket,(struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
                print_error("Accept error. Exit.",1);
			printf("New connect, fd is %d , ip: %s , port: %d \n" ,new_socket,inet_ntoa(address.sin_addr),ntohs(address.sin_port));  
			
            // добавляем новый сокет в массив сокетов
            for (i=0;i<max_clients;i++)
            {
                // если позиция пуста
                if(client_socket[i]==0)
                {
                    client_socket[i]=new_socket;
                    break;
                }
            }
        }
		
        for (i=0;i<max_clients;i++)
        {
            sd=client_socket[i];

            if(FD_ISSET(sd,&readfds))
            {
                // Проверить, было ли это для закрытия, а также прочитать входящее сообщение
                if((valread=read(sd,buffer,6))==0)
                {
                    // Закрыть сокет и отметить как 0 в списке для повторного использования
					close(sd);
                    client_socket[i]=0;
                }
                // Возвращаем сообщение, которое пришло
                else
                {
                    printf("Message: %s\n",buffer);
					send(sd,buffer,sizeof(buffer),0);
					buffer[valread]='\0';
                }
            }
        }
    }

    return 0;
}
