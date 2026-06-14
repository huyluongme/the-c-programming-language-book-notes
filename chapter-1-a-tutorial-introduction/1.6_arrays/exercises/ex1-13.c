/*
 * File name:   ex1-13.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is ease to draw the histogram with the bars horizontal;
 * a vertical orientation is more challenging.
 */

#include <stdio.h>

#define MAX_LEN     15      /* maximum length of a word to keep track of individually */
#define IN          1
#define OUT         0

int main()
{
    int c, i, j, len, max_count, state;
    int len_counts[MAX_LEN + 1]; /* count of words for each length from 1 to MAX_LEN */
    int overflow;                /* words with length > MAX_LEN */

    /* initialize counts */
    for (i = 0; i <= MAX_LEN; ++i)
        len_counts[i] = 0;
    overflow = 0;

    state = OUT;
    len = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                if (len <= MAX_LEN)
                    ++len_counts[len];
                else
                    ++overflow;
                len = 0;
                state = OUT;
            }
        } else {
            state = IN;
            ++len;
        }
    }
    /* handle the last word if it doesn't end with a whitespace before EOF */
    if (state == IN) {
        if (len <= MAX_LEN)
            ++len_counts[len];
        else
            ++overflow;
    }

    /* find the maximum count to determine the height of the vertical histogram */
    max_count = overflow;
    for (i = 1; i <= MAX_LEN; ++i) {
        if (len_counts[i] > max_count)
            max_count = len_counts[i];
    }

    /* print horizontal histogram */
    printf("Horizontal Bar:\n");
    for (i = 1; i <= MAX_LEN; ++i) {
        printf("%2d: ", i);
        for (j = 0; j < len_counts[i]; ++j)
            printf("*");
        printf("\n");
    }
    printf(">%d: ", MAX_LEN);
    for (j = 0; j < overflow; ++j)
        printf("*");
    printf("\n");

    /* print vertical histogram */
    printf("\nVertical Bar:\n");
    for (i = max_count; i >= 1; --i) {
        for (j = 1; j <= MAX_LEN; ++j) {
            if (len_counts[j] >= i)
                printf("  *");
            else
                printf("   ");
        }
        /* print column for overflow */
        if (overflow >= i)
            printf("  *");
        else
            printf("   ");
        printf("\n");
    }

    /* print X-axis labels */
    for (i = 1; i <= MAX_LEN; ++i)
        printf("%3d", i);
    printf(" >%d\n", MAX_LEN);

    return 0;
}
