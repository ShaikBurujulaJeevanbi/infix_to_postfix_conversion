#ifndef INFIX_H
#define INFIX_H

int precedence(char ch);
int isOperand(char ch);
int isOperator(char ch);
int isOpening(char ch);
int isClosing(char ch);
int isMatching(char open, char close);

int isValid(char infix[]);
void infixToPostfix(char infix[], char postfix[]);

#endif
