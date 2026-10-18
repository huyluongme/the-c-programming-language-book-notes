/*
 * File name:   ex5-18.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Oct 18, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-18. Make dcl recover from input errors.
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
void errmsg(char *);

int gettoken(void);
int getch(void);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];
int errflag;                /* set when the current line has an error */

int main()  /* convert declaration to words */
{
    while (gettoken() != EOF) {     /* 1st token on line */
        if (tokentype == '\n')      /* blank line */
            continue;

        errflag = 0;                /* start every line from a clean state */
        name[0] = '\0';
        out[0] = '\0';

        if (tokentype != NAME)
            errmsg("expected data type");
        else {
            strcpy(datatype, token);    /* is the datatype */
            dcl();                      /* parse rest of line */

            if (!errflag && tokentype != '\n' && tokentype != EOF)
                errmsg("syntax error");
        }

        if (errflag) {
            /* recover: discard the rest of the bad line */
            while (tokentype != '\n' && tokentype != EOF)
                tokentype = getch();
        }
        else
            printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

/* errmsg: report an error and mark the current line as bad */
void errmsg(char *msg)
{
    printf("error: %s\n", msg);
    errflag = 1;
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; ) /* count *`s */
        ns++;

    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if (errflag)        /* already failed while reading the '*'s */
        return;

    if (tokentype == '(') {             /* ( dcl ) */
        dcl();

        if (errflag)
            return;

        if (tokentype != ')') {
            errmsg("missing )");
            return;
        }
    }
    else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else {
        errmsg("expected name or (dcl)");
        return;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

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
        for (*p++ = c; (c = getch()) != ']' && c != '\n' && c != EOF; )
            *p++ = c;

        if (c != ']') {             /* unterminated [ : stop at end of line */
            *p = '\0';
            errmsg("missing ]");
            return tokentype = c;
        }

        *p++ = c;
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
