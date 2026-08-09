/*
 * File name:   ex4-13.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 9, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 4-13. Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_rec(char s[], int i, int j)
{
    if (i >= j)
        return;

    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;

    reverse_rec(s, i + 1, j - 1);
}

/* reverse: reverse string s */
void reverse(char s[])
{
    int len = strlen(s);
    reverse_rec(s, 0, len - 1);
}

int main()
{
    char test1[] = "hello";
    reverse(test1);
    printf("reverse(\"hello\") -> \"%s\"\n", test1);

    char test2[] = "abcd";
    reverse(test2);
    printf("reverse(\"abcd\")  -> \"%s\"\n", test2);

    char test3[] = "a";
    reverse(test3);
    printf("reverse(\"a\")     -> \"%s\"\n", test3);

    char test4[] = "";
    reverse(test4);
    printf("reverse(\"\")      -> \"%s\"\n", test4);

    char test5[] = "racecar";
    reverse(test5);
    printf("reverse(\"racecar\") -> \"%s\"\n", test5);

    return 0;
}
