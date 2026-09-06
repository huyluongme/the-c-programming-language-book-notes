/*
 * File name:   ex5-12-entab.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Sep 6, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-12. Extend entab and detab to accept the shorthand
 * entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convenient (for the user)
 * default behavior.
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
    int m = 0;
    int n = TABSTOP;
    int custom_list = 0;

    for (i = 0; i <= MAXLINE; i++)
        tab[i] = 0;

    while (--argc > 0) {
        char *s = *++argv;
        if (*s == '-') {
            m = atoi(s + 1);
        }
        else if (*s == '+') {
            n = atoi(s + 1);
        }
        else {
            pos = atoi(s);
            if (pos > 0 && pos <= MAXLINE) {
                tab[pos] = 1;
                custom_list = 1;
            }
        }
    }

    if (!custom_list) {
        if (n <= 0)
            n = TABSTOP;
        if (m < 0)
            m = 0;

        for (i = (m > 0 ? m : n); i <= MAXLINE; i += n)
            tab[i] = 1;
    }
}

/* istab: check if current position is a tab stop */
int istab(int pos, char *tab)
{
    if (pos > MAXLINE)
        return 1;

    return tab[pos];
}
