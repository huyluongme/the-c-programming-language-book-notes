/*
 * File name:   ex4-10.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 26, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 4-10. An alternate organization uses getline to read an entire input line;
 * this makes getch and ungetch unnecessary. Revise the calculator to use this approach.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* for atof() */
#include <math.h>   /* for fmod() */
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that the number was found */
#define NAME    'n' /* signal that the name was found */
#define MAXLINE 1000

double variables[26]; /* array to store the 26 variables */
double lastValue;
int var = 0;

char line[MAXLINE]; /* line buffer to hold input line */
int li = 0;         /* current index in line */

int getLine(char [], int);
int getop(char []);
void push(double);
double pop(void);
void top(void);
void duplicate(void);
void swap(void);
void clear(void);

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;

            case 't':
                top();
                break;
            case 'd':
                duplicate();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear();
                break;
            case NAME:
                if (strcmp(s, "sin") == 0)
                    push(sin(pop()));
                else if (strcmp(s, "cos") == 0)
                    push(cos(pop()));
                else if (strcmp(s, "tan") == 0)
                    push(tan(pop()));
                else if (strcmp(s, "exp") == 0)
                    push(exp(pop()));
                else if (strcmp(s, "log") == 0)
                    push(log(pop()));
                else if (strcmp(s, "log10") == 0)
                    push(log10(pop()));
                else if (strcmp(s, "sqrt") == 0)
                    push(sqrt(pop()));
                else if (strcmp(s, "pow") == 0) {
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else
                    printf("error: unknown command %s\n", s);
                break;
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                var = type - 'A';
                push(variables[var]);
                break;
            case '=':
                pop();
                variables[var] = pop();
                push(variables[var]);
                break;
            case '\n':
                lastValue = pop();
                printf("\t%.8g\n", lastValue);
                break;
            case '#':
                push(lastValue);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

#define MAXVAL  100 /* maximum depth of val stack */

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* top: print top value of stack without popping */
void top(void)
{
    if (sp > 0)
        printf("\t%.8g\n", val[sp - 1]);
    else
        printf("error: stack empty\n");
}

/* duplicate: duplicate top value of stack */
void duplicate(void)
{
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("error: stack empty\n");
}

/* swap: swap top two values of stack */
void swap(void)
{
    if (sp > 1) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    }
    else
        printf("error: stack has less than two values\n");
}

/* clear: clear the stack */
void clear(void)
{
    sp = 0;
}

/* getLine: read a line into s, return length */
int getLine(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* getop: get next character or numeric operand from line buffer */
int getop(char s[])
{
    int i, c;

    if (line[li] == '\0') {
        if (getLine(line, MAXLINE) == 0)
            return EOF;
        li = 0;
    }

    while ((s[0] = c = line[li++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (isalpha(c)) {
        while (isalnum(s[++i] = c = line[li++]))
            ;
        s[i] = '\0';
        if (c != '\0')
            li--;

        if (strlen(s) > 1)
            return NAME;
        else
            return s[0];
    }

    if (!isdigit(c) && c != '.') {
        if (c == '-') {
            int next = line[li];
            if (isdigit(next) || next == '.') {
                s[1] = c = line[li++];
                i = 1;
            } else {
                return '-';
            }
        } else {
            return c;
        }
    } else {
        i = 0;
    }

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = line[li++]))
            ;

    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = line[li++]))
            ;

    s[i] = '\0';

    if (c != '\0')
        li--;

    return NUMBER;
}
