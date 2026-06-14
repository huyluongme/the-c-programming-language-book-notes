/*
 * File name:   ex1-14.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-14. Write a program to print a histogram of the frequencies of
 * different characters in its input.
 */

#include <stdio.h>

#define ASCII_MAX   128

int main()
{
    int c, i, j;
    int freq[ASCII_MAX];

    /* initialize counts to 0 */
    for (i = 0; i < ASCII_MAX; ++i)
        freq[i] = 0;

    /* read input and count frequencies */
    while ((c = getchar()) != EOF) {
        if (c >= 0 && c < ASCII_MAX) {
            ++freq[c];
        }
    }

    /* print horizontal histogram for characters that occurred at least once */
    printf("Horizontal Histogram of Character Frequencies:\n");
    for (i = 0; i < ASCII_MAX; ++i) {
        if (freq[i] > 0) {
            if (i == ' ')
                printf("' ' (space) : ");
            else if (i == '\n')
                printf("'\\n' (newline): ");
            else if (i == '\t')
                printf("'\\t' (tab)    : ");
            else if (i >= '!' && i <= '~')
                printf("'%c'          : ", i);
            else
                printf("0x%02X        : ", i);

            for (j = 0; j < freq[i]; ++j)
                printf("*");
            printf(" (%d)\n", freq[i]);
        }
    }

    return 0;
}
