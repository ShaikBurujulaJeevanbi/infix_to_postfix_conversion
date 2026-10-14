a.out: main.o stack.o infix.o
	gcc main.o stack.o infix.o

main.o: main.c stack.h infix.h
	gcc -c main.c

stack.o: stack.c stack.h
	gcc -c stack.c

infix.o: infix.c infix.h stack.h
	gcc -c infix1.c
