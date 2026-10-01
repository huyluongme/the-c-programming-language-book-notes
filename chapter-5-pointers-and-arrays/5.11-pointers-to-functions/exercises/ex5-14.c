/*
 * File name:   ex5-14.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Sep 25, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES    5000        /* max #lines to be sorted */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int rev_strcmp(char *, char *);
int rev_numcmp(char *, char *);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;          /* number of input lines read */
    int numeric = 0;     /* 1 if numeric sort */
    int reverse = 0;     /* 1 if reverse sort */
    int c, error = 0;    /* 1 if illegal option */
    int (*comp)(void *, void *);

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("sort: illegal option %c\n", c);
                argc = 0;
                error = 1;
                break;
            }

    if (error) {
        printf("Usage: sort [-n] [-r]\n");
        return 1;
    }

    if (numeric)
        comp = reverse ? (int (*) (void*, void*)) rev_numcmp
                        : (int (*) (void*, void*)) numcmp;
    else
        comp = reverse ? (int (*) (void*, void*)) rev_strcmp
                        : (int (*) (void*, void*)) strcmp;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort((void**)lineptr, 0, nlines - 1, comp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN  1000    /* max length of any input line */
#define ALLOCSIZE 10000 /* size of available space */

int getLine(char *, int);
char *alloc(int);

/* readlines: read input lines */ 
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getLine(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* getLine: read a line into s, return length using pointers*/
int getLine(char *s, int lim)
{
    int c;
    char *p = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - p;
}

/* alloc: allocate storage using pointers*/
char *alloc(int n)
{
    static char allocbuf[ALLOCSIZE];
    static char *allocp = allocbuf;

    if (n <= allocbuf + ALLOCSIZE - allocp) {
        allocp += n;
        return allocp - n;
    }
    return NULL;
}

/* my_qsort: sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right, int (*comp) (void *, void *))
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right)  /* do nothing if array contains fewer than two elements */
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    my_qsort(v, left, last, comp);
    my_qsort(v, last + 1, right, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* rev_strcmp: compare s1 and s2, reversed order */
int rev_strcmp(char *s1, char *s2)
{
    return -strcmp(s1, s2);
}

/* rev_numcmp: compare s1 and s2 numerically, reversed order */
int rev_numcmp(char *s1, char *s2)
{
    return -numcmp(s1, s2);
}
