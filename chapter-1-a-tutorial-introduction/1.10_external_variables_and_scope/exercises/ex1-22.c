/*
 * File name:   ex1-22.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 15, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column
 */

#include <stdio.h>

#define N 10
#define TABVAL 8

char line[N + 1];

/* Function prototypes */
void print_line(int end_idx);
int find_blank(int end_idx);
int shift_line(int split_idx, int total_len);
int get_col(int len);
int get_char_width(int c, int current_col);

int main()
{
    int c;
    int pos = 0;
    int col = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            print_line(pos);
            putchar('\n');
            pos = 0;
            col = 0;
        } else {
            int width = get_char_width(c, col);

            if (col + width > N) {
                int i = find_blank(pos);

                if (i >= 0) {
                    print_line(i);
                    putchar('\n');

                    pos = shift_line(i, pos);
                    col = get_col(pos);
                } else {
                    print_line(pos);
                    putchar('\n');
                    pos = 0;
                    col = 0;
                }

                width = get_char_width(c, col);
            }

            line[pos] = c;
            pos++;
            col += width;
        }
    }

    if (pos > 0) {
        print_line(pos);
    }

    return 0;
}

/* Print line buffer up to end_idx (non-inclusive) */
void print_line(int end_idx)
{
    int j;
    for (j = 0; j < end_idx; ++j) {
        putchar(line[j]);
    }
}

/* Find the last blank space or tab in line buffer */
int find_blank(int end_idx)
{
    int i = end_idx - 1;
    while (i >= 0 && line[i] != ' ' && line[i] != '\t') {
        --i;
    }
    return i;
}

/* Shift remaining characters after split_idx to the start of the buffer */
int shift_line(int split_idx, int total_len)
{
    int j;
    int remaining_len = total_len - 1 - split_idx;
    for (j = 0; j < remaining_len; ++j) {
        line[j] = line[split_idx + 1 + j];
    }
    return remaining_len;
}

/* Recalculate screen column position for the buffer contents */
int get_col(int len)
{
    int j;
    int current_col = 0;
    for (j = 0; j < len; ++j) {
        current_col += get_char_width(line[j], current_col);
    }
    return current_col;
}

/* Get screen column width of a character at the current column */
int get_char_width(int c, int current_col)
{
    if (c == '\t') {
        return TABVAL - (current_col % TABVAL);
    }
    return 1;
}
