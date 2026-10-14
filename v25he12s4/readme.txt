INFIX TO POSTFIX CONVERSION USING STACK IN C
================================================

1. PROJECT OVERVIEW
-------------------
This project converts a valid arithmetic expression from infix notation to
postfix notation using a stack.

Infix notation places an operator between operands.
Example: a+b

Postfix notation places an operator after its operands.
Example: ab+

The program first validates the infix expression. If the expression is valid,
it converts the expression to postfix form. Otherwise, it displays an invalid
expression message.


2. PROJECT FILES
----------------
The project contains the following files:

1. main.c
   - Starts the program.
   - Reads the infix expression from the user.
   - Calls isValid() to validate the expression.
   - Calls infixToPostfix() when the expression is valid.
   - Displays the postfix expression.

2. infix.h
   - Contains declarations for infix validation and conversion functions.
   - Declares helper functions for operands, operators, brackets and precedence.

3. infix.c
   - Implements expression validation.
   - Implements operator-precedence rules.
   - Implements infix-to-postfix conversion.
   - Uses stack operations while processing operators and brackets.

4. stack.h
   - Contains declarations for stack operations.
   - Provides the stack interface used by infix.c.

5. stack.c
   - Implements the stack using an array.
   - Stores operators and opening brackets temporarily.
   - Implements operations such as push, pop, peek and empty-stack checking.

6. Makefile
   - Contains the commands required to compile the complete project.
   - Compiles main.c, infix.c and stack.c.
   - Uses the header dependencies infix.h and stack.h.
   - Produces the executable file a.out.


3. OVERALL PROJECT WORKFLOW
---------------------------
1. The program starts in main.c.
2. Two arrays are created: infix[] and postfix[].
3. The user enters an infix expression.
4. main.c calls isValid(infix).
5. isValid() checks:
   - Whether every character is supported.
   - Whether operands and operators appear in a valid order.
   - Whether opening and closing brackets match.
   - Whether the expression starts and ends correctly.
6. If validation fails, the program prints:

   Invalid infix expression

7. If validation succeeds, main.c calls:

   infixToPostfix(infix, postfix)

8. The conversion function scans the expression from left to right.
9. Operands are copied directly to the postfix expression.
10. Opening brackets are pushed onto the stack.
11. Operators are pushed or popped according to precedence and associativity.
12. When a closing bracket is found, operators are popped until the matching
    opening bracket is reached.
13. After the complete expression is scanned, all remaining operators are
    popped from the stack.
14. The postfix string is terminated with '\0'.
15. Control returns to main.c.
16. main.c displays the final postfix expression.


4. INFIX-TO-POSTFIX ALGORITHM
-----------------------------
1. Initialize an empty stack.
2. Initialize an empty postfix expression.
3. Scan the infix expression from left to right.
4. If the current character is an operand:
   - Append it directly to postfix.
5. If the current character is an opening bracket:
   - Push it onto the stack.
6. If the current character is a closing bracket:
   - Pop operators from the stack and append them to postfix until the
     matching opening bracket is found.
   - Remove the opening bracket without adding it to postfix.
7. If the current character is an operator:
   - Compare its precedence with the operator at the top of the stack.
   - Pop operators that have higher precedence.
   - Pop operators of equal precedence when required by associativity.
   - Append every popped operator to postfix.
   - Push the current operator onto the stack.
8. After scanning the complete expression:
   - Pop all remaining operators and append them to postfix.
9. Add '\0' at the end of the postfix expression.
10. Display the result.


5. OPERATOR PRECEDENCE
----------------------
Highest : ^
Medium  : *, /, %
Lowest  : +, -

The exponent operator ^ is normally right-associative.
The operators *, /, %, + and - are left-associative.
Parentheses control grouping but are not included in the postfix output.


6. WORKFLOW EXAMPLE
-------------------
Input infix expression:

a^b+b-d/f

Expected postfix expression:

ab^b+df/-

Step-by-step processing:

Step  Symbol  Action                                      Stack     Postfix
----  ------  ------------------------------------------  --------  ----------
1     a       Operand: append directly to postfix         Empty     a
2     ^       Operator: push onto stack                   ^         a
3     b       Operand: append directly to postfix         ^         ab
4     +       Pop ^ because it has higher precedence.     +         ab^
              Append ^ to postfix, and then push +.
5     b       Operand: append directly to postfix         +         ab^b
6     -       Pop + because it has equal precedence       -         ab^b+
              and is left-associative. Then push -.
7     d       Operand: append directly to postfix         -         ab^b+d
8     /       / has higher precedence than -, so push it. - /       ab^b+d
9     f       Operand: append directly to postfix         - /       ab^b+df
10    End     Pop / and then - into postfix.              Empty     ab^b+df/-

Final conversion:

Infix   : a^b+b-d/f
Postfix : ab^b+df/-

Explanation:
- a^b is processed first because ^ has the highest precedence.
- The next operand b is added to the result of a^b.
- d/f is processed before subtraction because / has higher precedence than -.
- Finally, the result of d/f is subtracted.

The expression is therefore grouped logically as:

(a^b + b) - (d/f)


7. FILE-TO-FILE CALL FLOW
-------------------------
main.c
  |
  +-- isValid() ------------------------> infix.c
  |
  +-- infixToPostfix() -----------------> infix.c
                                              |
                                              +-- Stack operations
                                                     |
                                                     v
                                                  stack.c

The function declarations are provided through infix.h and stack.h.


8. CREATE THE MAKEFILE BEFORE COMPILATION
----------------------------------------
Before compiling or running the program, create a file named Makefile in the
same folder as all five project files. The Makefile is then used to compile the
complete project without manually typing the gcc command every time.

The Makefile knows the project source files and header dependencies:

Source files:
- main.c
- infix.c
- stack.c

Header files:
- infix.h
- stack.h

Build file:
- Makefile

Generated executable:
- a.out

Suggested Makefile content:

CC = gcc
TARGET = a.out
OBJECTS = main.o infix.o stack.o

a.out: main.o stack.o infix.o
	gcc main.o stack.o infix.o

main.o: main.c stack.h infix.h
	gcc -c main.c

stack.o: stack.c stack.h
	gcc -c stack.c

infix.o: infix.c infix.h stack.h
	gcc -c infix.c
Required order:
1. Place main.c, infix.h, infix.c, stack.h and stack.c in one folder.
2. Create and save the Makefile shown above in the same folder.
3. Run make to compile the project.
4. Run ./a.out to execute the program.

How the Makefile works:
1. make reads the Makefile.
2. main.c is compiled into main.o.
3. infix.c is compiled into infix.o.
4. stack.c is compiled into stack.o.
5. The object files are linked together.
6. The final executable is created as a.out.
7. If only one source file changes, make recompiles the required file and then
   links the project again.
8. make clean removes the object files and a.out.

Important:
The command lines below each Makefile target must begin with a TAB character,
not spaces.


9. COMPILATION AND EXECUTION AFTER CREATING MAKEFILE
---------------------------------------------------
After creating the Makefile, confirm that these files are in the same project
folder:

main.c
infix.h
infix.c
stack.h
stack.c
Makefile

Compile the project:

make

Run the program:

./a.out

Example execution:

Enter infix expression: a^b+b-d/f
Postfix = ab^b+df/-


10. COMPLEXITY
--------------
Time Complexity  : O(n)
Space Complexity : O(n)

Each input character is scanned once. Each operator is pushed onto and popped
from the stack at most once. The stack and postfix output can grow according
to the length of the input expression.


11. CONCLUSION
--------------
This project demonstrates how a stack converts an infix expression into
postfix form. The file structure separates user interaction, expression
validation, conversion logic and stack operations. The Makefile manages the
compilation dependencies and creates a.out using all required source files.
This modular organization makes the project easier to understand, compile,
test and maintain.
