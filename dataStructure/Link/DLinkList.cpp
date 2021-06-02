#include <stdio.h>
#include <stdlib.h>

typedef char Elem;
typedef struct DNode {
    Elem date;
    struct DNode * prior;
    struct DNode * rear;
}DLinkList;


void InitList(DLinkList *&L) {
    L = (DLinkList*)malloc(sizeof(DLinkList));
    L->prior = L->rear = NULL;
}

void CreateListF(DLinkList *&L, Elem a[], int n) {
    DLinkList *s;
    int i = 0;
    for (i = 0; i < n; i++) {
        s = (DLinkList*)malloc(sizeof(DLinkList));
        s->date = a[i];
        s->rear = L->rear;
        if (L->rear!=NULL)
            L->rear->prior = s;
        L->rear = s;
        s->prior = L;
    }
}

void CreateListR(DLinkList *&L, Elem a[], int n) {
    DLinkList *p = L, *s;
    int i = 0;
    for (i = 0; i < n; i++) {
        s = (DLinkList*)malloc(sizeof(DLinkList));
        s->date = a[i];
        p->rear = s;
        s->prior = p;
        p = s;
    }
    p->rear = NULL;
}

bool InsertElem(DLinkList *&L, int index, Elem data) {
    DLinkList *p, *s;
    int i = 0;
    p = L;
    while (i < index-1 && p!=NULL) {
        p = p->rear;
        i++;
    }
    if (p==NULL) {
        return false;
    } else {
        s = (DLinkList*)malloc(sizeof(DLinkList));
        s->date = data;
        s->rear = p->rear;
        if (p->rear!=NULL)
            p->rear->prior = s;
        p->rear = s;
        s->prior = p;
        return true;
    }
}

bool DeleteElem(DLinkList *&L, int index, Elem &data) {
    DLinkList *p, *s;
    int i = 0;
    p = L;
    while (i < index-1 && p!=NULL) {
        p = p->rear;
        i++;
    }
    if (p==NULL) {
        return false;
    } else {
        s = p->rear;
        if (s==NULL) return false;
        data = s->date;
        p->rear = s->rear;
        if (s->rear!=NULL) {
            s->rear->prior = p;
        }
        return true;
    }
}

void Traverse(DLinkList *L) {
    DLinkList *p = L->rear;
    if (p->rear == NULL)
        printf("The link is empty!\n");
    else {
        while (p) {
            printf("%c ", p->date);
            p = p->rear;
        }
        printf("\n");
    }
}


int main() {
    DLinkList *list;
    InitList(list);
    
    // Elem str[] = {'a', 'b', 'c', 'd', 'e'};
    // CreateListR(list, str, 5);

    InsertElem(list, 1, 'a');
    InsertElem(list, 2, 'd');
    InsertElem(list, 3, 'c');
    InsertElem(list, 4, 'b');
    InsertElem(list, 5, 'e');
    Traverse(list);
    Elem data;
    DeleteElem(list, 5, data);
    printf("The delete element is: %c\n", data);
    DeleteElem(list, 2, data);
    printf("The delete element is: %c\n", data);
    Traverse(list);
    return 0;
}