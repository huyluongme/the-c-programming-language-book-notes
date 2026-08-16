/*
 * File name:   ex5-6.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        August 16, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 5-6. Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getline (Chapters 1 and 4), atoi, itoa, and their variants
 * (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
 * (Chapter 4).
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUMBER '0'

int getLine(char *s, int lim);
int atoi(const char *s);
char* itoa(int n, char *s);
void reverse(char *s);
int strindex(const char *s, const char *t);
int getop(char *s);

int main()
{
    /* 1. Test getLine */
    char line[100];
    printf("--- Test getLine ---\n");
    printf("Enter a line: ");
    int len = getLine(line, sizeof(line));
    printf("Length: %d, Content: %s\n", len, line);

    /* 2. Test atoi */
    char numStr1[] = "-12345";
    char numStr2[] = "+6789";
    printf("--- Test atoi ---\n");
    printf("atoi(\"%s\") = %d\n", numStr1, atoi(numStr1));
    printf("atoi(\"%s\") = %d\n", numStr2, atoi(numStr2));

    /* 3. Test itoa */
    char buf1[50], buf2[50];
    printf("--- Test itoa ---\n");
    printf("itoa(-12345) = %s\n", itoa(-12345, buf1));
    printf("itoa(0) = %s\n", itoa(0, buf2));

    /* 4. Test reverse */
    char str[] = "Hello World";
    printf("--- Test reverse ---\n");
    printf("Before reverse: %s\n", str);
    reverse(str);
    printf("After reverse: %s\n", str);

    /* 5. Test strindex */
    char s[] = "Hello World";
    char t1[] = "World";
    char t2[] = "abc";
    printf("--- Test strindex ---\n");
    printf("strindex(\"%s\", \"%s\") = %d\n", s, t1, strindex(s, t1));
    printf("strindex(\"%s\", \"%s\") = %d\n", s, t2, strindex(s, t2));

    /* 6. Test getop */
    char sOp[100];
    int type;
    printf("--- Test getop ---\n");
    printf("Enter an expression (e.g. 12.34 + 56): ");
    while ((type = getop(sOp)) != EOF && type != '\n') {
        if (type == NUMBER)
            printf("Found NUMBER: %s\n", sOp);
        else
            printf("Found OPERATOR: %c\n", type);
    }

    return 0;
}

/* getLine: read a line into s using pointers, return length */
int getLine(char *s, int lim)
{
    int c;
    char *p = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;

    *s = '\0';

    return s - p;
}

/* atoi: convert string s to integer */
int atoi(const char *s)
{
    int n = 0;
    int sign = 1;

    while (isspace(*s))
        s++;

    if (*s == '+' || *s == '-') {
        sign = (*s == '-') ? -1 : 1;
        s++;
    }

    while (*s >= '0' && *s <= '9') {
        n = 10 * n + (*s - '0');
        s++;
    }

    return n * sign;
}

/* reverse: reverse string s in place using pointers */
void reverse(char *s)
{
    if (!*s)
        return;

    char *p = s;
    char *q = s;

    while (*q)
        q++;
    q--;

    while (p < q) {
        char temp = *p;
        *p++ = *q;
        *q-- = temp;
    }
}

/* itoa: convert integer n to string s */
char* itoa(int n, char *s)
{
    char *p = s;
    int sign = n;

    if (n < 0)
        n = -n;

    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        *s++ = '-';

    *s = '\0';

    reverse(p);

    return p;
}

/* strindex: return index of first occurrence of t in s, -1 if none */
int strindex(const char *s, const char *t)
{
    const char *p, *q, *r;

    for (p = s; *p != '\0'; p++) {
        for (q = p, r = t; *r != '\0' && *q == *r; q++, r++)
            ;
        if (r > t && *r == '\0')
            return p - s;
    }

    return -1;
}

/* getop: get next character or numeric operand using pointers */
int getop(char *s)
{
    int c;

    /* Skip white spaces */
    while ((*s = c = getchar()) == ' ' || c == '\t')
        ;
    *(s + 1) = '\0';

    /* Not a number or decimal point */
    if (!isdigit(c) && c != '.')
        return c;

    /* Collect integer part */
    if (isdigit(c))
        while (isdigit(*++s = c = getchar()))
            ;

    /* Collect fraction part */
    if (c == '.')
        while (isdigit(*++s = c = getchar()))
            ;

    *s = '\0';
    if (c != EOF)
        ungetc(c, stdin);

    return NUMBER;
}
