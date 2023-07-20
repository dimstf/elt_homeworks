#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MSGSIZE 8

int main()
{
	int pp1[2],pp2[2],i;
	pid_t pid;

	if(pipe(pp1)<0)
		exit(1);
	if(pipe(pp2)<0)
		exit(1);
	
	pid=fork();
	switch(pid)
	{
		case -1:
		{
			perror("fork() error. Exit.");
			exit(1);
		} break;
		case 0:
		{
			char outbuf[MSGSIZE];
			for(i=0;i<2;i++)
			{
				read(pp1[0],outbuf,MSGSIZE);
				printf("%s\n",outbuf);
			}
			char msg1[]="hello 3";
			char msg2[]="hello 4";
			write(pp2[1],msg1,MSGSIZE);
			write(pp2[1],msg2,MSGSIZE);
			exit(0);
		} break;
		default:
		{
			char msg1[]="hello 1";
			char msg2[]="hello 2";
			write(pp1[1],msg1,MSGSIZE);
			write(pp1[1],msg2,MSGSIZE);
			char outbuf[MSGSIZE];
			for(i=0;i<2;i++)
			{
				read(pp2[0],outbuf,MSGSIZE);
				printf("%s\n",outbuf);
			}
			int st;
			wait(&st);
		} break;
	}
	
	return 0;
}