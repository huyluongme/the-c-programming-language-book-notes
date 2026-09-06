/*
 * File name:   ex5-13.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Sep 6, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-13. Write the program tail, which prints the last n lines of its input.
 * By default, n is set to 10, let us say, but it can be changed by an optional argument
 * so that tail -n prints the last n lines.
 * The program should behave rationally no matter how unreasonable the input or the
 * value of n. Write the program so it makes the best use of available storage; lines
 * should be stored as in the sorting program of Section 5.6, not in a two-dimensional
 * array of fixed size. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_N   10
#define MAXLEN      1000

int getLine(char *s, int lim);
void writetail(char *lineptr[], int n, int total_lines, int cur);

int main(int argc, char *argv[])
{
    int n = DEFAULT_N;
    int cur = 0;
    int total_lines = 0;
    int len, i;
    char line[MAXLEN];
    char **lineptr;

    /* Parse command-line arguments */
    if (argc == 2) {
        if (argv[1][0] == '-') {
            char *p = argv[1] + 1;
            if (*p == 'n' && *(p + 1) == '\0') {
                fprintf(stderr, "tail: option requires an argument -- 'n'\n");
                return 1;
            }
            while (*p) {
                if (!isdigit(*p)) {
                    fprintf(stderr, "tail: invalid number of lines: '%s'\n", argv[1]);
                    return 1;
                }
                p++;
            }
            n = atoi(argv[1] + 1);
        }
        else {
            fprintf(stderr, "Usage: tail [-n]\n");
            return 1;
        }
    }
    else if (argc == 3 && strcmp(argv[1], "-n") == 0) {
        char *p = argv[2];
        while (*p) {
            if (!isdigit(*p)) {
                fprintf(stderr, "tail: invalid number of lines: '%s'\n", argv[2]);
                return 1;
            }
            p++;
        }
        n = atoi(argv[2]);
    }
    else if (argc > 3) {
        fprintf(stderr, "Usage: tail [-n]\n");
        return 1;
    }

    /* Behave rationally: if n <= 0, nothing to print */
    if (n <= 0)
        return 0;

    /* Allocate circular buffer of n line pointers */
    lineptr = (char **)malloc(n * sizeof(char *));
    if (lineptr == NULL) {
        fprintf(stderr, "tail: out of memory for line pointers\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        lineptr[i] = NULL;

    /* Read lines into the circular buffer */
    while ((len = getLine(line, MAXLEN)) > 0) {
        if (lineptr[cur] != NULL)
            free(lineptr[cur]);

        lineptr[cur] = (char *)malloc(len + 1);
        if (lineptr[cur] == NULL) {
            fprintf(stderr, "tail: out of memory for line text\n");
            for (i = 0; i < n; i++) {
                if (lineptr[i] != NULL)
                    free(lineptr[i]);
            }
            free(lineptr);
            return 1;
        }
        strcpy(lineptr[cur], line);

        cur = (cur + 1) % n;
        total_lines++;
    }

    /* Write out the tail lines */
    writetail(lineptr, n, total_lines, cur);

    /* Free all allocated memory */
    for (i = 0; i < n; i++) {
        if (lineptr[i] != NULL)
            free(lineptr[i]);
    }
    free(lineptr);

    return 0;
}

/* writetail: print the last n lines from the circular buffer in chronological order */
void writetail(char *lineptr[], int n, int total_lines, int cur)
{
    int count = (total_lines < n) ? total_lines : n;
    int start = (total_lines < n) ? 0 : cur;
    int i;

    for (i = 0; i < count; i++)
        printf("%s", lineptr[(start + i) % n]);
}

/* getLine: read a line into s using pointers, return length */
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
