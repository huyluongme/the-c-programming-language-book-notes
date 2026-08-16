/*
 * File name:   ex5-4.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 16, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if
 * the string t occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>

int strend(const char *s, const char *t);

int main()
{
    char s[100] = "Hello World";
    char t[] = "World";
    int res = strend(s, t);
    printf("%d\n", res);
    return 0;
}

/* strend(s, t): returns 1 if the string t occurs at the
   end of the string s, and zero otherwise. */
int strend(const char *s, const char *t)
{
    const char *orig_s = s;
    const char *orig_t = t;
    
    while (*s)
        s++;
    while (*t)
        t++;

    while (t > orig_t) {
        if (s == orig_s)
            return 0;

        if (*--s != *--t)
            return 0;
    }
    
    return 1;
}
