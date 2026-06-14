/*
 * File name:   ex1-21.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 15, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for detab. When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 *
 * Answer: When either a tab or a single blank would suffice to reach a tab
 * stop, prefer a tab over a single blank to achieve the same spacing.
 */

#include <stdio.h>

#define TABSTOP 8

int main()
{
    int c;
    int pos = 0;
    int blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++pos;
            ++blanks;
            if (pos % TABSTOP == 0) {
                putchar('\t');
                blanks = 0;
            }
        } else {
            while (blanks > 0) {
                putchar(' ');
                --blanks;
            }

            putchar(c);

            if (c == '\n') {
                pos = 0;
            } else if (c == '\t') {
                pos = pos + (TABSTOP - (pos % TABSTOP));
            } else {
                ++pos;
            }
        }
    }

    while (blanks > 0) {
        putchar(' ');
        --blanks;
    }

    return 0;
}
