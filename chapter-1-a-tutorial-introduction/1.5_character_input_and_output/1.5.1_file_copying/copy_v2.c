/*
 * File name:   copy_v2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 13, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* copy input to output; 2nd version */
int main()
{
    int c;

    while ((c = getchar()) != EOF)
        putchar(c);

    return 0;
}

