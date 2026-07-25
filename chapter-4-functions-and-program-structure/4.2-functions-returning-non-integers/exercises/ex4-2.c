/*
 * File name:   ex4-2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 25, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 4-2. Extend atof to handle scientific notation of the form
 * 123.45e-6 where a floating-point number may be followed by e or E and an
 * optional signed exponent.
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int getLine(char s[], int lim);
double atof(char s[]);

int main()
{
    double sum;
    char line[MAXLINE];

    sum = 0;
    while (getLine(line, MAXLINE) > 0) {
        printf("\t%g\n", sum += atof(line));
    }

    return 0;
}

/* getLine: get line into s, return length */
int getLine(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign, exp, exp_sign;
    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    val = sign * val / power;
    /* Handle scientific notation (e / E) */
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exp = 0; isdigit(s[i]); i++) {
            exp = 10 * exp + (s[i] - '0');
        }
        if (exp_sign == 1) {
            while (exp-- > 0)
                val *= 10.0;
        } else {
            while (exp-- > 0)
                val /= 10.0;
        }
    }
    return val;
}
