/**
 * C: Naive, improved memory access 
 * Requirements: Symmetry
 * O(A.r^3)
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include "timer.h"

enum { MAX_SIZE = 5300 };

double A[MAX_SIZE][MAX_SIZE];
double A2[MAX_SIZE][MAX_SIZE];

int main() {
    tic();
    size_t r, c;
    scanf("%ld %ld", &r, &c);
    // read A
    for (size_t i = 0; i < r; ++i) {
        while (1) {
            int j1;
            scanf("%d", &j1);
            if (j1 == -1) {
                break;
            }
            size_t j = (size_t)(j1-1);
            scanf("%lf", &A[i][j]);
        }
    }

    toc(1);
    tic();
    // twice
    for (size_t k = 0; k < r; ++k) { // In this loop all memory accesses occur between A[k] ~ A[k+1]
        for (size_t i = 0; i < r; ++i) {
            for (size_t j = 0; j < c; ++j) {
                // Symmetric
                A2[i][j] += A[k][i] * A[k][j];
            }
        }
    }

    toc(2);
    tic();
    // print
    printf("%ld %ld\n", r, c);
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            if (A2[i][j] != 0) {
                printf("%ld %lf ", j + 1, A2[i][j]);
            }
        }
        printf("-1\n");
    }

    toc(3);
    return 0;
}

/* 
Samples
=======
In
--
3 2
1 2.0 -1
2 4.0 -1
2 1.0 -1
2 4
1 3.0 4 1.0 -1
2 4.0 3 2.0 4 3.0 -1

Out
---
3 4
1 6.0 4 2.0 -1
2 16.0 3 8.0 4 12.0 -1
2 4.0 3 2.0 4 3.0 -1

*/
