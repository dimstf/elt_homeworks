#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo, siginfo_t *info, void *context)
{
	puts("Signal: SIGSEGV. Exit.");
	exit(0);
}

int main(void)
{
	struct sigaction act = { 0 };

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handler;
	if (sigaction(SIGSEGV, &act, NULL) == -1) 
	{
		perror("sigaction");
		exit(1);
	}

	raise(SIGSEGV);
	puts("No signal (main). Exit.");
	
	return 0;
}