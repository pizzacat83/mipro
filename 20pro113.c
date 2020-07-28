#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include "./memory.h"
#include "util.h"

unsigned tsp(size_t n, unsigned maxw, const unsigned* W, const unsigned* V) {
    unsigned** dp;
    NEW(dp, n);
    for (size_t i = 0; i < n; ++i) {
        NEW(dp[i], maxw + 1);
    }

    for (unsigned w = 0; w < maxw + 1; ++w) {
        if (w >= W[0]) {
            dp[0][w] = V[0];
        } else {
            dp[0][w] = 0;
        } 
    }

    for (size_t i = 1; i < n; ++i) {
        dp[i][0] = 0;
        for (unsigned w = 1; w < maxw + 1; ++w) {
            dp[i][w] = dp[i-1][w];
            if (W[i] <= w) {
                dp[i][w] = max(dp[i][w], dp[i-1][w - W[i]] + V[i]);
            }
        }
    }
    
    for (size_t i = 0; i < n; ++i) {
        for (unsigned w = 0; w < maxw + 1; ++w) {
            fprintf(stderr, "%d ", dp[i][w]);
        }
        fprintf(stderr, "\n");
    }

    unsigned res = dp[n-1][maxw];

    for (size_t i = 0; i < n; ++i) {
        free(dp[i]);
    }
    free(dp);

    return res;
}


int main() {
    size_t n;
    unsigned maxw;
    scanf("%ld %d", &n, &maxw);
    unsigned* W;
    unsigned* V;
    NEW(W, n);
    NEW(V, n);
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &W[i]);
    }
    for (size_t i = 0; i < n; ++i) {
        scanf("%d", &V[i]);
    }
    printf("%d\n", knapsack(n, maxw, W, V));
    free(V);
    free(W);
    return 0;
}
