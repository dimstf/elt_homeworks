#include <stdio.h>
#include <pthread.h>
#define ARR_SIZE 40

void *thread_calc(void *args)
{
	int *ptr=(int *) args;
	
	printf("%d\n",*ptr);
	return NULL;
}

int main()
{
	int i;
	int *s;
	int a[ARR_SIZE];
	pthread_t thread[ARR_SIZE];
	
	for(i=0;i<ARR_SIZE;i++)
	{
		a[i]=i;
		pthread_create(&thread[i],NULL,thread_calc,(void *) &a[i]);
		//pthread_create(&thread[i],NULL,thread_calc,(void *) &i);
	}
	for(i=0;i<ARR_SIZE;i++)
	{
		pthread_join(thread[i],(void *) &s);
	}
	
	return 0;
}