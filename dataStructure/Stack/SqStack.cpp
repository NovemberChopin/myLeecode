/**
 * Sequence stack base operation
 * time: 2020-6-2
 */ 

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

typedef char Elem;
typedef struct {
    Elem val[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack *&stack) {
    stack = (SqStack *)malloc(sizeof(SqStack));
    stack->top = -1;
}

void DestroyStack(SqStack *&stack) {
    free(stack);
}

bool IsEmpty(SqStack *stack) {
    return (stack->top == -1);
}

bool IsFull(SqStack *stack) {
    return (stack->top == MaxSize-1);
}

bool Push(SqStack *&stack, Elem val) {
    if (IsFull(stack)) 
        return false;
    stack->top++;
    stack->val[stack->top] = val;
    return true;
}

bool Pop(SqStack *&stack, Elem &val) {
    if (IsEmpty(stack))
        return false;
    val = stack->val[stack->top];
    stack->top--;
    return true;
}


int main() {
    Elem val;
    SqStack *stack;
    InitStack(stack);
    printf("The stack is enpty? \%s", IsEmpty(stack)?"yes":"no");
    printf("Push element a,b,c,d,e\n");
	Push(stack,'a');
	Push(stack,'b');
	Push(stack,'c');
	Push(stack,'d');
	Push(stack,'e');
    printf("The stack is enpty? \%s", IsEmpty(stack)?"yes":"no");
    printf("The pop sequence is: \n");
    while (!IsEmpty(stack)) {
        Pop(stack, val);
        printf("%c ", val);
    }
    printf("\n");
    printf("The stack is enpty? \%s", IsEmpty(stack)?"yes":"no");
    DestroyStack(stack);
    return 0;
}
