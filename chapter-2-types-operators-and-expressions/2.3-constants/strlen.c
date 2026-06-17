/*
 * File name:   strlen.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 17, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* my_strlen: return length of s */
int my_strlen(char s[])
{
    int i;

    while (s[i] != '\0')
        ++i;

    return i;
}

int main()
{
    char s[] = "huyluongme";

    printf("%d\n", my_strlen(s));

    return 0;
}

