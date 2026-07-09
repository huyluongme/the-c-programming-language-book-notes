/*
 * File name:   ex2-9.c
 * Author:      Huy Luong Duc <huyluongme.cs@gmail.com>
 * Date:        July 9, 2026
 *
 * [SECOND EDITION] The C Programming Language
 * by Brian W.Kernighan and Dennis M.Ritchie
 *
 * Exercise 2-9. In a two's complement number system, x & (x-1) deletes the
 * rightmost 1-bit in x. Explain why. Use this observation to write a faster
 * version of bitcount.
 */

#include <stdio.h>

int bitcount(unsigned x);
int bitcount_faster(unsigned x);

int main()
{
    unsigned x = 5;
    printf("Number of 1 bits in %d is %d\n", x, bitcount(x));
    printf("Number of 1 bits in %d is %d\n", x, bitcount_faster(x));

    return 0;
}

int bitcount(unsigned x)
{
    int i;
    for (i = 0; x != 0; x >>= 1)
        if (x & 01)
            ++i;
    return i;
}

int bitcount_faster(unsigned x)
{
    int i;
    for (i = 0; x != 0; x &= (x-1))
        ++i;
    return i;
}

/*
Explanation of x & (x-1):

Consider x in its binary representation.
When we subtract 1 from x, two things happen:
1. The rightmost 1-bit in x is flipped to 0.
2. All the 0-bits to the right of that rightmost 1-bit are flipped to 1.

Example:
Let x = ...1000
Then x-1 = ...0111

Now, when we perform the bitwise AND operation x & (x-1):
- The bits to the left of the rightmost 1 remain unchanged in both x and x-1, so their AND result is the same as the original bits.
- The rightmost 1-bit in x becomes 0 in x-1, so their AND result is 0.
- The 0-bits to the right of the rightmost 1 in x remain 0 in x-1, so their AND result is 0.

Therefore, x & (x-1) effectively clears (sets to 0) the rightmost 1-bit in x, while leaving all other bits unchanged.

Faster version of bitcount:
Instead of iterating through all bits of x and checking if each bit is 1, we can repeatedly apply the x & (x-1) operation until x becomes 0. Each application of this operation removes one 1-bit, so the number of operations required is exactly equal to the number of 1-bits in x.
*/