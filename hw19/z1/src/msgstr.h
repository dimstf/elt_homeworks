#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MSGSIZE 128	

typedef struct msgbuf {
	long mtype;
	char mtext[MSGSIZE];
} message_buf;
