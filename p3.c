/* CS100 Fall 2026 - HW2 Problem 3: Polynomial evaluation
 *
 * Evaluate P(x) at m given points; print each value rounded to 3 decimals.
 * An array is enough for the coefficients; do not use heap memory and do
 * not use <math.h> (your program is not linked against the math library).
 * Do not rename this file.
 */
#include <stdio.h>

int main(void)
{
    int n, m;
    double a[32], x;

    scanf("%d", &n);
    for (int i = 0; i <= n; i += 1) {
        scanf("%lf", &a[i]);
    }
    
    scanf("%d", &m);
    for (int i = 0; i < m; i += 1) {
        scanf("%lf", &x);
        double ans = a[0], xn = x;
        for (int j = 1; j <= n; j += 1) {
            ans += a[j] * xn;
            xn *= x;
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}
