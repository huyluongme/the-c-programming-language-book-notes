/*
 * File name:   ex2-6.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 8, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-6. Write a function setbits(x, p, n, y) that returns x with the
 * n bits that begin at position p set to the rightmost n bits of y,
 * leaving the other bits of x unchanged.
 */

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
void print_binary(unsigned int x);

int main()
{
    unsigned int x = 0b10111110;
    int p = 4;
    int n = 3;
    unsigned int y = 0b11111101;
    printf("x = ");
    print_binary(x);
    printf("y = ");
    print_binary(y);
    printf("p = %d, n = %d\n", p, n);
    printf("setbits(x, p, n, y) = ");
    print_binary(setbits(x, p, n, y));

    return 0;
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    unsigned int last_n_bits_of_y = y & ~(~0 << n);
    unsigned int mask = ~(~0 << n) << (p + 1 - n);
    
    return x & ~mask | last_n_bits_of_y << (p + 1 - n);
}

void print_binary(unsigned int x)
{
    int i;
    
    for (i = 31; i >= 0; i--) {
        putchar((x >> i) & 1 ? '1' : '0');
    }
    putchar('\n');
}
