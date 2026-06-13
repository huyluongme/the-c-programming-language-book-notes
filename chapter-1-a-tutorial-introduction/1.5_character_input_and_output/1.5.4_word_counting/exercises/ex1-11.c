/*
 * File name:   ex1-11.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        Jun 14, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 1-11. How would you test the word count program?
 * What kinds of input are most likely to uncover bugs if there are any?
 *
 * --------------------------------------------------------------------------
 * EXPLANATION:
 *
 * 1. How to test the word count program:
 *    - We can build an automated test suite by writing a C test runner (as shown below)
 *      or a shell script.
 *    - In the C program below, the core word counting algorithm is extracted into a test
 *      harness function. We define several test cases with predefined input strings
 *      and expected counts (nl, nw, nc), then run the logic and compare actual results
 *      against the expectations.
 *    - For black-box system testing, we can feed different files or generated inputs
 *      to the compiled binary using redirection (`./a.out < input.txt`) or piping
 *      (`echo "..." | ./a.out`) and assert the printed output matches standard counts.
 *
 * 2. What kinds of input are most likely to uncover bugs (Edge/Boundary cases):
 *    - Empty input (no characters, immediate EOF): Verifies that counts remain 0.
 *    - Whitespace-only input: Input containing only ' ', '\t', and '\n'. Ensures the
 *      word count remains 0.
 *    - Complex whitespace patterns: Multiple consecutive spaces, tabs, and newlines
 *      to verify the IN/OUT state machine transitions correctly and doesn't double-count.
 *    - Boundary words: Words starting immediately at the first character of input, or
 *      ending directly at EOF without trailing whitespace or newline.
 *    - Punctuation and special characters: Words like "state-of-the-art" or "hello,world!".
 *      K&R defines a word as any sequence of characters not containing whitespace.
 *      Thus, "hello,world!" is counted as 1 word. A production-ready tool might treat
 *      punctuation as boundaries (counting as 2 words).
 *    - Integer overflow: Extremely large inputs (lines, words, or character counts exceeding
 *      INT_MAX), which will cause counter overflow and negative outputs.
 *    - Multi-byte characters: Input containing UTF-8 characters (e.g., non-ASCII/emojis).
 *      Since K&R wc operates on single-byte chars, character counting (nc) counts raw
 *      bytes rather than visual graphemes.
 */

#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* Function to run the word count logic on a test string and verify output */
void run_test(const char *test_name, const char *input, int expected_nl, int expected_nw, int expected_nc)
{
    int c, nl, nw, nc, state;
    int i, j;

    state = OUT;
    nl = nw = nc = 0;
    i = 0;

    while ((c = (unsigned char)input[i++]) != '\0') {
        ++nc;

        if (c == '\n')
            ++nl;

        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }

    printf("Test case: %s\n", test_name);
    printf("Input:     \"");
    for (j = 0; input[j] != '\0'; ++j) {
        if (input[j] == '\n')
            printf("\\n");
        else if (input[j] == '\t')
            printf("\\t");
        else
            putchar(input[j]);
    }
    printf("\"\n");
    printf("Expected:  nl=%d, nw=%d, nc=%d\n", expected_nl, expected_nw, expected_nc);
    printf("Actual:    nl=%d, nw=%d, nc=%d\n", nl, nw, nc);

    if (nl == expected_nl && nw == expected_nw && nc == expected_nc) {
        printf("Result:    PASS\n\n");
    } else {
        printf("Result:    FAIL\n\n");
    }
}

int main()
{
    printf("=== RUNNING WORD COUNT TEST SUITE ===\n\n");

    /* 1. Empty input */
    run_test("Empty input", "", 0, 0, 0);

    /* 2. Whitespace only */
    run_test("Whitespace only", " \t\n  \n\t ", 2, 0, 8);

    /* 3. One word, no whitespace */
    run_test("One word, no whitespace", "hello", 0, 1, 5);

    /* 4. One word, wrapped in whitespaces */
    run_test("One word, wrapped in whitespaces", " \n\t hello \t\n ", 2, 1, 13);

    /* 5. Multiple words with single spacing */
    run_test("Multiple words with single spacing", "hello world", 0, 2, 11);

    /* 6. Multiple words with multiple and mixed whitespaces */
    run_test("Multiple words with mixed whitespaces", "  hello \t\n  world \n", 2, 2, 19);

    /* 7. Words containing punctuation (K&R definition vs real world) */
    run_test("Words with punctuation (K&R logic)", "hello,world! state-of-the-art", 0, 2, 29);

    /* 8. Word ending directly with EOF (no trailing newline) */
    run_test("No trailing newline", "hello world", 0, 2, 11);

    return 0;
}
