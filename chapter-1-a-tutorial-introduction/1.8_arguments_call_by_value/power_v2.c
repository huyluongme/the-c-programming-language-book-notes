/*
 * File name:   power_v2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

int power(int m, int n);

/* test power function */
int main()
{
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));

    return 0;
}

/* power: raise base to n-th power; n >= 0; version 2*/
int power(int base, int n) {
    int p;

    for (p = 1; n > 0; --n)
        p = p * base;

    return p;
}
