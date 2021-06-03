/**
 * The base operation of squence queue
 * 
 * Queue: first come first out
 * Element enQueue in the front, and deQueue at the rear
 * Queue is empty: front == rear
 * Queue is full: rear == MaxSize - 1
 * EnQueue: rear++, element enQueue
 * DeQueue: front++, get the first element in the head
 * 
 * The index is increase from the first to end.
 */

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 5

typedef char Elem;
typedef struct {
    Elem val[MaxSize];
    int front,rear;
}SqQueue;
 
void InitQueue(SqQueue *&q) {
    q = (SqQueue *)malloc(sizeof(SqQueue));
    q->front= q->rear= -1;
}
 
void DestroyQueue(SqQueue *&q) {
    free(q);
}

bool IsEmpty(SqQueue *q) {
    return (q->front == q->rear);
}

bool IsFull(SqQueue *q) {
    return (q->rear == MaxSize - 1);
}

bool enQueue(SqQueue *q, Elem val) {
    if (IsFull(q)) 
        return false;
    q->rear++;
    q->val[q->rear] = val;
    return true;
}

bool deQueue(SqQueue *q, Elem &val) {
    if (IsEmpty(q)) 
        return false;
    q->front++;
    val = q->val[q->front];
    return true;
}

int main() {
    Elem val;
    SqQueue *queue;
    InitQueue(queue);
    printf("The queue is empty? \%s \n", IsEmpty(queue)?"yes":"no");
    printf("EnQueue element a,b,c,d,e\n");
	enQueue(queue,'a');
	enQueue(queue,'b');
	enQueue(queue,'c');
	enQueue(queue,'d');
	enQueue(queue,'e');
    printf("The queue is full? \%s \n", IsFull(queue)?"yes":"no");
    printf("The deQueue sequence is: ");
    while (!IsEmpty(queue)) {
        deQueue(queue, val);
        printf("%c ", val);
    }
    printf("\n");
    printf("The queue is empty? \%s", IsEmpty(queue)?"yes":"no");
    DestroyQueue(queue);
    return 0;
}


