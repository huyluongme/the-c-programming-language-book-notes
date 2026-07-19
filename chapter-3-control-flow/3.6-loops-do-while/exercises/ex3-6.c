/*
 * File name:   ex3-6.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 19, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 3-6. Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the number must be padded
 * with blanks on the left if necessary to make it wide enough.
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
void itoa(int n, char s[], int width)
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

    int len = strlen(s);
    if (len < width) {
        int i;
        for (i = len; i < width; i++) {
            s[i] = ' ';
        }
        s[i] = '\0';
    }

    reverse(s);
}

int main()
{
    char s[100];

    itoa(123, s, 5);
    printf("%s\n", s);

    itoa(-12345, s, 10);
    printf("%s\n", s);

    return 0;
}
