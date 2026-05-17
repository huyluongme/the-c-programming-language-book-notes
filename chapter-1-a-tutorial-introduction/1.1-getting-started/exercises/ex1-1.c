/*
 * File name:   ex1-1.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        May 17, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-1. Run the "hello, world" programe on your system. Expertiment
 * with leaving out parts of the program, to see what error messages you get.
 */

#include <stdio.h>

int main()
{
    printf("huyluongme\n);
    return 0;
}

/*
Result: We will get a “missing quotes character” error.

exercise_1_1.c: In function ‘main’:
exercise_1_1.c:5:12: warning: missing terminating " character
    5 |     printf("huyluongme\n);
      |            ^
exercise_1_1.c:5:12: error: missing terminating " character
    5 |     printf("huyluongme\n);
      |            ^~~~~~~~~~~~~~~
exercise_1_1.c:6:5: error: expected expression before ‘return’
    6 |     return 0;
      |     ^~~~~~
exercise_1_1.c:6:14: error: expected ‘;’ before ‘}’ token
    6 |     return 0;
      |              ^
      |              ;
    7 | }
      | ~
*/

