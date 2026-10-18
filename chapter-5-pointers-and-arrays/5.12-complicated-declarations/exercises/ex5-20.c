/*
 * File name:   ex5-20.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Oct 18, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-20. Expand dcl to handle declarations with function
 * argument types, qualifiers like const, and so on.
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100
#define MAXOUT      1000
#define MAXPTR      20      /* max number of *'s in one declarator */

#define QCONST      1       /* qualifier flags of a pointer */
#define QVOLATILE   2

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
void specifiers(void);
void parmlist(void);
void errmsg(char *);
int inlist(char *, char *[]);

int gettoken(void);
void ungettoken(void);
int getch(void);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = unsigned long, const char, etc. */
char out[MAXOUT];
int errflag;                /* set when the current line has an error */
int absok;                  /* 1 while parsing a parameter: name is optional */
int backtoken;              /* 1 if the last token was pushed back */

char *quals[]   = { "const", "volatile", NULL };
char *storage[] = { "auto", "extern", "register", "static", NULL };
char *types[]   = { "void", "char", "short", "int", "long", "float",
                    "double", "signed", "unsigned", NULL };
char *tags[]    = { "struct", "union", "enum", NULL };

int main()  /* convert declaration to words */
{
    while (gettoken() != EOF) {     /* 1st token on line */
        if (tokentype == '\n')      /* blank line */
            continue;

        errflag = 0;                /* start every line from a clean state */
        absok = 0;
        backtoken = 0;
        name[0] = '\0';
        out[0] = '\0';

        if (tokentype != NAME)
            errmsg("expected data type");
        else {
            specifiers();           /* datatype: const char, unsigned int... */

            if (!errflag)
                dcl();              /* parse rest of line */

            if (!errflag && tokentype != '\n' && tokentype != EOF)
                errmsg("syntax error");
        }

        if (errflag) {
            /* recover: discard the rest of the bad line */
            backtoken = 0;

            while (tokentype != '\n' && tokentype != EOF)
                tokentype = getch();
        }
        else
            printf("%s:%s %s\n", name, out, datatype);
    }

    return 0;
}

/* errmsg: report an error and mark the current line as bad */
void errmsg(char *msg)
{
    printf("error: %s\n", msg);
    errflag = 1;
}

/* inlist: is s one of the strings in the NULL-terminated table list? */
int inlist(char *s, char *list[])
{
    for ( ; *list != NULL; list++)
        if (strcmp(s, *list) == 0)
            return 1;

    return 0;
}

/* addword: append a word to datatype */
void addword(char *w)
{
    if (datatype[0] != '\0')
        strcat(datatype, " ");

    strcat(datatype, w);
}

/* specifiers: read the declaration specifiers (type words, qualifiers such
 * as const, storage classes, struct tags) into datatype. The current token
 * is the first one; the token after the last specifier is pushed back. */
void specifiers(void)
{
    int havetype = 0;       /* seen a type word (int, struct x, a typedef name) */

    datatype[0] = '\0';

    while (tokentype == NAME) {
        if (inlist(token, quals) || inlist(token, storage))
            ;
        else if (inlist(token, types))
            havetype = 1;
        else if (inlist(token, tags)) {
            addword(token);

            if (gettoken() != NAME) {
                errmsg("expected tag name");
                return;
            }

            havetype = 1;
        }
        else if (!havetype)         /* a typedef name, like size_t */
            havetype = 1;
        else                        /* second plain name: the declarator's */
            break;

        addword(token);
        gettoken();
    }

    if (!havetype) {
        errmsg("expected data type");
        return;
    }

    ungettoken();
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns, i;
    int ptrq[MAXPTR];       /* qualifiers (const, volatile) of each * */

    for (ns = 0; ; ) {      /* count *`s and the qualifiers after them */
        gettoken();

        if (tokentype == '*') {
            if (ns >= MAXPTR) {
                errmsg("too many *");
                return;
            }

            ptrq[ns++] = 0;
        }
        else if (ns > 0 && tokentype == NAME && inlist(token, quals))
            ptrq[ns - 1] |= (strcmp(token, "const") == 0) ? QCONST : QVOLATILE;
        else
            break;
    }

    dirdcl();

    /* the * closest to the name is read first */
    for (i = ns - 1; i >= 0; i--) {
        if (ptrq[i] & QCONST)
            strcat(out, " const");

        if (ptrq[i] & QVOLATILE)
            strcat(out, " volatile");

        strcat(out, " pointer to");
    }
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
    else if (absok)             /* unnamed parameter, like int * */
        ungettoken();
    else {
        errmsg("expected name or (dcl)");
        return;
    }

    while (!errflag && ((type = gettoken()) == PARENS || type == BRACKETS
                                                      || type == '('))
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(')
            parmlist();
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

/* parmlist: parse a parameter list (the '(' is already read) and add
 * " function taking (...) returning" to out. Each parameter is itself a
 * declaration, so out, name and datatype are saved and restored around it. */
void parmlist(void)
{
    char outer[MAXOUT], outername[MAXTOKEN], outertype[MAXTOKEN];
    char list[MAXOUT], desc[MAXOUT + MAXTOKEN + 2];
    char *p;
    int outerabs;

    strcpy(outer, out);
    strcpy(outername, name);
    strcpy(outertype, datatype);
    outerabs = absok;

    absok = 1;
    list[0] = '\0';

    gettoken();

    if (tokentype != ')') {             /* "( )" is an empty list */
        for ( ; ; ) {
            if (tokentype == '.') {     /* ... */
                if (getch() != '.' || getch() != '.') {
                    errmsg("expected ...");
                    break;
                }

                strcat(list, "...");
                gettoken();
            }
            else if (tokentype != NAME) {
                errmsg("expected parameter type");
                break;
            }
            else {
                out[0] = '\0';
                name[0] = '\0';

                specifiers();

                if (!errflag)
                    dcl();

                if (errflag)
                    break;

                sprintf(desc, "%s %s", out, datatype);

                for (p = desc; *p == ' '; p++)
                    ;

                if (name[0] != '\0') {
                    strcat(list, name);
                    strcat(list, ": ");
                }

                strcat(list, p);
            }

            if (tokentype != ',')
                break;

            strcat(list, ", ");
            gettoken();
        }

        if (!errflag && tokentype != ')')
            errmsg("missing ) in parameter list");
    }

    strcpy(out, outer);
    strcpy(name, outername);
    strcpy(datatype, outertype);
    absok = outerabs;

    if (!errflag) {
        if (list[0] == '\0')
            strcat(out, " function returning");
        else {
            strcat(out, " function taking (");
            strcat(out, list);
            strcat(out, ") returning");
        }
    }
}

void ungetch(int);

int gettoken(void)  /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (backtoken) {                /* hand out the pushed-back token */
        backtoken = 0;
        return tokentype;
    }

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
    else if (isalpha(c) || c == '_') {
        for (*p++ = c; isalnum(c = getch()) || c == '_'; )
            *p++ = c;

        *p = '\0';
        ungetch(c);

        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

/* ungettoken: the next gettoken returns the current token again */
void ungettoken(void)
{
    backtoken = 1;
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
