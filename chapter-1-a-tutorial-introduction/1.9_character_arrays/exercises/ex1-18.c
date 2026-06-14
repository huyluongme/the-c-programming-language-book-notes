/*
 * File name:   ex1-18.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-18. Write a program to remove trailing blanks and tabs
 * from each line of input, and to delete entirely blank lines.
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getLine(char line[], int maxline);

/* remove trailing blanks and tabs, and delete entirely blank lines */
int main()
{
    int len;
    char line[MAXLINE];

    while((len = getLine(line, MAXLINE)) > 0) {
        int i = len - 1;

        /* Skip trailing newline if it exists */
        if (i >= 0 && line[i] == '\n') {
            i--;
        }

        /* Strip trailing spaces and tabs */
        while (i >= 0 && (line[i] == ' ' || line[i] == '\t')) {
            --i;
        }

        /* If the line has content (not completely blank), print it */
        if (i >= 0) {
            if (line[len - 1] == '\n') {
                line[i + 1] = '\n';
                line[i + 2] = '\0';
            } else {
                line[i + 1] = '\0';
            }
            printf("%s", line);
        }
    }
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
