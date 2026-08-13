/*
 * File name:   ex5-1.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 13, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-1. As written, getint treats a + or - not followed by a
 * digit as a valid representation of zero. Fit it to push such a character
 * back on the input.
 */

#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);
int getint(int *);

int main(void)
{
    int n, array[SIZE];

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;

    for (int i = 0; i < n; i++)
        printf("%d\n", array[i]);

    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int d = getch();
        if (!isdigit(d)) {
            if (d != EOF)
                ungetch(d);
            ungetch(c);
            return 0;
        }
        c = d;
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

/* getch: get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back onto input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
