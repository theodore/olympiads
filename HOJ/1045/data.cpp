#include <cstdio>
#include <cstdlib>

const int mod = 13;

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    printf("%d\n", n);
    long long a = 0;
    for (int i = 1, t; i < n; ++i)
	printf("%d\n", t = rand() % mod), a += t;
    printf("%lld\n", 2 * n - a % n);
}
