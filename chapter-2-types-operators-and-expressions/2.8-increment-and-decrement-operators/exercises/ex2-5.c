/*
 * File name:   ex2-5.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 5, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-5. Write the function any(s1, s2) which returns the first location
 * in a string s1 where any character from the string s2 occurs, or -1 if s1
 * contains no characters from s2. (The standard library function strpbrk does
 * the same job but returns a pointer to the location.)
 */

#include <stdio.h>

int any(const char s1[], const char s2[]);

int main()
{
    char s1[] = "hello world";
    char s2[] = "lo";
    printf("%d\n", any(s1, s2));
    return 0;
}

int any(const char s1[], const char s2[])
{
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        j = 0;
        while (s2[j] != '\0' && s2[j] != s1[i]) {
            j++;
        }
        if (s2[j] != '\0') {
            return i;
        }
    }
    return -1;
}
