#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define SHOP_COUNT 5
#define BUYERS_COUNT 3
#define MAX_GOODS 1000
#define ADD_GOODS 500

pthread_mutex_t mt[SHOP_COUNT];
int shop[SHOP_COUNT];

void *supplier(void *args)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	int i=0;
	while(1)
	{
		for(i=0;i<SHOP_COUNT;i++)
		{
			pthread_mutex_lock(&mt[i]);
			if(shop[i]<MAX_GOODS)
			{
				shop[i]+=ADD_GOODS;
				printf("Added %d goods in shop %d.\n",ADD_GOODS,i);
			}
			pthread_mutex_unlock(&mt[i]);
			//sleep(2);
		}
		sleep(2);
	}
	pthread_exit(NULL);
}

void *buyer(void *args)
{
	int needs=10000, i=0;;
	int *ptr=(int *) args;
	while(needs>0)
	{
		for(i=0;i<SHOP_COUNT;i++)
		{
			pthread_mutex_lock(&mt[i]);
			if(shop[i]>0)
			{
				needs=needs-shop[i];
				if(needs>=0)
				{
					printf("Buyer %d buy %d goods.\n",*ptr,shop[i]);
					shop[i]=0;
				} else {
					printf("Buyer %d buy %d goods.\n",*ptr,shop[i]-((-1)*needs));
					shop[i]=(-1)*needs;
					needs=0;
					pthread_mutex_unlock(&mt[i]);
					break;
				}
				printf("Buyer %d needs: %d.\n",*ptr,needs);
			}
			pthread_mutex_unlock(&mt[i]);
			sleep(1);
		}
		sleep(1);
	}
	printf("Buyer %d needs: %d. Finish.\n",*ptr,needs);
	pthread_exit(NULL);
}

int main()
{
	int i=0;
	int buyers_index[BUYERS_COUNT]={0,1,2};
	pthread_t thread_buyers[BUYERS_COUNT];
	pthread_t thread_supplier;
	
	for(i=0;i<SHOP_COUNT;i++)
		shop[i]=MAX_GOODS;

	for(i=0;i<BUYERS_COUNT;i++)
	{
		if(pthread_create(&thread_buyers[i],NULL,buyer,&buyers_index[i])!=0)
		{
			perror("pthread_create error. Exit");
			exit(1);
		}
	}
	
	if(pthread_create(&thread_supplier,NULL,supplier,NULL)!=0)
	{
		perror("pthread_create error. Exit");
		exit(1);
	}
	
	for(i=0;i<BUYERS_COUNT;i++)
	{
		if(pthread_join(thread_buyers[i],NULL)==-1)
		{
			perror("pthread_join error. Exit");
			exit(2);
		}
	}
	
	// Send signal to supplier(finish).
	if(pthread_cancel(thread_supplier)==-1)
	{
		perror("pthread_cancel error. Exit");
		exit(3);
	}
	
	if(pthread_join(thread_supplier,NULL)==-1)
	{
		perror("pthread_join error. Exit");
		exit(2);
	}
	
	return 0;
}