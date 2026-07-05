/*
 * File name:   ex2-4.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 5, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-4. Write an alternative version of squeeze(s1, s2) that deletes
 * each character in s1 that matches any character in the string s2.
 */

#include <stdio.h>

void squeeze(char s1[], const char s2[]);

int main()
{
    char s1[] = "hello world";
    char s2[] = "lo";

    squeeze(s1, s2);
    printf("%s\n", s1);

    return 0;
}

void squeeze(char s1[], const char s2[])
{
    int i, j, k;
    for (i = j = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0' && s2[k] != s1[i]; k++)
            ;
        
        if (s2[k] == '\0') {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}
