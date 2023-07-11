#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	int st;
	
	pid=fork();
	if(pid==0)
	{
		printf("Child pid: %d\n",getpid());
		exit(0);
	}
	else 
	{
		printf("Parent pid: %d\n",getpid());
		wait(&st);
		printf("status = %d\n", WEXITSTATUS(st));
	}
	return 0;
}