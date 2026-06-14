/*
 * File name:   ex1-23.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 15, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-23. Write a program to remove all comments from a C program.
 * Don't forget to handle quotes strings and character constants properly.
 * C comments don't nest.
 */

#include <stdio.h>

void rcomment(int c);
void in_comment(void);
void in_single_comment(void);
void echo_quote(int c);

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        rcomment(c);
    }
    return 0;
}

/* rcomment: read and handle characters in normal state */
void rcomment(int c)
{
    int d;

    if (c == '/') {
        if ((d = getchar()) == '*') {
            in_comment(); /* inside a multi-line comment */
        } else if (d == '/') {
            in_single_comment(); /* inside a single-line comment */
        } else {
            putchar(c); /* print '/' and the character that followed it */
            if (d != EOF) {
                putchar(d);
            }
        }
    } else if (c == '\'' || c == '"') {
        echo_quote(c); /* inside a quoted string or character constant */
    } else {
        putchar(c);
    }
}

/* in_comment: skip inside a multi-line comment */
void in_comment(void)
{
    int c, d;

    c = getchar();
    d = getchar();
    while (c != '*' || d != '/') {
        c = d;
        d = getchar();
        if (d == EOF) {
            break;
        }
    }
}

/* in_single_comment: skip inside a single-line comment // ... */
void in_single_comment(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        ; /* discard everything until newline or EOF */
    }
    if (c == '\n') {
        putchar(c); /* preserve the newline character */
    }
}

/* echo_quote: print quoted strings/characters, handling escape sequences */
void echo_quote(int c)
{
    int d;

    putchar(c); /* print the opening quote */
    while ((d = getchar()) != c && d != EOF) {
        putchar(d);
        if (d == '\\') {
            int escaped = getchar();
            if (escaped != EOF) {
                putchar(escaped);
            }
        }
    }
    if (d == c) {
        putchar(d); /* print the closing quote */
    }
}
