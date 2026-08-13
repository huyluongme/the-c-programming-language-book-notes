/*
 * File name:   ex5-2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 13, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-2. Write getfloat, the floating-point analog of getint. What type
 * does getfloat return as its function value?
 *
 * Answer: getfloat returns int.
 * The return value indicates status (EOF, 0 for invalid number, or character read),
 * while the floating-point value is passed back via the pointer argument (float *pn).
 */

#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);
int getfloat(float *);

int main(void)
{
    int n = 0, status;
    float array[SIZE];

    while (n < SIZE && (status = getfloat(&array[n])) != EOF) {
        if (status != 0) {
            n++;
        } else {
            getch(); /* skip invalid character */
        }
    }

    for (int i = 0; i < n; i++)
        printf("%f\n", array[i]);

    return 0;
}

/* getfloat: get next floating-point number from input into *pn */
int getfloat(float *pn)
{
    int c, sign;
    float power;
    int has_digits = 0;

    while (isspace(c = getch())) /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c); /* it is not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    int has_sign = (c == '+' || c == '-');
    int sign_char = c;

    if (has_sign) {
        c = getch();
        if (!isdigit(c) && c != '.') {
            if (c != EOF)
                ungetch(c);
            ungetch(sign_char);
            return 0;
        }
    }

    for (*pn = 0.0f; isdigit(c); c = getch()) {
        *pn = 10.0f * *pn + (c - '0');
        has_digits = 1;
    }

    if (c == '.') {
        int dot_char = c;
        c = getch();
        if (!has_digits && !isdigit(c)) {
            if (c != EOF)
                ungetch(c);
            ungetch(dot_char);
            if (has_sign)
                ungetch(sign_char);
            return 0;
        }
    }

    for (power = 1.0f; isdigit(c); c = getch()) {
        *pn = 10.0f * *pn + (c - '0');
        power *= 10.0f;
    }

    *pn = (*pn * sign) / power;

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
