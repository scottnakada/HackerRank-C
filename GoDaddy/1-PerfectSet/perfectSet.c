#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG
/*
Problem Statement

There are n tokens in a box numbered from 1 to n. You are also given an integer d. You have to pick m different
tokens blindly, but the numbers written on the tokens must have a special property.

Suppose the set of numbers written on the tokens you picked is S = {x1,x2.......xm}. The set S is perfect if there is
at least d pairs of numbers (xa,xb) in the set such that xa+xb=n+1.

(xa,xb) and (xb,xa) are considered the same pairs. Also, xa and xb are not the same.

What is the minimum number of tokens you must pick so that it's guaranteed that S is a perfect set?

Input Format

There are two integers n and d separated by a space.

Constraints

2<=n<=2?109
1<=d<=n/2
It is guaranteed that a valid answer exists.

Output Format

Print a single number denoting the minimum number of tokens you must pick up so that it's guaranteed that S is a
perfect set.

Sample Input

8 2
Sample Output

6
Explanation

If you pick any 6 numbers from 1 to 8, there will always be at least two pairs that add up to n+1.
For example: if you pick {1,4,5,6,7,8}, the valid pairs will be (1,8) and (4,5).

If you pick less than 6 numbers, there is a chance there might be less than two such pairs.
*/

int main() {
    int numTokens;          /* Number of tokens numbered 1-N (N) */
    int numPairs;           /* Number of pairs that add to N+1 (D) */
    int minTokensToPull;    /* Miniumum number of tokens to pull */

    /* Read the number of tokens and pairs required */
    scanf("%d %d", &numTokens, &numPairs);
#ifdef DEBUG
    printf("Tokens = %d, Pairs = %d\r\n", numTokens, numPairs);
#endif

    /* Assuming worst cast pull of all low numbers, we need to pull n/2 numbers + num Pairs */
    /* If n is odd, add one, since there is a number with no matching number to equal n+1 */
    minTokensToPull = (numTokens/2) + (numTokens % 2) + numPairs;

#ifdef DEBUG
    printf("Miniumum tokens to Pull = %d\r\n", minTokensToPull);
#endif
    /* Print out the final count of campers */
    printf("%d\r\n", minTokensToPull);

    return 0;
}
