#include <cstdio>
#include <cstring>

#ifdef LOCAL
# include <cassert>
# define Assert(x) assert(x)
#else
# define Assert(x) 0
#endif

typedef long long ll;
const int P = 999999599;
const int prms[] = {2, 13, 5281, 7283};
const int maxp = 7287;
int p, idx;
ll ans_arr[4];
ll fact[4][maxp], fact_pow[maxp][4];

ll powermod(ll a, ll n, ll mod)
{
    ll ret = 1, cur = a % mod;
    while (n)
    {
	if (n & 1)
	    ret *= cur, ret %= mod;
	n >>= 1;
	cur *= cur;
	cur %= mod;
    }
    return ret;
}

void ext_euc(const ll a, ll& x, const ll b, ll& y)
{
    if (b == 0)
    {
	x = 1;
	y = 0;
	return;
    }
    ext_euc(b, y, a % b, x);
    y -= a / b * x;
}

void init()
{
    for (int i = 0; i < 4; ++i)
    {
	fact[i][0] = 1;
	fact_pow[0][i] = 1;
	for (int j = 1; j < prms[i]; ++j)
	{
	    fact[i][j] = fact[i][j - 1] * j % prms[i];
	    fact_pow[j][i] = powermod(fact[i][j], prms[i] - 2, prms[i]);
	}
    }
}

ll factorial(ll x)
{
    if (x < p)
	return fact[idx][x];
    return powermod(fact[idx][p - 1], x / p, p) * fact[idx][x % p] % p
	* factorial(x / p) % p;
}

ll num_ofp(ll x)
{
    if (x < p)
	return 0;
    return x / p + num_ofp(x / p);
}

ll get_val(ll n, ll d)
{
#if DB & 1
    if (p == 13)
	fprintf(stderr, "get_val %lld %lld\n", n, d);
#endif
    ll up = num_ofp(n);
    ll down = num_ofp(d) * (n / d)  + num_ofp(n / d);
    if (up > down)
	return 0;
    Assert(up == down);
    ll x = factorial(d);
    x = powermod(x, n / d, p);
    x *= factorial(n / d);
#if DB & 1
    ll z = powermod(x, p - 2, p) * factorial(n) % p;
    if (p == 13)
	fprintf(stderr, "val is %lld\n", z);
    return z;
#endif
    return powermod(x, p - 2, p) * factorial(n) % p;
}

void calc(ll n)
{
    for (int d = 1; d * d <= n; ++d)
	if (n % d == 0)
	{
	    for (int& i = idx = 0; i < 4; ++i)
		p = prms[i], ans_arr[i] += get_val(n, d), ans_arr[i] %= p;
	    if (d * d != n)
		for (int& i = idx = 0; i < 4; ++i)
		    p = prms[i], ans_arr[i] += get_val(n, n / d), ans_arr[i] %= p;
	}
}

ll answer(ll n)
{
    calc(n);
    const int M = P - 1;
    ll ret = 0, a, m, e, s, t;
    for (int i = 0; i < 4; ++i)
    {
	a = ans_arr[i];
	m = M / prms[i];
	ext_euc(m, s, prms[i], t);
	s %= M;
	e = s * m % M;
	ret += e * a % M;
    }
    ret %= M;
    ret += M;
    return ret;
}

int main()
{
    init();
    int _;
    ll n, m;
    for (scanf("%d", &_); _--; )
    {
	scanf("%lld%lld", &n, &m);
	memset(ans_arr, 0, sizeof ans_arr);
	if (m % P == 0)
	    puts("0");
	else
	    printf("%lld\n", powermod(m, answer(n), P));
    }
    return 0;
}
