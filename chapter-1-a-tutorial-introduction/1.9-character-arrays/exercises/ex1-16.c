/*
 * File name:   ex1-16.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-16. Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrary long input lines, and as much as
 * possible of the text.
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getLine(char line[], int maxline);
void copy(char to[], char from[]);

/* print the length of arbitrary long input lines,
   and as much as possible of the text. */
int main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while((len = getLine(line, MAXLINE)) > 0)
        if(len > max) {
            max = len;
            copy(longest, line);
        }
    if(max > 0)
        printf("len: %d - string: %s", max, longest);
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
    else
        while((c = getchar()) != EOF && c != '\n')
            ++i;

    if(i < lim)
        s[i] = '\0';
    else
        s[lim - 1] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}
