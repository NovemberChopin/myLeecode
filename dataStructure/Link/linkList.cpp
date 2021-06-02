#include <stdio.h>
#include <stdlib.h>

typedef char Elem;
typedef struct LNode {
    Elem date;
    struct LNode * next;
}LinkList;


void InitList(LinkList *&L) {
    L = (LinkList*)malloc(sizeof(LinkList));
    L->next=NULL;
}

void CreateListF(LinkList *&L, Elem a[], int n) {
    LinkList *s;
    int i = 0;
    InitList(L);
    while (i < n) {
        s =  (LinkList *)malloc(sizeof(LinkList));
        s->date = a[i];
        s->next = L->next;
        L->next = s;
        i++;
    }
}

void CreateListR(LinkList *&L, Elem a[], int n) {
    LinkList *r, *s;
    int i  = 0;
    InitList(L);
    r = L;
    while (i < n) {
        s = (LinkList *)malloc(sizeof(LinkList));
        s->date = a[i];
        r->next = s;
        r = s;
        i++;
    }
    r->next = NULL;
}

void DestroyList(LinkList *&L) {
    LinkList *pre=L->next, *s;
    while (pre) {
        s = pre->next;
        free(pre);
        pre = s;
    }
    L->next = NULL;
}

bool IsEmpty(LinkList *L) {
    return (L->next==NULL);
}

int ListLength(LinkList *L) {
    int length;
    LinkList *p = L;
    while (p->next!=NULL) {
        length++;
        p = p->next;
    }
    return length;
}

void Traverse(LinkList *L) {
    LinkList *p=L->next;
    if (p == NULL)
        printf("The link is empty!\n");
    else {
        while (p!=NULL) {
            printf("%c ", p->date);
            p = p->next;
        }
        printf("\n");
    }
}

bool InsertElem(LinkList *&L, int index, Elem data) {
    LinkList *p, *s;
    int i = 0;
    // ------- The process of finding previous nodes -----------
    p = L;
    while (i < index-1 && p!=NULL) {
        p = p->next;
        i++;
    }
    if (p==NULL) {
        return false;
    } else {
    // ----------------------------------------------------------
        s = (LinkList*)malloc(sizeof(LinkList));
        s->date = data;
        s->next = p->next;
        p->next = s;
        return true;
    }
}

bool DeleteElem(LinkList *&L, int index, Elem &data) {
    LinkList *p = L, *s;
    int i = 0;
    while (i < index - 1 && p!=NULL) {
        p = p->next;
        i++;
    }
    if (p==NULL) return false;
    else {
        s = p->next;
        if (s == NULL) return false;
        data = s->date;
        p->next = s->next;
        free(s);
        return true;
    }
}


int main() {
    LinkList *list;

    // Test: create a link list from group
    // int n = 5;
    // char str[] = {'a', 'b', 'c', 'd', 'e'};
    // CreateListR(list, str, 5);

    InitList(list);
    printf("The link is empty: %s\n", IsEmpty(list)?"Yes":"No");
    InsertElem(list, 1, 'a');
    InsertElem(list, 2, 'b');
    InsertElem(list, 3, 'c');
    InsertElem(list, 4, 'd');
    InsertElem(list, 5, 'e');
    printf("The link is empty: %s\n", IsEmpty(list)?"Yes":"No");
    printf("The length of the link is: %d\n", ListLength(list));
    Traverse(list);
    Elem data;
    DeleteElem(list, 3, data);
    Traverse(list);
    printf("The delete element is: %c\n", data);
    printf("The length of the link is: %d\n", ListLength(list));
    DestroyList(list);
    printf("The length of the link is: %d\n", ListLength(list));
    printf("The link is empty: %s\n", IsEmpty(list)?"Yes":"No");
    return 0;
}