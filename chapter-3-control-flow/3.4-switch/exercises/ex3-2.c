/*
 * File name:   ex3-2.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 15, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 3-2. Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t as it copies
 * the string t to s. Use a switch. Write a function for the other direction
 * as well, converting escape sequences into the real characters.
 */

#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main()
{
    char s[100];
    char t[100] = "Hello\nWorld\tHuy";
    char r[100];
    escape(s, t);
    printf("escaped: %s\n", s);
    unescape(r, s);
    printf("unescaped: %s\n", r);

    return 0;
}

void escape(char s[], char t[])
{
    int i, j;

    i = 0;
    j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\n':
                s[j] = '\\';
                s[++j] = 'n';
                break;
            case '\t':
                s[j] = '\\';
                s[++j] = 't';
                break;
            default:
                s[j] = t[i];
                break;
        }
        ++i;
        ++j;
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j;

    i = 0;
    j = 0;
    while (t[i] != '\0') {
        if (t[i] == '\\') {
            switch (t[i + 1]) {
                case 'n':
                    s[j++] = '\n';
                    i += 2;
                    break;
                case 't':
                    s[j++] = '\t';
                    i += 2;
                    break;
                default:
                    s[j++] = t[i++];
                    break;
            }
        } else {
            s[j++] = t[i++];
        }
    }
    s[j] = '\0';
}
