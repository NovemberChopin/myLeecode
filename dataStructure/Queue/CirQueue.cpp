/**
 * Circle Queue
 * Init: front = rear = 0
 * Queue Empty: front == rear
 * Queue full: (rear + 1) % MaxSize == front
 * EnQueue: rear++, element enQueue
 * DeQueue: front++, get the first element in the head.
 */


#include <stdio.h>
#include <stdlib.h>
#define MaxSize 5

typedef char Elem;
typedef struct {
    Elem val[MaxSize];
    int front,rear;
} SqQueue;
 
void InitQueue(SqQueue *&q) {
    q = (SqQueue *)malloc(sizeof(SqQueue));
    q->front= q->rear= 0;
}
 
void DestroyQueue(SqQueue *&q) {
    free(q);
}
 
bool IsEmpty(SqQueue *q) {
    return (q->front == q->rear);
}

bool IsFull(SqQueue *q) {
    return ((q->rear + 1) % MaxSize == q->front);
}

bool EnQueue(SqQueue *q, Elem val) {
    if (IsFull(q))
        return false;
    q->rear = (q->rear + 1) % MaxSize;
    q->val[q->rear] = val;
    return true;
}

bool DeQueue(SqQueue *q, Elem &val) {
    if (IsEmpty(q)) 
        return false;
    q->front = (q->front + 1) % MaxSize;
    val = q->val[q->front];
    return true;
}


int main() {
    Elem val;
    SqQueue *queue;
    InitQueue(queue);
    printf("The queue is enpty? \%s \n", IsEmpty(queue)?"yes":"no");
    printf("Push element a,b,c,d \n");
	EnQueue(queue,'a');
	EnQueue(queue,'b');
	EnQueue(queue,'c');
	EnQueue(queue,'d');
    printf("The queue is full? \%s \n", IsFull(queue)?"yes":"no");
    printf("The pop sequence is: ");
    while (!IsEmpty(queue)) {
        DeQueue(queue, val);
        printf("%c ", val);
    }
    printf("\n");
    printf("The queue is empty? \%s", IsEmpty(queue)?"yes":"no");
    DestroyQueue(queue);
    return 0;
}
