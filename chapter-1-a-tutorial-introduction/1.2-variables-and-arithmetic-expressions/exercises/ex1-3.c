/*
 * File name:   ex1-3.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 7, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-3. Modify the temperature conversion program
 * to print a heading above the table
 */

#include <stdio.h>

/* printf Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300 */

int main()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;      /* lower limit of temperature sclase */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;

    printf("Fahr -> Celsius\n");
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%4.0f\t%7.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}

