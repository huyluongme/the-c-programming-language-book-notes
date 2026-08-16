/*
 * File name:   ex5-3.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 16, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-3. Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end of s.
 */

#include <stdio.h>

void my_strcat(char *s, char *t);

int main()
{
    char s[100] = "Hello ";
    char t[] = "World";
    my_strcat(s, t);
    printf("%s\n", s);
    return 0;
}

/* my_strcat(s, t): pointer version */
void my_strcat(char *s, char *t)
{
    while (*s) s++;
    while (*t) *s++ = *t++;
    *s = '\0';
}
