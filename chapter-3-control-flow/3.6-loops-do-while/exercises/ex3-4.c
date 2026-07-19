/*
 * File name:   ex3-4.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 19, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 3-4. In a two's complement number representation, our version of itoa
 * does not handle the largest negative number, that is, the value of n equal to
 * - (2 ^ (wordsize - 1)). Explain why not. Modify it to print that value
 * correctly, regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

/* reverse: reverse string s */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;
    i = 0;
    sign = n;

    do {
        int digit = n % 10;
        if (digit < 0)
            digit = -digit;
        s[i++] = digit + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[100];

    itoa(INT_MIN, s);
    printf("%s\n", s);

    itoa(-12345, s);
    printf("%s\n", s);

    return 0;
}
