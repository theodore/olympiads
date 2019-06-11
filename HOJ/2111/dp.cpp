#include <cstdio>

typedef long long ll;
const int maxn = 1000007;
int n, p;
ll f[maxn];
ll fact[maxn], fact_pow[maxn];

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
    fact_pow[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
	fact[i] = fact[i - 1] * i % p;
	fact_pow[i] = powmod(fact[i], p - 2, p);
    }
}

ll chs(int a, int b)
{
    return fact[a] * fact_pow[b] % p * fact_pow[a - b] % p;
}

void calc()
{
    f[0] = f[1] = 1;
    for (int i = 2, x = 0; i <= n; ++i)
    {
	// calc x
	if (i >= 3 * x + 2)
	    x = x * 2 + 1;
	f[i] = chs(i - 1, x) * f[x] % p * f[i - 1 - x] % p;
    }
}

int main()
{
    scanf("%d%d", &n, &p);
    init();
    calc();
    printf("%lld\n", f[n]);
#if DB & 1
    for (int i = 1; i <= 20; ++i)
	fprintf(stderr, "%lld\n", f[i]);
#endif
}
