#include <cstdio>

typedef long long ll;
const int P = 999911659;
const int prms[] = {2, 3, 4679, 35617};
const int maxp = 35623;
int idx, p;
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

ll bino(ll n, ll m)
{
    if (m > n)
	return 0;
    return fact[idx][n] * fact_pow[m][idx] % p * fact_pow[n - m][idx] % p;
}

ll get_val(ll n, ll m)
{
    if (m == 0)
	return 1;
    ll ret = bino(n % p, m % p);
    if (ret)
	ret *= get_val(n / p, m / p), ret %= p;
    return ret;
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
		    p = prms[i], ans_arr[i] += get_val(n, n / d),
		      ans_arr[i] %= p;
	}
}

ll answer(ll n)
{
    calc(n);
    const int M = P - 1;
    ll ret(0), a, e, m, s, t;
    for (int i = 0; i < 4; ++i)
    {
	//a = calc(n, i);
	a = ans_arr[i];
	m = M / prms[i];
	ext_euc(m, s, prms[i], t);
	s %= M;
	e = s * m % M;
	ret += e * a % M;
    }
    ret %= M;
    ret += M;
    return ret % M;
}

int main()
{
    init();
    ll n, g;
    scanf("%lld%lld", &n, &g);
    if (g % P == 0)
	puts("0");
    else
	printf("%lld\n", powermod(g, answer(n), P));
}
// vim:ts=8
