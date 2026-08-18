/*
 * File name:   ex5-7.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Aug 18, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the program?
 *
 * Solution explanation & performance:
 * 1. Storage is allocated in main() as `char linestor[MAXSTORAGE]` and passed to `readlines`.
 * 2. `getLine()` reads text directly into `linestor` at current pointer position `p`, avoiding
 *    both extra function call overhead of `alloc()` and memory copy overhead of `strcpy()`.
 * 3. The program is faster because:
 *    - Removes string copy overhead (`strcpy`) from an intermediate buffer.
 *    - Eliminates function call overhead for `alloc()`.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES    5000        /* max #lines to be sorted */
#define MAXLEN      1000        /* max length of any input line */
#define MAXSTORAGE  50000       /* max total characters stored */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int maxlines, char *linestor);
void writelines(char *lineptr[], int nlines);
void my_qsort(char *lineptr[], int left, int right);
int getLine(char *, int);

/* sort input lines */
int main()
{
    int nlines; /* number of input lines read */
    char linestor[MAXSTORAGE]; /* storage buffer supplied by main */

    if ((nlines = readlines(lineptr, MAXLINES, linestor)) >= 0) {
        my_qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines directly into linestor buffer supplied by main */ 
int readlines(char *lineptr[], int maxlines, char *linestor)
{
    int len, nlines;
    char *p = linestor;
    char *linestor_end = linestor + MAXSTORAGE;

    nlines = 0;
    while ((len = getLine(p, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > linestor_end)
            return -1;
        p[len - 1] = '\0'; /* delete newline */
        lineptr[nlines++] = p;
        p += len;
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* getLine: read a line into s, return length using pointers */
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
