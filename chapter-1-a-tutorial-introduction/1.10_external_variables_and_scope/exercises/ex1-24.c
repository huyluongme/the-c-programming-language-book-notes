/*
 * File name:   ex1-24.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 15, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-24. Write a program to check a C program for rudimentary syntax
 * errors like unmatched parentheses, brackets and braces. Don't forget about
 * quotes, both single and double, escape sequences, and comments.
 * (This program is hard if you do it in full generality.)
 */

#include <stdio.h>

#define MAXSTACK 1000

int line_num = 1;
char stack[MAXSTACK];
int stack_ptr = 0;
int errors = 0;

int my_getchar(void);
void check_char(int c);
void skip_comment(void);
void skip_single_comment(void);
void skip_quote(int c);
void push(int c);
void pop_and_check(int expected_open, int closing_char);

int main()
{
    int c;

    while ((c = my_getchar()) != EOF) {
        check_char(c);
    }

    if (stack_ptr > 0) {
        printf("Error: Unmatched opening bracket '%c' remains at end of file\n", stack[stack_ptr - 1]);
        errors++;
    }

    if (errors == 0) {
        printf("Syntax check passed: No unmatched parentheses, brackets, or braces found.\n");
    } else {
        printf("Syntax check failed: %d error(s) found.\n", errors);
    }

    return 0;
}

int my_getchar(void)
{
    int c = getchar();
    if (c == '\n') {
        ++line_num;
    }
    return c;
}

void check_char(int c)
{
    int d;

    if (c == '/') {
        if ((d = my_getchar()) == '*') {
            skip_comment();
        } else if (d == '/') {
            skip_single_comment();
        } else {
            /* It's just a division or slash, check the character d */
            check_char(d);
        }
    } else if (c == '\'' || c == '"') {
        skip_quote(c);
    } else if (c == '{' || c == '[' || c == '(') {
        push(c);
    } else if (c == '}') {
        pop_and_check('{', '}');
    } else if (c == ']') {
        pop_and_check('[', ']');
    } else if (c == ')') {
        pop_and_check('(', ')');
    }
}

void push(int c)
{
    if (stack_ptr < MAXSTACK) {
        stack[stack_ptr++] = c;
    } else {
        printf("Error on line %d: Stack overflow (too many nested brackets)\n", line_num);
        errors++;
    }
}

void pop_and_check(int expected_open, int closing_char)
{
    if (stack_ptr == 0) {
        printf("Error on line %d: Unmatched closing bracket '%c'\n", line_num, closing_char);
        errors++;
    } else {
        int open_char = stack[stack_ptr - 1];
        if (open_char == expected_open) {
            stack_ptr--;
        } else {
            printf("Error on line %d: Mismatched brackets: expected '%c' to match '%c', but got '%c'\n",
                   line_num, expected_open, open_char, closing_char);
            errors++;
            /* Pop to try to recover and find matching brackets for outer blocks */
            stack_ptr--;
        }
    }
}

void skip_comment(void)
{
    int c, d;

    c = my_getchar();
    d = my_getchar();
    while (c != '*' || d != '/') {
        c = d;
        d = my_getchar();
        if (d == EOF) {
            printf("Error on line %d: Unterminated comment (ends with EOF)\n", line_num);
            errors++;
            break;
        }
    }
}

void skip_single_comment(void)
{
    int c;
    while ((c = my_getchar()) != '\n' && c != EOF) {
        ;
    }
}

void skip_quote(int c)
{
    int d;

    while ((d = my_getchar()) != c && d != EOF) {
        if (d == '\\') {
            int escaped = my_getchar();
            if (escaped == EOF) {
                printf("Error on line %d: Escape character '\\' at EOF inside quote\n", line_num);
                errors++;
                break;
            }
        }
    }
    if (d == EOF) {
        printf("Error on line %d: Unterminated quote '%c' (ends with EOF)\n", line_num, c);
        errors++;
    }
}
