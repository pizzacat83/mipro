#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include "./memory.h"

size_t binary_search(int* A, size_t n, int q) {
    // A[i] >= q?
    size_t ng = 0;
    size_t ok = n-1;
    if (q < A[ng]) {
        return 0;
    }
    if (A[ok] < q) {
        return n;
    }
    while (ok - ng > 1) {
        size_t c = (ng+ok)/2;
        if (A[c] >= q) {
            ok = c;
        } else {
            ng = c;
        }
    }
    return ok;
}

int main() {
    size_t n;
    scanf("%lu", &n);
    int* A;
    NEW(A, n);
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &A[i]);
    }
    int q;
    scanf("%d", &q);
    printf("%lu\n", binary_search(A, n, q));

    free(A);
    return 0;
}
