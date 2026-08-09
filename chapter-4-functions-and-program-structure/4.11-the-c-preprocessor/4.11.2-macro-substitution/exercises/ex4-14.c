/*
 * File name:   ex4-14.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 9, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments
 * of type t. (Block structure will help.)
 */

#include <stdio.h>

#define swap(t, x, y) do { t temp = (x); (x) = (y); (y) = temp; } while (0)

int main()
{
    int a = 1, b = 2;
    printf("a = %d, b = %d\n", a, b);
    swap(int, a, b);
    printf("a = %d, b = %d\n", a, b);

    char c = 'a', d = 'b';
    printf("c = %c, d = %c\n", c, d);
    swap(char, c, d);
    printf("c = %c, d = %c\n", c, d);

    double x = 1.0, y = 2.0;
    printf("x = %f, y = %f\n", x, y);
    swap(double, x, y);
    printf("x = %f, y = %f\n", x, y);

    /* Test swap in an if-else statement without braces */
    if (a > b)
        swap(int, a, b);
    else
        printf("a is not greater than b\n");

    return 0;
}
