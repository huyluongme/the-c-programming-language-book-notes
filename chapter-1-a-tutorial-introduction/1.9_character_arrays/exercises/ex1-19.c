/*
 * File name:   ex1-19.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-19. Write a function reverse(s) that reverses the characters
 * string s. Use it to write a program that reverses its input a line at a time
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int getLine(char line[], int maxline);
void reverse(char s[]);

/* print longest input line */
int main()
{
    int len;
    char line[MAXLINE];

    while((len = getLine(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
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

/* reverse: reverse the character string s */
void reverse(char s[])
{
    int i, len = 0;
    while(s[len] != '\0')
        ++len;

    int end = len - 1;
    if (end >= 0 && s[end] == '\n') {
        end--;
    }

    for(i = 0; i < end; ++i, --end) {
        char tmp = s[i];
        s[i] = s[end];
        s[end] = tmp;
    }
}
