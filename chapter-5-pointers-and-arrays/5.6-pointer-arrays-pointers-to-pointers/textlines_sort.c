/*
 * File name:   textlines_sort.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Aug 18, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES    5000        /* max #lines to be sorted */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
    int nlines; /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort(lineptr, 0, nlines - 1);
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
void my_qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)  /* do nothing if array contains fewer than two elements */
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    my_qsort(v, left, last);
    my_qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
