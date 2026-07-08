/*
 * File name:   ex2-8.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 8, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n positions
 */

#include <stdio.h>
#include <limits.h>

void print_binary(unsigned int x);
unsigned int rightrot(unsigned int x, int n);

int main()
{
    unsigned int x = 0b10110101;
    int n = 3;
    printf("x = ");
    print_binary(x);
    printf("n = %d\n", n);
    printf("rightrot(x, n) = ");
    print_binary(rightrot(x, n));

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

unsigned rightrot(unsigned x, int n)
{
    int word_size = sizeof(unsigned) * CHAR_BIT;

    n = n % word_size;

    if (n == 0)
        return x;

    return (x >> n) | (x << (word_size - n));
}
