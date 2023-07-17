#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MSGSIZE 8

int main()
{
	int pp[2],i;
	pid_t pid;

	if(pipe(pp)<0)
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
				read(pp[0],outbuf,MSGSIZE);
				printf("%s\n",outbuf);
			}
			exit(0);
		} break;
		default:
		{
			char msg1[]="hello 1";
			char msg2[]="hello 2";
			write(pp[1],msg1,MSGSIZE);
			write(pp[1],msg2,MSGSIZE);
			int st;
			wait(&st);
		} break;
	}
	
	return 0;
}