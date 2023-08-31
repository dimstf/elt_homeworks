#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
extern int errno;
int main()
{
	printf("Select an option: \n1. Sign up\n2. Login\n3. Create a new group\n");
	char user_name[1000];
	scanf("%s",user_name);
	FILE *fp;
	FILE *fp1;
	char *option=user_name;
	char *current;
	char id[100];
	if(strcmp(option,"1")==0)
	{
		printf("Please enter your username: \n");
		fp1=fopen("groups.txt","a");
		char name[100]="";
		getchar();
		scanf("%[^\n]",id);
		strcat(name,id);
		strcat(id,".txt");
		fp = fopen(id,"a");
		fclose(fp);
		char input[100]="";
		strcat(input,name);
		strcat(input," ");
		strcat(input,name);
		strcat(input," \n");
		fprintf(fp1,"%s",input);
		fclose(fp1);
		return 0;
	}
	else if(strcmp(option,"3")==0){
		fp = fopen("groups.txt","a");
		printf("Enter number of members: \n");
		int num;
		scanf("%d",&num);
		printf("Enter group name: \n");
		char group[100];
		getchar();
		scanf("%[^\n]",group);
		strcat(group," ");
		fprintf(fp,"%s",group );
		for(int j=0;j<num;j++){
			printf("%d. Enter user id: \n",j+1);
			char name[50];
			scanf("%s",name);
			strcat(name, " ");
			fprintf(fp, "%s",name);
		}
		fprintf(fp," \n");
		fclose(fp);
		return 0;
	}
	else if(strcmp(option,"2")==0)
	{
		printf("Please enter your username: \n");
		scanf("%s",id);
	}
    else{
        printf("Please enter correct option\n");
        return 0;     
    }  
	while(1){
		printf("Select Option:\n1. Read\n2. Write\n3. Exit\n");
		scanf("%s",user_name);
		option=user_name;
		if(strcmp(option,"3")==0)
		{		
			return 0;			
		}
		else if(strcmp("2",option)==0)
		{
			printf("Enter message \n");
			char msg[1000];
			getchar();
			scanf("%[^\n]", msg);
			printf("Enter recipient: \n");
			fp = fopen("groups.txt","r");
			scanf("%s", user_name);
			char* line=NULL;
			size_t len=0;
			int read=0;
			char *token;
			while((read=getline(&line,&len,fp))!=-1){
				token = strtok(line," ");
				if(strcmp(token,user_name)==0){
					break;
				}
			}
			fclose(fp);
			if(read==-1)
			{
				printf("Invalid recipient\n");
				continue;
			}
			token=strtok(NULL," ");
			while(token!=NULL ){
				if(strcmp(token,"\n")==0)
				{
					break;
				}
				char send[100]="";
				strcat(send,token);
				getchar();
				strcat(send,".txt");
				key_t key=ftok(send,65);
				int shmid=shmget(key,1024,0666|IPC_CREAT);
				if(shmid==-1)
				{
					int errnum=errno;
					printf("Value of error %d\n",errnum);
					perror("Unable to get id");
					printf("%s\n",strerror(errnum));
				}
				char *str=(char *)shmat(shmid,(void*)0,0);
				if((void*)str==(void*)-1)
				{
					int errnum=errno;
					printf("Value of error %d\n",errnum);
					perror("Unable to attach to shared memory.");
					printf("%s\n",strerror(errnum));
				}
				strcat(str,"\n");
				strcat(str , id);
				strcat(str,": ");
				strcat(str, msg);
				shmdt(str);
				token=strtok(NULL," ");
			}
			
		}
		else
		{
				char *id1=strdup(id);
				strcat(id1,".txt");
				key_t key=ftok(id1,65);
				int shmid=shmget(key,1024,0666|IPC_CREAT);
				if(shmid==-1)
				{
					int errnum = errno;
					printf("Value of error %d\n",errnum);
					perror("Unable to get id");
					printf("%s\n",strerror(errnum));
				}
				char *str=(char*) shmat(shmid,(void*)0,0);
				if((void*)str==(void*)-1)
				{
					int errnum = errno;
					printf("Value of error %d\n",errnum);
					perror("Unable to attach to shared memory.");
					printf("%s\n",strerror(errnum));
				}
				printf("%s\n",str);
				shmdt(str);
				shmctl(shmid,IPC_RMID,NULL);
		}
	}
	return 0;
}