#include <stdio.h>
#include "stack.h"
#include "infix.h"

int precedence(char ch)
{
    if(ch == '^')
        return 3;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

int isOperand(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9'));
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' ||
            ch == '^');
}

int isOpening(char ch)
{
    return (ch == '(' || ch == '{' || ch == '[');
}

int isClosing(char ch)
{
    return (ch == ')' || ch == '}' || ch == ']');
}

int isMatching(char open, char close)
{
    return ((open == '(' && close == ')') ||
            (open == '{' && close == '}') ||
            (open == '[' && close == ']'));
}

int isValid(char infix[])
{
    int i;
    int expectOperand = 1;
    int bracketTop = -1;
    char brackets[MAX];

    for(i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if(isOperand(ch))
        {
            if(expectOperand == 0)
                return 0;

            while(isOperand(infix[i]))
                i++;

            i--;
            expectOperand = 0;
        }
        else if(isOpening(ch))
        {
            if(expectOperand == 0 || bracketTop == MAX - 1)
                return 0;

            brackets[++bracketTop] = ch;
        }
        else if(isClosing(ch))
        {
            if(expectOperand == 1 || bracketTop == -1)
                return 0;

            if(!isMatching(brackets[bracketTop], ch))
                return 0;

            bracketTop--;
            expectOperand = 0;
        }
        else if(isOperator(ch))
        {
            if(expectOperand == 1)
                return 0;

            expectOperand = 1;
        }
        else
        {
            return 0;
        }
    }

    return (expectOperand == 0 && bracketTop == -1);
}

void infixToPostfix(char infix[], char postfix[])
{
    int i, k = 0;

    top = -1;

    for(i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if(isOperand(ch))
        {
            while(isOperand(infix[i]))
            {
                postfix[k++] = infix[i++];
            }

            postfix[k++] = ' ';
            i--;
        }
        else if(isOpening(ch))
        {
            push(ch);
        }
        else if(isClosing(ch))
        {
            while(top != -1 && !isOpening(stack[top]))
            {
                postfix[k++] = pop();
            }

            pop();
        }
        else if(isOperator(ch))
        {
            while(top != -1 &&
                  !isOpening(stack[top]) &&
                  (precedence(stack[top]) >=precedence(ch)&&
                   ch != '^'))
            {
                postfix[k++] = pop();
            }

            push(ch);
        }
    }

    while(top != -1)
    {
        postfix[k++] = pop();
    }

    postfix[k] = '\0';
}
