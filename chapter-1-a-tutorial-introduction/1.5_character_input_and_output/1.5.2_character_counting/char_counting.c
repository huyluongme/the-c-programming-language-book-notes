/*
 * File name:   char_counting.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 13, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* count characters in input; 1st version */
int main()
{
    long nc;

    while (getchar() != EOF)
        ++nc;

    printf("%ld\n", nc);

    return 0;
}

