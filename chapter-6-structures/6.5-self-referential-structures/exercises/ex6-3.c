/*
 * File name:   ex6-3.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Nov 02, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 6-3. Write a cross-referencer that prints a list of all words
 * in a document, and for each word, a list of the line numbers on which it
 * occurs. Remove noise words like ``the,''``and,'' and so on. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct lnode {                  /* a line number in the list */
    int line;                   /* line number */
    struct lnode *next;         /* next line number */
};

struct tnode {                  /* the tree node */
    char *word;                 /* points to the text */
    struct lnode *lines;        /* first line number */
    struct lnode *last;         /* last line number */
    struct tnode *left;         /* left child */
    struct tnode *right;        /* right child */
};

/* noise words, in sorted order; they are not put in the index */
char *noise[] = {
    "a", "about", "an", "and", "are", "as", "at", "be", "but", "by", "for",
    "from", "had", "has", "have", "he", "her", "his", "i", "in", "is", "it",
    "its", "of", "on", "or", "she", "that", "the", "their", "there", "they",
    "this", "to", "was", "we", "were", "which", "will", "with", "you"
};

#define NNOISE (sizeof noise / sizeof noise[0])

struct tnode *addtree(struct tnode *, char *, int);
void addline(struct tnode *, int);
struct tnode *talloc(void);
struct lnode *lalloc(void);
char *dupstr(char *);
int isnoise(char *);
void treeprint(struct tnode *);
int getword(char *, int);

int getch(void);
void ungetch(int c);

/* cross-referencer: each word with the lines it occurs on */
int main(void)
{
    struct tnode *root;
    char word[MAXWORD];
    int c, line;

    root = NULL;
    line = 1;
    while ((c = getword(word, MAXWORD)) != EOF)
        if (c == '\n')
            line++;
        else if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, word, line);
    treeprint(root);
    return 0;
}

/* addtree: add the line number of w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int line)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();
        p->word = dupstr(w);
        p->lines = p->last = NULL;
        p->left = p->right = NULL;
        addline(p, line);
    } else if ((cond = strcmp(w, p->word)) == 0)
        addline(p, line);   /* repeated word */
    else if (cond < 0)
        p->left = addtree(p->left, w, line);
    else
        p->right = addtree(p->right, w, line);
    return p;
}

/* addline: add a line number at the end of p's list, unless it is there */
void addline(struct tnode *p, int line)
{
    struct lnode *l;

    if (p->last != NULL && p->last->line == line)
        return;                 /* same word twice on one line */
    l = lalloc();
    l->line = line;
    l->next = NULL;
    if (p->last == NULL)
        p->lines = l;
    else
        p->last->next = l;
    p->last = l;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* lalloc: make an lnode */
struct lnode *lalloc(void)
{
    return (struct lnode *)malloc(sizeof(struct lnode));
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

/* isnoise: binary search for word in noise; 1 if found */
int isnoise(char *word)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = NNOISE - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, noise[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return 1;
    }
    return 0;
}

/* treeprint: in-order print of tree p, each word with its line numbers */
void treeprint(struct tnode *p)
{
    struct lnode *l;

    if (p != NULL) {
        treeprint(p->left);
        printf("%s:", p->word);
        for (l = p->lines; l != NULL; l = l->next)
            printf(" %d", l->line);
        putchar('\n');
        treeprint(p->right);
    }
}

/*
 * getword: get next word or character from input; words are put in
 * lower case, and a newline is returned as a character of its own so
 * that the caller can count lines
 */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while ((c = getch()) != '\n' && isspace(c))
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
