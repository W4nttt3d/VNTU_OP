#include <stdio.h>

long double fact(int k)
{
    if (k <= 1) return 1.0;
    return k * fact(k - 1);
}

long double recursive(int n, int i)
{
    if (i > n) return 0.0;
    return fact(2 * i) / fact(n + 1) + recursive(n, i + 1);
}

int main(void)
{
    for (int n = 12; n <= 24; n += 4)
    {
        long double S = recursive(n, 1);
        printf("n = %d, S(n) = %.6Lf\n", n, S);
    }
    return 0;
}
