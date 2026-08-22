/*
 * File name:   ex5-9.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Aug 22, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers
 * instead of indexing.
 */

#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    int year = 1980;
    int month = 8;
    int day = 31;
    int m, d;

    /* 1. Test valid inputs */
    int yearday = day_of_year(year, month, day);
    if (yearday != -1) {
        printf("%d-%d-%d is day number %d\n", year, month, day, yearday);
    } else {
        printf("Invalid date: %d-%d-%d\n", year, month, day);
    }

    if (month_day(year, yearday, &m, &d) != -1) {
        printf("Day number %d of year %d is %d-%d-%d\n", yearday, year, year, m, d);
    } else {
        printf("Invalid day of year: %d for year %d\n", yearday, year);
    }

    /* 2. Test invalid inputs for day_of_year */
    printf("\n--- Testing invalid inputs for day_of_year ---\n");
    printf("day_of_year(2023, 13, 10): %d\n", day_of_year(2023, 13, 10));         /* invalid month */
    printf("day_of_year(2023, 2, 29): %d\n", day_of_year(2023, 2, 29));          /* Feb 29 in non-leap year */
    printf("day_of_year(2024, 2, 29): %d\n", day_of_year(2024, 2, 29));          /* Feb 29 in leap year (valid) */
    printf("day_of_year(-2023, 5, 10): %d\n", day_of_year(-2023, 5, 10));        /* invalid year */

    /* 3. Test invalid inputs for month_day */
    printf("\n--- Testing invalid inputs for month_day ---\n");
    if (month_day(2023, 366, &m, &d) == -1)
        printf("month_day(2023, 366): invalid day of year for non-leap year\n");
    if (month_day(2024, 366, &m, &d) == 0)
        printf("month_day(2024, 366): valid for leap year -> %d-%d-%d\n", 2024, m, d);
    if (month_day(2023, 0, &m, &d) == -1)
        printf("month_day(2023, 0): invalid day of year\n");

    return 0;
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day; returns -1 on invalid input */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    if (year < 1 || month < 1 || month > 12)
        return -1;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    p = *(daytab + leap);

    if (day < 1 || day > *(p + month))
        return -1;

    while (--month)
        day += *++p;
    return day;
}

/* month_day: set month, day from day of year; returns 0 on success, -1 on invalid input */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap, maxdays;
    char *p;

    if (year < 1 || pmonth == NULL || pday == NULL)
        return -1;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    maxdays = leap ? 366 : 365;

    if (yearday < 1 || yearday > maxdays)
        return -1;

    p = *(daytab + leap);
    while (yearday > *++p)
        yearday -= *p;
    *pmonth = p - *(daytab + leap);
    *pday = yearday;
    return 0;
}
