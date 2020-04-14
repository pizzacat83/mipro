#include <stdio.h>

int main()
{
    double res = 0;
    for (int i = 0; i < 10; ++i) {
        double x;
        scanf("%lf", &x);
        res += x*x;
    }
    printf("%f\n", res);
    return 0;
}
