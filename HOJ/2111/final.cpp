#include <cstdio>

typedef long long ll;
const int maxn = 1000007;
int n, p;
ll f[maxn];
ll fact[maxn];

ll powmod(ll a, int x, int m)
{
    ll r = 1, c = a % m;
    while (x)
    {
	if (x & 1)
	    r *= c, r %= m;
	c *= c;
	c %= m;
	x >>= 1;
    }
    return r;
}

void init()
{
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
	fact[i] = fact[i - 1] * i % p;
}

ll chs(int a, int b)
{
    return fact[a] * powmod(fact[b], p - 2, p) % p
	* powmod(fact[a - b], p - 2, p) % p;
}

ll ff(int z)
{
    if (f[z])
	return f[z];
    int x = 1;
    while ((x << 1) + 1 <= z)
	x <<= 1, ++x;
    if (z - x <= x / 2)
	x /= 2;
    return f[z] = chs(z - 1, x) * ff(x) % p * ff(z - 1 - x) % p;
}

int main()
{
    scanf("%d%d", &n, &p);
    init();
    f[0] = f[1] = 1;
    printf("%lld\n", ff(n));
#if DB & 1
    for (int i = 1; i <= 20; ++i)
	fprintf(stderr, "%lld\n", ff(i));
#endif
}
