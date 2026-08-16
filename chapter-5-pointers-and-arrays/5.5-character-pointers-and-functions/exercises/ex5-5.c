/*
 * File name:   ex5-5.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 16, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-5. Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */

#include <stdio.h>

char *my_strncpy(char *s, const char *t, size_t n);
char *my_strncat(char *s, const char *t, size_t n);
int my_strncmp(const char *s, const char *t, size_t n);

int main()
{
    char s[100] = "Hello ";
    char t[] = "World";

    printf("strncpy: %s\n", my_strncpy(s, t, 5));

    char s2[100] = "Hello ";
    char t2[] = "World";

    printf("strncat: %s\n", my_strncat(s2, t2, 5));

    char s3[100] = "Hello ";
    char t3[] = "World";

    printf("strncmp: %d\n", my_strncmp(s3, t3, 5));

    return 0;
}

/* my_strncpy(s,t,n): copy at most the first n characters of t to s */
char *my_strncpy(char *s, const char *t, size_t n)
{
    char *dest = s;

    while (n > 0 && *t) {
        *s++ = *t++;
        n--;
    }

    while (n > 0) {
        *s++ = '\0';
        n--;
    }

    return dest;
}

/* my_strncat(s, t, n): concatenate at most the first n characters of t to s */
char *my_strncat(char *s, const char *t, size_t n)
{
    char *dest = s;

    while (*s) s++;

    while (n > 0 && *t) {
        *s++ = *t++;
        n--;
    }

    *s = '\0';

    return dest;
}

/* my_strncmp(s,t,n): compare the first n characters of s and t */
int my_strncmp(const char *s, const char *t, size_t n)
{
    while (n > 0 && *s && *t) {
        if (*s != *t)
            return *s - *t;
        s++;
        t++;
        n--;
    }

    return n > 0 ? *s - *t : 0;
}
