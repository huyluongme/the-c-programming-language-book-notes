/*
 * File name:   temperature_converter.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 9, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

/* printf Fahrenheit-Celsius table */

int main()
{
    int fahr;

    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));

    return 0;
}

