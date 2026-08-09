/*
 * File name:   ex4-12.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 9, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 4-12. Adapt the ideas of printd to write a recursive version
 * of itoa; that is, convert an integer into a string by calling a recursive
 * routine.
 */

#include <stdio.h>
#include <stdlib.h>

/* itoa_rec: helper function to convert n to characters in s recursively */
static int itoa_rec(int n, char s[], int i)
{
    if (n / 10)
        i = itoa_rec(n / 10, s, i);

    s[i++] = abs(n % 10) + '0';
    s[i] = '\0';

    return i;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i = 0;

    if (n < 0)
        s[i++] = '-';

    itoa_rec(n, s, i);
}

int main()
{
    char s[100];

    itoa(-12345, s);
    printf("n = -12345  -> s = %s\n", s);

    itoa(12345, s);
    printf("n = 12345   -> s = %s\n", s);

    itoa(0, s);
    printf("n = 0       -> s = %s\n", s);

    itoa(-2147483648, s);
    printf("n = INT_MIN -> s = %s\n", s);

    return 0;
}
