/*
 * File name:   ex1-2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        May 17, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-2. Experiment to find out what happens
 * when printf's argument string contains \c,
 * where c is some character not listed above.
 */

#include <stdio.h>

int main()
{
    printf("huyluong\cme\n");
    return 0;
}

/*
Result: Get "unknown escape sequence" error

exercise_1_2.c: In function ‘main’:
exercise_1_2.c:5:28: warning: unknown escape sequence: '\c'
    5 |     printf("huyluong\cme\n");
      |                            ^
*/

