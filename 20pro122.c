#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include <math.h>
#include "./memory.h"

double poly(double* A, size_t n, double x) {
    double xi = 1;
    double ans = 0;
    double* Y;
    NEW(Y, n);
    for (size_t i = 0; i < n; ++i) {
        Y[i]= A[i] * xi;
        xi *= x;
    }
    for (size_t i = 0; i < n; ++i) {
        if (fabs(x) > 1) {
            ans += Y[i];
        } else {
            ans += Y[n-i-1];
        }
    }
    free(Y);
    return ans;
}

double binary_search(double* A, size_t n, double pos, double neg) {
    while (fabs(pos - neg) > 1e-10) {
        double c = (pos + neg)/2;
        if (poly(A, n, c) >= 0) {
            pos = c;
        } else {
            neg = c;
        }
    }
    return pos;
}

int main() {
    size_t n;
    scanf("%lu", &n);
    ++n;
    double* A;
    NEW(A, n);
    for (size_t i = 0; i < n; ++i) {
        scanf("%lf", &A[n - 1 - i]);
    }
    double pos, neg;
    scanf("%lf %lf", &pos, &neg);
    if (poly(A, n, pos) < poly(A, n, neg)) {
        double t = pos;
        pos = neg;
        neg = t;
    }
    double ans = binary_search(A, n, pos, neg);
    printf("%.10lf\n", ans);
    fprintf(stderr, "%lf\n", poly(A,n,ans));

    free(A);
    return 0;
}
