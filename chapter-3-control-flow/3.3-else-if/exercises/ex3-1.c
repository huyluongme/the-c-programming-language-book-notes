/*
 * File name:   ex3-1.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 15, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write a version with
 * only one test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>
#include <time.h>

#define MAX_ELEMENTS 100000
#define NUM_SEARCHES 2000000

int binsearch_original(int x, int v[], int n);
int binsearch_new(int x, int v[], int n);
void run_unit_tests();

int main()
{
    // Run correctness verification tests first
    run_unit_tests();

    int test_array[MAX_ELEMENTS];
    int i;
    clock_t start, end;
    double time_original, time_new;
    int result = 0;

    // Initialize sorted array
    for (i = 0; i < MAX_ELEMENTS; i++) {
        test_array[i] = i;
    }

    printf("Benchmarking binsearch_original...\n");
    start = clock();
    for (i = 0; i < NUM_SEARCHES; i++) {
        result += binsearch_original(i % (MAX_ELEMENTS * 2), test_array, MAX_ELEMENTS);
    }
    end = clock();
    time_original = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Benchmarking binsearch_new...\n");
    start = clock();
    for (i = 0; i < NUM_SEARCHES; i++) {
        result += binsearch_new(i % (MAX_ELEMENTS * 2), test_array, MAX_ELEMENTS);
    }
    end = clock();
    time_new = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Result sum (to prevent optimization): %d\n", result);
    printf("Original binsearch: %.6f seconds\n", time_original);
    printf("New binsearch:      %.6f seconds\n", time_new);

    return 0;
}

/* binsearch: find x in v[]	[K&R-A version]
 * parameters: x is the element to search for, v[] is the sorted array,
 * n is the size of the array.
 * returns: the index of x if found, -1 otherwise
 */
int binsearch_original(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;

        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

/* binsearch: find x in v[] [modified version]
 * parameters: x is the element to search for, v[] is the sorted array,
 * n is the size of the array.
 * returns: the index of x if found, -1 otherwise
 */
int binsearch_new(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low < high) {
        mid = (low + high) / 2;
        if (x > v[mid])
            low = mid + 1;
        else
            high = mid;
    }

    if (low == high && v[low] == x)
        return low;
    else
        return -1;
}

void run_unit_tests()
{
    int empty[] = {0}; // Allocating space to avoid empty initializer warning in strict C
    int one[] = {5};
    int two[] = {3, 5};
    int several[] = {1, 3, 5, 7, 9};

    // Test n = 0
    if (binsearch_original(5, empty, 0) != -1 || binsearch_new(5, empty, 0) != -1) {
        printf("Test failed: empty array\n");
        return;
    }

    // Test n = 1
    if (binsearch_original(5, one, 1) != 0 || binsearch_new(5, one, 1) != 0) {
        printf("Test failed: n=1, present\n");
        return;
    }
    if (binsearch_original(3, one, 1) != -1 || binsearch_new(3, one, 1) != -1) {
        printf("Test failed: n=1, absent\n");
        return;
    }

    // Test n = 2
    if (binsearch_original(3, two, 2) != 0 || binsearch_new(3, two, 2) != 0) {
        printf("Test failed: n=2, first element\n");
        return;
    }
    if (binsearch_original(5, two, 2) != 1 || binsearch_new(5, two, 2) != 1) {
        printf("Test failed: n=2, second element\n");
        return;
    }
    if (binsearch_original(4, two, 2) != -1 || binsearch_new(4, two, 2) != -1) {
        printf("Test failed: n=2, absent middle\n");
        return;
    }

    // Test several
    int i;
    for (i = 0; i < 5; i++) {
        if (binsearch_original(several[i], several, 5) != i || binsearch_new(several[i], several, 5) != i) {
            printf("Test failed: several, index %d\n", i);
            return;
        }
    }
    if (binsearch_original(0, several, 5) != -1 || binsearch_new(0, several, 5) != -1) {
        printf("Test failed: several, absent low\n");
        return;
    }
    if (binsearch_original(10, several, 5) != -1 || binsearch_new(10, several, 5) != -1) {
        printf("Test failed: several, absent high\n");
        return;
    }

    printf("All correctness unit tests passed successfully!\n");
}
