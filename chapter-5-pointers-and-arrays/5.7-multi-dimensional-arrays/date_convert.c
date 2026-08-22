/*
 * File name:   date_convert.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Aug 19, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Sample code copied from the book
 */

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    int year = 1980;
    int month = 8;
    int day = 31;
    int yearday = day_of_year(year, month, day);
    printf("%d-%d-%d is day number %d\n", year, month, day, yearday);
    month_day(year, yearday, &month, &day);
    printf("day number %d of year %d is %d-%d-%d\n", yearday, year, year, month, day);
    return 0;
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
