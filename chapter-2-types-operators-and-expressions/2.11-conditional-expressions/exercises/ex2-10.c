/*
 * File name:   ex2-10.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 11, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-10. Rewite the function lower, which converts
 * upper case letters to lower case, with a conditional expression
 * instead of if-else
 */

#include <stdio.h>

/* lower: convert c to lowercase */
int lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

int main()
{
    char str[] = "AbCdEfGhIjKlMnOpQrStUvWxYz0123456789!@#$%^&*()_+=-`~[];',./<>? \t\n\r\f\v\\\"\'\?";

    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = lower(str[i]);
    }

    printf("%s\n", str);

    return 0;
}

