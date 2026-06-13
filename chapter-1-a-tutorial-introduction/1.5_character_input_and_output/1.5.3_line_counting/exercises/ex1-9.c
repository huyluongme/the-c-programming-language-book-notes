/*
 * File name:   ex1-9.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-9. Write a program to copy its input to its output,
 * replacing each string of one or more blanks with a single blank.
 */

#include <stdio.h>

int main()
{
    int c;
    int blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        } else {
            if (blanks > 0) {
                putchar(' ');
                blanks = 0;
            }
            putchar(c);
        }
    }

    return 0;
}
