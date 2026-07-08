/*
 * File name:   ex2-7.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 8, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
 * that begin at position p inverted (i.e., 1 changed to 0 and vice versa),
 * leaving the others unchanged
 */

#include <stdio.h>

void print_binary(unsigned int x);
unsigned int invert(unsigned int x, int p, int n);

int main()
{
    unsigned int x = 0b10110101;
    int p = 4;
    int n = 3;
    printf("x = ");
    print_binary(x);
    printf("p = %d, n = %d\n", p, n);
    printf("invert(x, p, n) = ");
    print_binary(invert(x, p, n));

    return 0;
}

void print_binary(unsigned int x)
{
    int i;
    
    for (i = 31; i >= 0; i--) {
        putchar((x >> i) & 1 ? '1' : '0');
    }
    putchar('\n');
}

unsigned int invert(unsigned int x, int p, int n)
{
    unsigned int mask = ~(~0 << n) << (p + 1 - n);

    return x ^ mask;
}
