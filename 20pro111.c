#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include "./memory.h"
#include "strings.h"
#include "util.h"

unsigned distance(const String s1, const String s2) {
    unsigned** dp;
    NEW(dp, s1.length + 1);
    for (size_t i = 0; i < s1.length + 1; ++i) {
        NEW(dp[i], s2.length + 1);
    }

    for (size_t j = 0; j < s2.length + 1; ++j) {
        dp[0][j] = (unsigned)j;
    }
    for (size_t i = 1; i < s1.length + 1; ++i) {
        dp[i][0] = (unsigned)i;
    }

    for (size_t i = 1; i < s1.length + 1; ++i) {
        for (size_t j = 1; j < s2.length + 1; ++j) {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1;
            dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (s1.chars[i - 1] != s2.chars[j - 1]));
        }
    }

    unsigned res = dp[s1.length][s2.length];

    for (size_t i = 0; i < s1.length + 1; ++i) {
        free(dp[i]);
    }
    free(dp);

    return res;
}


int main() {
    String s1;
    String s2;
    read_new_string(s1, 1000);
    read_new_string(s2, 1000);
    printf("%d\n", distance(s1, s2));
    delete_string(&s1);
    delete_string(&s2);
    return 0;
}
