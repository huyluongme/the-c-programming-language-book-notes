/*
 * File name:   ex5-11-entab.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Sep 6, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-11. Modify the program entab and detab (written as exercises in Chapter 1)
 * to accept a list of tab stops as arguments. Use the default tab settings if there are
 * no arguments.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define TABSTOP 8

void settab(int argc, char *argv[], char *tab);
int istab(int pos, char *tab);

int main(int argc, char *argv[])
{
    int c;
    int pos = 0;
    int blanks = 0;
    char tab[MAXLINE + 1];

    settab(argc, argv, tab);

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++pos;
            ++blanks;
            if (istab(pos, tab)) {
                putchar('\t');
                blanks = 0;
            }
        }
        else {
            while (blanks > 0) {
                putchar(' ');
                --blanks;
            }

            putchar(c);

            if (c == '\n') {
                pos = 0;
            }
            else if (c == '\t') {
                do {
                    ++pos;
                } while (!istab(pos, tab) && pos < MAXLINE);
            }
            else {
                ++pos;
            }
        }
    }

    while (blanks > 0) {
        putchar(' ');
        --blanks;
    }

    return 0;
}

/* settab: initialize tab stop table from command-line arguments or defaults */
void settab(int argc, char *argv[], char *tab)
{
    int i, pos;

    for (i = 0; i <= MAXLINE; i++)
        tab[i] = 0;

    if (argc <= 1) {
        /* default tab stops every TABSTOP columns */
        for (i = TABSTOP; i <= MAXLINE; i += TABSTOP)
            tab[i] = 1;
    }
    else {
        /* user-specified tab stops: entab 4 8 16 ... */
        while (--argc > 0) {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE)
                tab[pos] = 1;
        }
    }
}

/* istab: check if current position is a tab stop */
int istab(int pos, char *tab)
{
    if (pos > MAXLINE)
        return 1;

    return tab[pos];
}
