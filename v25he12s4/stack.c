#include <stdio.h>
#include "stack.h"

char stack[MAX];
int top = -1;

void push(char data)
{
    if(top == MAX - 1)
    {
        printf("Stack is full\n");
    }
    else
    {
        stack[++top] = data;
    }
}

char pop()
{
    if(top == -1)
    {
        return '\0';
    }

    return stack[top--];
}
