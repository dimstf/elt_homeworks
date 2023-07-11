#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t pid2, pid3, pid4, pid5, pid6;
	int st;
	
	pid2=fork();
	if(pid2==0)
	{
		printf("2: %d\n",getpid());
		pid4=fork();
		if(pid4==0)
		{
			printf("4: %d\n",getpid());
			exit(0);
		} 
		else
		{
			pid5=fork();
			if(pid5==0)
			{
				printf("5: %d\n",getpid());
				exit(0);
			}
			wait(&st);
		}
		wait(&st);
		exit(0);
	}
	else 
	{
		printf("1: %d\n",getpid());
		pid3=fork();
		if(pid3==0)
		{
			printf("3: %d\n",getpid());
			pid6=fork();
			if(pid6==0)
			{
				printf("6: %d\n",getpid());
				exit(0);
			}
			wait(&st);
			exit(0);
		}
		wait(&st);
		wait(&st);
		//printf("status = %d\n", WEXITSTATUS(st));
	}
	return 0;
}