/**
 * Link Queue
 * Insert data in the end, and get data in the begin
 * Time: 2021-6-3
 * Author: jsfantasy
 */

#include <stdio.h>
#include <stdlib.h>

typedef char Elem;
typedef struct qNode {
    Elem val;
    struct qNode * next;
} QNode;
typedef struct {
    QNode *front;
    QNode *rear;
}LinkQueue;

void InitQueue(LinkQueue *&queue) {
    queue = (LinkQueue*)malloc(sizeof(LinkQueue));
    queue->front=queue->rear = NULL;
}

void DestroyQueue(LinkQueue *&queue) {
    QNode *p, *r;
    p = queue->front;
    if (p!=NULL) {
        r = p->next;
        while (r!=NULL) {
            free(p);
            p=r;
            r=p->next;
        }
    }
    free(p);
    free(queue);
}

bool IsEmpty(LinkQueue *queue) {
    return (queue->rear == NULL);
}

// EnQueue: Add the element in the end of link
void EnQueue(LinkQueue *&queue, Elem val) {
    QNode *s = (QNode*)malloc(sizeof(QNode));
    s->next = NULL;
    s->val =  val;

    if (IsEmpty(queue)) { 
        queue->front = queue->rear = s;
    } else {
        queue->rear->next = s;
        queue->rear = s;
    }
}

// DeQueue: delete the first element in the link
bool DeQueue(LinkQueue *&queue, Elem &val) {
    QNode *p;
    if (IsEmpty(queue))
        return false;
    else {
        p = queue->front;
        if (p->next==NULL) // if only one element in the queue
            queue->front = queue->rear = NULL;
        else 
            queue->front = p->next;
        val = p->val;
        free(p);
        return true;
    }
}

int main() {
    Elem val;
    LinkQueue *queue;
    InitQueue(queue);
    printf("The queue is empty? \%s \n", IsEmpty(queue)?"yes":"no");
    printf("EnQueue element a,b,c,d \n");
	EnQueue(queue,'a');
	EnQueue(queue,'b');
	EnQueue(queue,'c');
	EnQueue(queue,'d');
    printf("The deQueue sequence is: ");
    while (!IsEmpty(queue)) {
        DeQueue(queue, val);
        printf("%c ", val);
    }
    printf("\n");
    printf("The queue is empty? \%s", IsEmpty(queue)?"yes":"no");
    DestroyQueue(queue);
    return 0;
}