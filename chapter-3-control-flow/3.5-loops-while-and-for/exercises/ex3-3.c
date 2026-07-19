/*
 * File name:   ex3-3.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jul 19, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 3-3. Write a function expand(s1, s2) that expands shorthand
 * notations like a-z in the string s1 into the equivalent complete abc...xyz
 * in s2. Allow for letters of either case and digits, and be prepared to handle
 * cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing -
 * is taken literally.
 */

#include <stdio.h>
#include <ctype.h>

int same_type(char a, char b)
{
    return (islower((unsigned char)a) && islower((unsigned char)b)) ||
           (isupper((unsigned char)a) && isupper((unsigned char)b)) ||
           (isdigit((unsigned char)a) && isdigit((unsigned char)b));
}

void expand(const char s1[], char s2[])
{
    int i;
    int j = 0;

    for (i = 0; s1[i] != '\0'; ++i) {
        if (s1[i] == '-' &&
            i > 0 &&
            s1[i + 1] != '\0' &&
            same_type(s1[i - 1], s1[i + 1]) &&
            s1[i - 1] < s1[i + 1]) {

            char c;

            for (c = s1[i - 1] + 1; c <= s1[i + 1]; ++c)
                s2[j++] = c;

            ++i;
        } else {
            s2[j++] = s1[i];
        }
    }

    s2[j] = '\0';
}

int main(void)
{
    char s2[200];

    expand("a-z", s2);
    printf("%s\n", s2);

    expand("a-z0-9", s2);
    printf("%s\n", s2);

    expand("-a-z", s2);
    printf("%s\n", s2);

    expand("a-z-", s2);
    printf("%s\n", s2);

    expand("a-b-c", s2);
    printf("%s\n", s2);

    return 0;
}
