#ifndef STACK_H
#define STACK_H

#define MAX 100

extern char stack[MAX];
extern int top;

void push(char data);
char pop();

#endif
