#include <cstdio>

int gcd(int a, int b)
{
    while (b)
    {
	int t = a % b;
	a = b;
	b = t;
    }
    return a;
}

long long  lcm(int a, int b)
{
    return (long long )a / gcd(a, b) * b;
}

long long int ans(int n)
{
    long long  z = 0;
    for (int i = 1; i <= n; ++i)
    {
	z += lcm(i, n);
	//fprintf(stderr, "%d %lld\n", i, z);
    }
    return z;
}

int main()
{
    int a, b;
    scanf("%d", &a);
    for (int i = 0; i < a; ++i)
	scanf("%d", &b),
    printf("%lld\n", ans(b));
}
