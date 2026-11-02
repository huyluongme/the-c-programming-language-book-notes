/*
 * File name:   ex6-2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Nov 02, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 6-2. Write a program that reads a C program and prints
 * in alphabetical order each group of variable names that are identical
 *in the first 6 characters, but different somewhere thereafter.
 * Don't count words within strings and comments. Make 6 a parameter that can be
 * set from the command line.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define DEFAULT_LEN 6   /* default number of leading characters to compare */

struct tnode {              /* the tree node */
    char *word;             /* points to the text */
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};

/* C keywords, in sorted order; they are not variable names */
char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while"
};

#define NKEYS (sizeof keywords / sizeof keywords[0])

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *dupstr(char *);
int iskeyword(char *);
void groupprint(struct tnode *, int);
int getword(char *, int);
void skipquote(int);
void skipcomment(void);
void skipline(void);

int getch(void);
void ungetch(int c);

/* print groups of variable names identical in the first n characters */
int main(int argc, char *argv[])
{
    struct tnode *root;
    char word[MAXWORD];
    int n = DEFAULT_LEN;

    if (argc > 2 || (argc == 2 && (n = atoi(argv[1])) <= 0)) {
        fprintf(stderr, "usage: %s [n]\n", argv[0]);
        return 1;
    }

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if ((isalpha(word[0]) || word[0] == '_') && !iskeyword(word))
            root = addtree(root, word);
    groupprint(root, n);
    return 0;
}

/* addtree: add a node with w, at or below p; duplicates are ignored */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();
        p->word = dupstr(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) < 0)
        p->left = addtree(p->left, w);
    else if (cond > 0)
        p->right = addtree(p->right, w);
    return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* dupstr: make a duplicate of s */
char *dupstr(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);   /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* iskeyword: binary search for word in keywords; 1 if found */
int iskeyword(char *word)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = NKEYS - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, keywords[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return 1;
    }
    return 0;
}

/*
 * groupprint: in-order walk of tree p. Names that share their first n
 * characters are neighbours in sorted order, so it is enough to compare
 * each name with the one visited just before it.
 */
void groupprint(struct tnode *p, int n)
{
    static char *prev = NULL;   /* name visited before p */
    static int ingroup = 0;     /* prev has already been printed */
    static int ngroups = 0;

    if (p == NULL)
        return;
    groupprint(p->left, n);
    if (prev != NULL && strncmp(prev, p->word, n) == 0) {
        if (!ingroup) {         /* a new group starts at prev */
            if (ngroups++ > 0)
                putchar('\n');
            printf("%s\n", prev);
            ingroup = 1;
        }
        printf("%s\n", p->word);
    } else
        ingroup = 0;
    prev = p->word;
    groupprint(p->right, n);
}

/*
 * getword: get next identifier or character from input, skipping
 * comments, string literals and character constants
 */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    for (;;) {
        while (isspace(c = getch()))
            ;
        if (c == '"' || c == '\'')
            skipquote(c);
        else if (c == '/') {
            if ((d = getch()) == '*')
                skipcomment();
            else if (d == '/')
                skipline();
            else {
                ungetch(d);
                break;
            }
        } else
            break;
    }

    if (c != EOF)
        *w++ = c;

    if (isdigit(c)) {           /* a number such as 0x1F or 1e5 */
        while (isalnum(d = getch()))
            ;
        ungetch(d);
        *w = '\0';
        return c;
    }

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        d = getch();
        if (!isalnum(d) && d != '_') {
            ungetch(d);
            break;
        }
        *w = d;
    }

    *w = '\0';

    return word[0];
}

/* skipquote: skip to the closing quote of a string or character constant */
void skipquote(int quote)
{
    int c;

    while ((c = getch()) != EOF && c != quote)
        if (c == '\\')
            getch();            /* skip the escaped character */
}

/* skipcomment: skip to the end of a block comment */
void skipcomment(void)
{
    int c;

    while ((c = getch()) != EOF)
        if (c == '*') {
            while ((c = getch()) == '*')
                ;
            if (c == '/' || c == EOF)
                return;
        }
}

/* skipline: skip to the end of a // comment */
void skipline(void)
{
    int c;

    while ((c = getch()) != EOF && c != '\n')
        ;
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
