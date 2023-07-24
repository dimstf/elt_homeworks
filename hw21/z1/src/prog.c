#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sig_hndl()
{
	printf("Signal: SIGUSR1. Exit.\n");
	exit(0);
}

int main()
{
	pid_t pid=getpid();
	printf("pid = %d\n",pid);
	int i=0;
	signal(SIGUSR1,sig_hndl);
	while(i<5)
	{
		sleep(5);
		printf("i = %d\n",i);
		i++;
	}
	printf("No signals. Finish.\n");
	
	return 0;
}