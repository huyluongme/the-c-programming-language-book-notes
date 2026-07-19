/*
 * File name:   ex3-5.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 19, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 3-5. Write the function itob(n, s, b) that converts the interger n
 * into a base b character representation in the string s.
 * In particular, itob(n, s, 16) formats s as a hexadecimal integer in s;
 */

#include <stdio.h>
#include <string.h>

/* reverse: reverse string s */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = (int)strlen(s) - 1; i < j; ++i, --j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itob: convert n to characters in s using base b */
void itob(int n, char s[], int b)
{
    int i = 0;
    int sign = n;

    if (b < 2 || b > 36) {
        s[0] = '\0';
        return;
    }

    do {
        int digit = n % b;

        /*
         * Giữ n ở dạng âm để xử lý được INT_MIN.
         * Phần dư âm được đổi thành dương.
         */
        if (digit < 0)
            digit = -digit;

        if (digit < 10)
            s[i++] = digit + '0';
        else
            s[i++] = digit - 10 + 'A';

        n /= b;
    } while (n != 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int main(void)
{
    char s[100];

    itob(256, s, 2);
    printf("%s\n", s);       /* 100000000 */

    itob(255, s, 16);
    printf("%s\n", s);       /* FF */

    itob(-31, s, 16);
    printf("%s\n", s);       /* -1F */

    return 0;
}
