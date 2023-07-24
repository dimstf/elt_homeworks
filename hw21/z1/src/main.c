#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	pid_t pid;
	printf("Input pid: ");
	scanf("%d",&pid);
	kill(pid,SIGUSR1);
	
	return 0;
}
