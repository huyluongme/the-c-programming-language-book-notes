/*
 * File name:   char_counting_v2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 13, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* count characters in input; 2nd version */
int main()
{
    double nc;

    for (nc = 0; getchar() != EOF; ++nc)
        ;

    printf("%.0f\n", nc);

    return 0;
}

