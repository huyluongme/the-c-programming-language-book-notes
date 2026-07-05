/*
 * File name:   lower.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 23, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* lower: convert c to lowercase */
int lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
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
