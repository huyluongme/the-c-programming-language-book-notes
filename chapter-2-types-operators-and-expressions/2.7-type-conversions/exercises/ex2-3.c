/*
 * File name:   ex2-3.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 5, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-3. Write a function htoi(s), which converts a strings of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and
 * A through F.
 */

#include <stdio.h>

int htoi(char s[]);

int main()
{
    printf("%d\n", htoi("0xFF"));
    printf("%d\n", htoi("0XFf"));
    printf("%d\n", htoi("0XfF"));
    printf("%d\n", htoi("0Xff"));
    printf("%d\n", htoi("0x0123456789ABCDEFabcdef"));

    return 0;
}

// htoi: convert a string of hexadecimal digits
// Example: 0xFF, 0XfF, fF, ... -> 255
int htoi(char s[])
{
    int i = 0, n = 0;

    if (s[i] == '0')
        if (s[i + 1] == 'x' || s[i + 1] == 'X')
            i += 2;

    for (; s[i] != '\0'; ++i) {
        int digit;

        if (s[i] >= '0' && s[i] <= '9')
            digit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            digit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            digit = s[i] - 'A' + 10;
        else
            break;

        n = n * 16 + digit;
    }

    return n;
}
