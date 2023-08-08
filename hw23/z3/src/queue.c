#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define QMAX 70

struct queue
{
	int qe[QMAX];
	int first, last;
};

void queue_init(struct queue *q)
{
	q->first=1;
	q->last=0;
}

void queue_insert(struct queue *q, int x)
{
	if((q->last)<QMAX-1)
	{
		q->last++;
		q->qe[q->last]=x;
	} else {
		puts("Queue is full.");
	}
}

int queue_is_empty(struct queue *q)
{
	if((q->last)<(q->first))
		return 1;
	
	return 0;
}

int queue_is_full(struct queue *q)
{
	if((q->last)==QMAX)
		return 1;
	
	return 0;
}

int queue_remove(struct queue *q)
{
	int x,h;
	if(queue_is_empty(q))
	{
		//puts("Queue is empty.");
		return 0;
	}
	x=q->qe[q->first];
	
	for(h=(q->first);h<(q->last);h++)
		q->qe[h]=q->qe[h+1];
	q->qe[q->last]=0;
	q->last--;
	
	return x;
}

void queue_print(struct queue *q)
{
	int h;
	if(queue_is_empty(q))
	{
		puts("Queue is empty.");
		return;
	}
	for(h=(q->first);h<=(q->last);h++)
		printf("%d ",q->qe[h]);
	
	return;
}