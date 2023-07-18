#include "msgstr.h"

int messagercv()
{
	printf("\nDo you want to accept the message (1-yes)?\n");
	int c;
	scanf("%d",&c);
	if(c!=1)
		return 0;
	
	int msqid;
	key_t key;
	
	pid_t pid;
	pid=fork();
	if(pid==0)
		key=5;
	else
		key=6;
	message_buf rbuf;
	
	msqid = msgget(key, 0666);
	
	msgrcv(msqid,&rbuf,MSGSIZE,1,0);
	printf("%s\n", rbuf.mtext);
	
	if(pid==0)
		exit(0);
	return 0;
}

int messagesnt()
{
	printf("\nDo you want to send messages to users (1-yes)?\n");
	int c;
	scanf("%d",&c);
	if(c!=1)
		return 0;
	
	key_t key;
	int msqid;
	
	pid_t pid;
	pid=fork();
	if(pid==0)
		key=7;
	else
		key=8;
	
	int msgflg = IPC_CREAT | 0666;
	message_buf sbuf;
	size_t buf_length;

	msqid = msgget(key, msgflg);
	sbuf.mtype = 1;
	(void) strcpy(sbuf.mtext, "Hello, I'm chat room");
	buf_length = strlen(sbuf.mtext) + 1;
	
	if((msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT)) < 0){
		perror("msgsnd");
		exit(1);
	} else
		printf("Message: \"%s\" sent\n", sbuf.mtext);
		
	if(pid==0)
		exit(0);
	return 0;
}

int main()
{
/* Общая комната. 
Принимает сообщения и отправляет ответ */
	messagercv();

	sleep(1);
	/* Ответ на сообщения */
	messagesnt();
	
	return 0;
}
