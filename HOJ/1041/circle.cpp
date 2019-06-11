#include <math.h>
#include <stdio.h>

int r, ans;

int gcd(int a, int b)
{
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void Calc(int x)
{
    for (int n = 1; 2 * n * n < x; n++) {
        int m = sqrt(x - n * n);
        if (n * n + m * m == x && ((~n & 1) || (~m & 1)) && gcd(n, m) == 1)
            ans++;
    }
}

int main()
{
    scanf("%d", &r);
    int z;
    for (z = 1; z * z < r; z++)
        if (r % z == 0)
            Calc(z), Calc(r / z);
    if (z * z == r)
        Calc(z);
    printf("%d\n", ans * 8 + 4);
}
