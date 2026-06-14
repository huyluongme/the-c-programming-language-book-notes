/*
 * File name:   ex1-20.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 15, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-20. Write a program detab that replaces tabs in the input with
 * the proper number of blanks to space to the next tab stop. Assume a fixed
 * set of tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter?
 *
 * Answer:
 * n should be a symbolic parameter (e.g., #define TABSTOP 8) if the tab size
 * is fixed and known at compile time, as this allows compiler optimizations
 * (like using bitwise operations for modulo if n is a power of 2) and saves
 * memory.
 *
 * However, n should be a variable if the program needs to support dynamic tab
 * sizes specified by the user at runtime (e.g., via command-line arguments).
 */

#include <stdio.h>

#define TABSTOP 8

int main()
{
    int c, pos = 0, spaces;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            spaces = TABSTOP - (pos % TABSTOP);

            while (spaces > 0) {
                putchar(' ');
                ++pos;
                --spaces;
            }
        } else if (c == '\n') {
            putchar(c);
            pos = 0;
        } else {
            putchar(c);
            ++pos;
        }
    }
    return 0;
}
