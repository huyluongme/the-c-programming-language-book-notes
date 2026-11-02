/*
 * File name:   ex6-4.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Nov 02, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 6-4. Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence.
 * Precede each word by its count.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct tnode {              /* the tree node */
    char *word;             /* points to the text */
    int count;              /* number of occurrences */
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
char *dupstr(char *);
int treecount(struct tnode *);
int treefill(struct tnode *, struct tnode *[], int);
int cmpcount(const void *, const void *);
int getword(char *, int);

int getch(void);
void ungetch(int c);

/* print the distinct words in decreasing order of frequency */
int main(void)
{
    struct tnode *root;
    struct tnode **sorted;      /* the nodes of the tree, to be sorted */
    char word[MAXWORD];
    int i, n;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    n = treecount(root);
    if (n == 0)
        return 0;
    sorted = (struct tnode **)malloc(n * sizeof(struct tnode *));
    if (sorted == NULL) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }
    treefill(root, sorted, 0);
    qsort(sorted, n, sizeof(struct tnode *), cmpcount);

    for (i = 0; i < n; i++)
        printf("%4d %s\n", sorted[i]->count, sorted[i]->word);
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();
        p->word = dupstr(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;     /* repeated word */
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
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

/* treecount: number of nodes in tree p */
int treecount(struct tnode *p)
{
    if (p == NULL)
        return 0;
    return treecount(p->left) + 1 + treecount(p->right);
}

/*
 * treefill: store the nodes of tree p in a[n], a[n+1], ...;
 * return the index of the next free place
 */
int treefill(struct tnode *p, struct tnode *a[], int n)
{
    if (p != NULL) {
        n = treefill(p->left, a, n);
        a[n++] = p;
        n = treefill(p->right, a, n);
    }
    return n;
}

/* cmpcount: larger count first; words with equal counts in alphabetical order */
int cmpcount(const void *a, const void *b)
{
    struct tnode *x = *(struct tnode **)a;
    struct tnode *y = *(struct tnode **)b;

    if (x->count != y->count)
        return y->count - x->count;
    return strcmp(x->word, y->word);
}

/* getword: get next word or character from input; words are put in lower case */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = tolower(c);

    if (isdigit(c)) {           /* skip a number such as 42 or 3rd */
        while (isalnum(d = getch()))
            ;
        ungetch(d);
        *w = '\0';
        return c;
    }

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        d = getch();
        if (!isalnum(d)) {
            ungetch(d);
            break;
        }
        *w = tolower(d);
    }

    *w = '\0';

    return word[0];
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
