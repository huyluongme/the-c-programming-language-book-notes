/*
 * File name:   echo_v1.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Sep 4, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* echo command-line arguments; 1st version */
int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");

    printf("\n");

    return 0;
}

