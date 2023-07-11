#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[])
{
	execvp(argv[1],argv+1);
	return 0;
}