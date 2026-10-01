/*
 * File name:   ex5-17.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Oct 1, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-17. Add a field-searching capability, so sorting may bee done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.) 
 *
 */

#include <ctype.h>
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
int fold_strcmp(char *, char *);
int rev_fold_strcmp(char *, char *);
int dirchar(int);
int dir_cmp(char *, char *, int);
int dir_strcmp(char *, char *);
int rev_dir_strcmp(char *, char *);
int dir_fold_strcmp(char *, char *);
int rev_dir_fold_strcmp(char *, char *);

#define MAXKEYS 10   /* max #field-sort keys given on the command line */

int nkeys = 0;
int keystart[MAXKEYS];              /* field where key i starts */
int keyend[MAXKEYS];                /* field where key i ends (exclusive), -1 = end of line */
int keynum[MAXKEYS], keyrev[MAXKEYS], keyfold[MAXKEYS], keydir[MAXKEYS]; /* per-key options */

int getnum(char **pp);
char *fieldptr(char *s, int n);
int fieldcmp(char *s1, char *s2);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;          /* number of input lines read */
    int numeric = 0;     /* 1 if numeric sort (whole-line, no fields given) */
    int reverse = 0;     /* 1 if reverse sort (whole-line, no fields given) */
    int fold = 0;        /* 1 if case-insensitive sort (whole-line, no fields given) */
    int directory = 0;   /* 1 if directory order sort (whole-line, no fields given) */
    int error = 0;       /* 1 if illegal option */
    int curkey = -1;     /* index of the key a trailing -M belongs to */
    char *p;
    int (*comp)(void *, void *);

    while (--argc > 0 && (++argv)[0][0] != '\0' &&
           (argv[0][0] == '+' || argv[0][0] == '-')) {
        p = argv[0] + 1;

        if (argv[0][0] == '+') {
            /* +N: start a new field-sort key at field N */
            if (nkeys >= MAXKEYS) {
                printf("sort: too many sort keys\n");
                error = 1;
                break;
            }
            curkey = nkeys++;
            keystart[curkey] = getnum(&p);
            keyend[curkey] = -1;
            keynum[curkey] = keyrev[curkey] = keyfold[curkey] = keydir[curkey] = 0;
        } else if (isdigit((unsigned char) *p)) {
            /* -M: end the current field-sort key at field M */
            if (curkey < 0) {
                printf("sort: -%s has no matching +pos1\n", p);
                error = 1;
                break;
            }
            keyend[curkey] = getnum(&p);
        }

        /* trailing/standalone option letters: apply to the current key
           if one is open, otherwise to the whole-line options */
        while (*p != '\0' && !error) {
            switch (*p) {
            case 'n':
                if (curkey >= 0) keynum[curkey] = 1; else numeric = 1;
                break;
            case 'r':
                if (curkey >= 0) keyrev[curkey] = 1; else reverse = 1;
                break;
            case 'f':
                if (curkey >= 0) keyfold[curkey] = 1; else fold = 1;
                break;
            case 'd':
                if (curkey >= 0) keydir[curkey] = 1; else directory = 1;
                break;
            default:
                printf("sort: illegal option %c\n", *p);
                error = 1;
                break;
            }
            p++;
        }

        if (error)
            break;
    }

    if (error) {
        printf("Usage: sort [+pos1 [-pos2][nrfd]]... [-n] [-r] [-f] [-d]\n");
        return 1;
    }

    if (nkeys > 0)
        comp = (int (*) (void*, void*)) fieldcmp;
    else if (numeric)
        comp = reverse ? (int (*) (void*, void*)) rev_numcmp
                        : (int (*) (void*, void*)) numcmp;
    else if (directory && fold)
        comp = reverse ? (int (*) (void*, void*)) rev_dir_fold_strcmp
                        : (int (*) (void*, void*)) dir_fold_strcmp;
    else if (directory)
        comp = reverse ? (int (*) (void*, void*)) rev_dir_strcmp
                        : (int (*) (void*, void*)) dir_strcmp;
    else if (fold)
        comp = reverse ? (int (*) (void*, void*)) rev_fold_strcmp
                        : (int (*) (void*, void*)) fold_strcmp;
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

/* fold_strcmp: compare s1 and s2, ignoring case distinctions */
int fold_strcmp(char *s1, char *s2)
{
    for ( ; tolower((unsigned char) *s1) == tolower((unsigned char) *s2); s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return tolower((unsigned char) *s1) - tolower((unsigned char) *s2);
}

/* rev_fold_strcmp: compare s1 and s2 ignoring case, reversed order */
int rev_fold_strcmp(char *s1, char *s2)
{
    return -fold_strcmp(s1, s2);
}

/* dirchar: nonzero if c counts in directory order (letter, digit or blank) */
int dirchar(int c)
{
    return isalnum((unsigned char) c) || isspace((unsigned char) c);
}

/* dir_cmp: compare s1 and s2 using only letters, digits and blanks,
   folding case if fold is nonzero */
int dir_cmp(char *s1, char *s2, int fold)
{
    int c1, c2;

    for (;;) {
        while (*s1 != '\0' && !dirchar((unsigned char) *s1))
            s1++;
        while (*s2 != '\0' && !dirchar((unsigned char) *s2))
            s2++;

        c1 = (unsigned char) *s1;
        c2 = (unsigned char) *s2;
        if (fold) {
            c1 = tolower(c1);
            c2 = tolower(c2);
        }

        if (c1 != c2)
            return c1 - c2;
        if (*s1 == '\0')
            return 0;
        s1++;
        s2++;
    }
}

/* dir_strcmp: compare s1 and s2 in directory order */
int dir_strcmp(char *s1, char *s2)
{
    return dir_cmp(s1, s2, 0);
}

/* rev_dir_strcmp: compare s1 and s2 in directory order, reversed order */
int rev_dir_strcmp(char *s1, char *s2)
{
    return -dir_strcmp(s1, s2);
}

/* dir_fold_strcmp: compare s1 and s2 in directory order, ignoring case */
int dir_fold_strcmp(char *s1, char *s2)
{
    return dir_cmp(s1, s2, 1);
}

/* rev_dir_fold_strcmp: compare s1 and s2 in directory order, ignoring case,
   reversed order */
int rev_dir_fold_strcmp(char *s1, char *s2)
{
    return -dir_fold_strcmp(s1, s2);
}

/* getnum: read a decimal number starting at *pp, advance *pp past the digits */
int getnum(char **pp)
{
    int n = 0;

    while (isdigit((unsigned char) **pp)) {
        n = 10 * n + (**pp - '0');
        (*pp)++;
    }
    return n;
}

/* fieldptr: return pointer to the start of field n (0-based; fields are
   separated by runs of blanks). if the line has fewer than n fields,
   returns a pointer to the trailing '\0'. */
char *fieldptr(char *s, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        while (*s == ' ' || *s == '\t')
            s++;
        while (*s != '\0' && *s != ' ' && *s != '\t')
            s++;
    }
    while (*s == ' ' || *s == '\t')
        s++;
    return s;
}

/* fieldcmp: compare s1 and s2 key by key, as described by keystart[]/
   keyend[] and their per-key options; the first key that differs decides
   the result, ties fall through to the next key */
int fieldcmp(char *s1, char *s2)
{
    char buf1[MAXLEN], buf2[MAXLEN];
    char *p1, *p2, *e1, *e2;
    int i, len, r;

    for (i = 0; i < nkeys; i++) {
        p1 = fieldptr(s1, keystart[i]);
        p2 = fieldptr(s2, keystart[i]);

        if (keyend[i] < 0) {
            e1 = p1 + strlen(p1);
            e2 = p2 + strlen(p2);
        } else {
            e1 = fieldptr(s1, keyend[i]);
            e2 = fieldptr(s2, keyend[i]);
            while (e1 > p1 && (e1[-1] == ' ' || e1[-1] == '\t'))
                e1--;
            while (e2 > p2 && (e2[-1] == ' ' || e2[-1] == '\t'))
                e2--;
        }

        len = e1 - p1;
        memcpy(buf1, p1, len);
        buf1[len] = '\0';
        len = e2 - p2;
        memcpy(buf2, p2, len);
        buf2[len] = '\0';

        if (keynum[i])
            r = keyrev[i] ? rev_numcmp(buf1, buf2) : numcmp(buf1, buf2);
        else if (keydir[i] && keyfold[i])
            r = keyrev[i] ? rev_dir_fold_strcmp(buf1, buf2) : dir_fold_strcmp(buf1, buf2);
        else if (keydir[i])
            r = keyrev[i] ? rev_dir_strcmp(buf1, buf2) : dir_strcmp(buf1, buf2);
        else if (keyfold[i])
            r = keyrev[i] ? rev_fold_strcmp(buf1, buf2) : fold_strcmp(buf1, buf2);
        else
            r = keyrev[i] ? rev_strcmp(buf1, buf2) : strcmp(buf1, buf2);

        if (r != 0)
            return r;
    }
    return 0;
}
