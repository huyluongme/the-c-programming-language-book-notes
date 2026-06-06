/*
 * File name:   ex1-4.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 7, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-4. Write a program to print the
 * corresponding Celsius to Fahrenheit table
 */

#include <stdio.h>

/* printf Celsius-Fahrenheit table
    for celsius = 0, 20, ..., 300 */

int main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;      /* lower limit of temperature sclase */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    celsius = lower;

    printf("Celsius -> Fahr\n");
    while (celsius <= upper) {
        fahr = (celsius * (9.0 / 5.0)) + 32.1;
        printf("%7.1f\t%7.0f\n", celsius, fahr);
        celsius = celsius + step;
    }

    return 0;
}

