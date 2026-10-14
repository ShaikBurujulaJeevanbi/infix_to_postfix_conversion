#include <stdio.h>
#include "infix.h"
#define MAX 100
int main()
{
    char infix[MAX];
    char postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    if(isValid(infix))
    {
        infixToPostfix(infix, postfix);
        printf("Postfix = %s\n", postfix);
    }
    else
    {
        printf("Invalid infix expression\n");
    }

    return 0;
}
