/*
 * File name:   ex5-19.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Oct 18, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-19. Modify undcl so that it does not add redundant parentheses
 * to declarations.
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char out[1000];

int main()  /* undcl: convert word descriptions to declarations */
{
    int type;
    int prevtype;           /* type of the token before the current one */
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        prevtype = tokentype;

        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS) {
                /* () and [] bind tighter than *, so "*x" followed by one of
                 * them needs parentheses: (*x)() / (*x)[] */
                if (prevtype == '*') {
                    sprintf(temp, "(%s)", out);
                    strcpy(out, temp);
                }

                strcat(out, token);
            }
            else if (type == '*') {
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
            }
            else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
                printf("invalid input at %s\n", token);

            prevtype = type;
        }

        printf("%s\n", out);
    }

    return 0;
}

int getch(void);
void ungetch(int);

int gettoken(void)  /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;

        *p = '\0';

        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;

        *p = '\0';
        ungetch(c);

        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

#define BUFSIZE 100

int buf[BUFSIZE]; /* buffer for ungetch (int array supports storing EOF / -1) */
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
