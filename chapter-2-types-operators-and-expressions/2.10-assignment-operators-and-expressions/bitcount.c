/*
 * File name:   bitcount.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 9, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int i;
    for (i = 0; x != 0; x >>= 1)
        if (x & 01)
            ++i;
    return i;
}

int main()
{
    unsigned x = 5;
    printf("Number of 1 bits in %d is %d\n", x, bitcount(x));

    return 0;
}
