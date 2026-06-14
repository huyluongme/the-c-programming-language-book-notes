/*
 * File name:   ex1-17.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-17. Write a program to print all input lines
 * that are longer than 80 characters
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */
#define MAX     80

int getLine(char line[], int maxline);

/* print lines longer than 80 characters */
int main()
{
    int len;
    char line[MAXLINE];

    while((len = getLine(line, MAXLINE)) > 0)
        if(len > MAX)
            printf("%s", line);
    return 0;
}

/* getLine: read a line into s, return length */
int getLine(char s[], int lim)
{
    int c, i;

    for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if(c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
