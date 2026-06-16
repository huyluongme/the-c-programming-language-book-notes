/*
 * File name:   ex2-1.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 17, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-1. Write a program to determine the ranges of char, short, int
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

void print_header_ranges(void);
void print_computed_ranges(void);

int main(void)
{
    print_header_ranges();
    putchar('\n');
    print_computed_ranges();

    return 0;
}

/* print ranges from standard headers */
void print_header_ranges(void)
{
    printf("===== RANGES FROM STANDARD HEADERS =====\n\n");

    printf("CHAR_BIT = %d\n\n", CHAR_BIT);

    printf("plain char      : min = %d, max = %d\n", CHAR_MIN, CHAR_MAX);
    printf("signed char     : min = %d, max = %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char   : min = %u, max = %u\n",
           0u, (unsigned)UCHAR_MAX);

    printf("short           : min = %d, max = %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short  : min = %u, max = %u\n",
           0u, (unsigned)USHRT_MAX);

    printf("int             : min = %d, max = %d\n", INT_MIN, INT_MAX);
    printf("unsigned int    : min = %u, max = %u\n",
           0u, UINT_MAX);

    printf("long            : min = %ld, max = %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long   : min = %lu, max = %lu\n",
           0ul, ULONG_MAX);

    putchar('\n');

    /*
     * Note:
     * FLT_MIN / DBL_MIN / LDBL_MIN are the smallest positive normalized values,
     * not the most negative values.
     */
    printf("float           : range = %e to %e\n", -FLT_MAX, FLT_MAX);
    printf("                  smallest positive normalized = %e\n", FLT_MIN);

    printf("double          : range = %e to %e\n", -DBL_MAX, DBL_MAX);
    printf("                  smallest positive normalized = %e\n", DBL_MIN);

    printf("long double     : range = %Le to %Le\n", -LDBL_MAX, LDBL_MAX);
    printf("                  smallest positive normalized = %Le\n", LDBL_MIN);
}

/*
 * print ranges by direct computation
 *
 * For unsigned types:
 *     max = all bits set to 1
 *
 * For signed types on modern two's-complement machines:
 *     max = unsigned_max >> 1
 *     min = -max - 1
 */
void print_computed_ranges(void)
{
    unsigned char uc_max;
    signed char sc_max, sc_min;

    unsigned short us_max;
    short s_max, s_min;

    unsigned int ui_max;
    int i_max, i_min;

    unsigned long ul_max;
    long l_max, l_min;

    printf("===== RANGES BY DIRECT COMPUTATION =====\n\n");

    uc_max = (unsigned char)~0;
    sc_max = (signed char)(uc_max >> 1);
    sc_min = -sc_max - 1;

    us_max = (unsigned short)~0;
    s_max = (short)(us_max >> 1);
    s_min = -s_max - 1;

    ui_max = ~0U;
    i_max = (int)(ui_max >> 1);
    i_min = -i_max - 1;

    ul_max = ~0UL;
    l_max = (long)(ul_max >> 1);
    l_min = -l_max - 1;

    printf("signed char     : min = %d, max = %d\n", sc_min, sc_max);
    printf("unsigned char   : min = %u, max = %u\n",
           0u, (unsigned)uc_max);

    printf("short           : min = %d, max = %d\n", s_min, s_max);
    printf("unsigned short  : min = %u, max = %u\n",
           0u, (unsigned)us_max);

    printf("int             : min = %d, max = %d\n", i_min, i_max);
    printf("unsigned int    : min = %u, max = %u\n",
           0u, ui_max);

    printf("long            : min = %ld, max = %ld\n", l_min, l_max);
    printf("unsigned long   : min = %lu, max = %lu\n",
           0ul, ul_max);

    putchar('\n');

    if (CHAR_MIN == SCHAR_MIN && CHAR_MAX == SCHAR_MAX)
        printf("plain char appears to be signed on this machine.\n");
    else
        printf("plain char appears to be unsigned on this machine.\n");
}
