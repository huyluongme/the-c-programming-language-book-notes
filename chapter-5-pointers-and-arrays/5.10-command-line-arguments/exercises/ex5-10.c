/*
 * File name:   ex5-10.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Sep 6, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a separate
 * argument. For example, expr 2 3 4 + * evaluates 2 * (3+4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXVAL  100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp >= MAXVAL)
        printf("error: stack full\n");
    else
        val[sp++] = f;
}

double pop(void)
{
    if (sp <= 0) {
        printf("error: stack empty\n");
        return 0;
    }

    return val[--sp];
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: expr <expression>\n");
        return 1;
    }

    while (--argc > 0) {
        char *arg = *++argv;
        if (arg[1] == '\0' && (arg[0] == '+' || arg[0] == '-' || arg[0] == '*' || arg[0] == '/')) {
            double op2 = pop();
            double op1 = pop();

            switch (arg[0]) {
                case '+':
                    push(op1 + op2);
                    break;
                case '-':
                    push(op1 - op2);
                    break;
                case '*':
                    push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) {
                        printf("error: division by zero\n");
                        return 1;
                    }
                    push(op1 / op2);
                    break;
            }
        }
        else
            push(atof(arg));
    }

    printf("Result: %.8g\n", pop());
    return 0;
}
