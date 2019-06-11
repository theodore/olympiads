#include <cstdio>
#include <cmath>

int main()
{
    long long n;
    scanf("%lld", &n);
    unsigned long long z = sqrt(n);
    while (z * z > n)
        z--;
    while (z * z < n)
        z++;
    printf("%lld\n", z);
}
