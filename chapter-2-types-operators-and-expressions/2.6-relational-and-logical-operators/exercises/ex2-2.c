/*
 * File name:   ex2-2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 22, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-2. Write a loop equivalent to the for loop above without && or ||
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getLine(char line[], int maxline);

int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getLine(line, MAXLINE)) > 0)
        printf("%s", line);

    return 0;
}

/* getLine: read a line into s, return length */
int getLine(char s[], int lim)
{
    int c, i;
    int ok = 1;

    i = 0;
    while (ok) {
        if (i >= lim - 1)
            ok = 0;
        else if ((c = getchar()) == EOF)
            ok = 0;
        else if (c == '\n')
            ok = 0;
        else {
            s[i] = c;
            ++i;
        }
    }

    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    else
        while((c = getchar()) != EOF && c != '\n')
            ++i;

    if(i < lim)
        s[i] = '\0';
    else
        s[lim - 1] = '\0';
    return i;
}
