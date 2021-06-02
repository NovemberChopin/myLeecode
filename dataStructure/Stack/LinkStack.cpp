/**
 * LinkStack
 * Stack empty: stack->next==NULL
 * Push: insert element in the front
 * Pop: delete the first element
 * time: 2021-6-2
 * author: jsfantasy
 */

#include <stdio.h>
#include <stdlib.h>

typedef char Elem;
typedef struct linkNode {
    Elem val;
    struct linkNode *next;
} LinkStack;

void InitStack(LinkStack *&stack) {
    stack = (LinkStack*)malloc(sizeof(LinkStack));
    stack->next = NULL;
}

void DestroyStack(LinkStack *&stack) {
    LinkStack *pre = stack, *p;
    if (pre!=NULL) {
        p = pre->next;
        free(pre);
        pre = p;
    }
    stack = NULL;
}

bool IsEmpty(LinkStack *stack) {
    return (stack->next==NULL);
}

void Push(LinkStack *&stack, Elem val) {
    LinkStack *p=stack, *s;
    s = (LinkStack*)malloc(sizeof(LinkStack));
    s->val = val;
    // insert in the front
    s->next = p->next;
    p->next = s;
}

bool Pop(LinkStack *&stack, Elem &val) {
    LinkStack *s;
    if (IsEmpty(stack))
        return false;
    s = stack->next;
    val = s->val;
    stack->next = s->next;
    free(s);
    return true;
}

void Display(LinkStack *stack) {
    LinkStack *p;
    if (!IsEmpty(stack)) {
        p = stack->next;
        while (p!=NULL) {
            printf("%c ", p->val);
            p = p->next;
        }
        printf("\n");
    }
}


int main() {
    Elem val;
    LinkStack *stack;
    InitStack(stack);
    printf("The stack is empty? \%s \n", IsEmpty(stack)?"yes":"no");
    printf("Push element a,b,c,d,e\n");
	Push(stack,'a');
	Push(stack,'b');
	Push(stack,'c');
	Push(stack,'d');
	Push(stack,'e');
    // Display(stack);
    printf("The stack is empty? \%s \n", IsEmpty(stack)?"yes":"no");
    printf("The pop sequence is: ");
    while (!IsEmpty(stack)) {
        Pop(stack, val);
        printf("%c ", val);
    }
    printf("\n");
    printf("The stack is empty? \%s", IsEmpty(stack)?"yes":"no");
    DestroyStack(stack);
    return 0;
}