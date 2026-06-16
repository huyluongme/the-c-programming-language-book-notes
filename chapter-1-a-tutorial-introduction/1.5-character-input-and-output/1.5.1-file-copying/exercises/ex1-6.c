/*
 * File name:   ex1-6.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 13, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-6. Verify that the expression
 * getchar() != EOF is 0 or 1.
 */

#include <stdio.h>

int main()
{
    int c;

    printf("Please enter some text and then send EOF (Ctrl+D on Unix, Ctrl+Z on Windows):\n");

    /* Read the first character (if any) and check if it's not EOF */
    c = (getchar() != EOF);
    printf("Value of (getchar() != EOF) with active input: %d\n", c);

    /* Consume the remaining characters in the input stream until EOF is reached */
    while (getchar() != EOF)
        ;

    /* Now at EOF, check the value again */
    c = (getchar() != EOF);
    printf("Value of (getchar() != EOF) at EOF: %d\n", c);

    return 0;
}
