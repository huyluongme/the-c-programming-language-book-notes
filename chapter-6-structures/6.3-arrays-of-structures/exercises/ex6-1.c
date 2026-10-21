/*
 * File name:   ex6-1.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Oct 21, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 6-1. Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines.
 * Write a better version.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    { "auto",     0 },
    { "break",    0 },
    { "case",     0 },
    { "char",     0 },
    { "const",    0 },
    { "continue", 0 },
    { "default",  0 },
    { "do",       0 },
    { "double",   0 },
    { "else",     0 },
    { "enum",     0 },
    { "extern",   0 },
    { "float",    0 },
    { "for",      0 },
    { "goto",     0 },
    { "if",       0 },
    { "int",      0 },
    { "long",     0 },
    { "register", 0 },
    { "return",   0 },
    { "short",    0 },
    { "signed",   0 },
    { "sizeof",   0 },
    { "static",   0 },
    { "struct",   0 },
    { "switch",   0 },
    { "typedef",  0 },
    { "union",    0 },
    { "unsigned", 0 },
    { "void",     0 },
    { "volatile", 0 },
    { "while",    0 }
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

int getword(char *word, int lim);
void skipcomment(void);
void skipquote(int quote);
void skipline(void);
int binsearch(char *word, struct key tab[], int n);

int getch(void);
void ungetch(int c);

/* count C keywords */
int main(void)
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;

    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;

        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

/*
 * getword: get next word or character from input;
 * skips comments, string and character constants, and preprocessor lines
 */
int getword(char *word, int lim)
{
    static int bol = 1;     /* 1 if only blanks seen so far on this line */
    int c, d;
    char *w = word;

    for (;;) {
        while (isspace(c = getch()))
            if (c == '\n')
                bol = 1;

        if (c == '#' && bol) {
            skipline();
            bol = 1;
            continue;
        }

        if (c == '/') {
            if ((d = getch()) == '*') {
                skipcomment();
                continue;
            } else if (d == '/') {
                skipline();
                bol = 1;
                continue;
            }
            ungetch(d);
        }

        bol = 0;

        if (c == '"' || c == '\'') {
            skipquote(c);
            continue;
        }

        break;
    }

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 1; w++) {
        c = getch();
        if (!isalnum(c) && c != '_') {
            ungetch(c);
            break;
        }
        *w = c;
    }

    *w = '\0';

    return word[0];
}


/* skipcomment: discard the rest of a comment, up to its closing delimiter */
void skipcomment(void)
{
    int c, prev = 0;

    while ((c = getch()) != EOF && !(prev == '*' && c == '/'))
        prev = c;
}


/* skipquote: discard the rest of a string or character constant */
void skipquote(int quote)
{
    int c;

    while ((c = getch()) != EOF && c != quote)
        if (c == '\\')
            getch();
}


/* skipline: discard the rest of the line; a backslash continues the line */
void skipline(void)
{
    int c;

    while ((c = getch()) != EOF && c != '\n')
        if (c == '\\')
            getch();
}


/*
 * Input buffer used by getch/ungetch.
 * These functions come from Chapter 4.
 */
char buf[BUFSIZE];
int bufp = 0;


/* getch: get a possibly pushed-back character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/* ungetch: push character back on input */
void ungetch(int c)
{
    if (c == EOF)
        return;

    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
