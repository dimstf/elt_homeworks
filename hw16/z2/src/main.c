#include <stdio.h>
#include <pthread.h>
#define ARR_SIZE 1000

long int a=0;

void *thread_calc_a(void *args)
{
	for(int i=0;i<1000;i++)
		a++;
	
	return NULL;
}

int main()
{
	int i;
	pthread_t thread[ARR_SIZE];
	
	for(i=0;i<ARR_SIZE;i++)
		pthread_create(&thread[i],NULL,thread_calc_a,NULL);

	for(i=0;i<ARR_SIZE;i++)
		pthread_join(thread[i],NULL);
	printf("a = %ld\n",a);
	
	return 0;
}