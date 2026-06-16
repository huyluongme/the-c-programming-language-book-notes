/*
 * File name:   ex1-15.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-15. Rewrite the temperature conversion program of Section 1.2
 * to use a function for conversion
 */

#include <stdio.h>

float to_celsius(float fahrenheit);

int main()
{
    float fahr;
    float lower, upper, step;

    lower = 0;      /* lower limit of temperature sclase */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    while (fahr <= upper) {
        printf("%3.0f\t%6.1f\n", fahr, to_celsius(fahr));
        fahr = fahr + step;
    }

    return 0;
}

/* to_celsius: convert fahrenheit to celsius */
float to_celsius(float fahrenheit) {
    return (5.0 / 9.0) * (fahrenheit - 32.0);
}
