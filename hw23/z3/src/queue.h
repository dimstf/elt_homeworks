#if !defined queue_h
#define queue_h
#define QMAX 70
struct queue
{
	int qe[QMAX];
	int first, last;
};
void queue_init(struct queue *q);
void queue_insert(struct queue *q, int x);
int queue_remove(struct queue *q);
#endif