#include <cstdio>
#include <cstring>
#include <iostream>

namespace
{
    typedef long long ll;
    const int maxn = 13;
    const int maxd = 1003;
    const int maxs = (1 << 10) + 7;
    int n, d;
    char s[maxn];
    ll f[maxs][maxd];
    ll pow[maxn];
    ll ff(int, int);
    void initpow()
    {
	pow[0] = 1;
	for (int i = 1; i <= 10; ++i)
	    pow[i] = pow[i - 1] * 10;
    }
}

namespace
{
    ll ff(int z, int m)
    {
	ll& x = f[z][m];
	if (x != -1)
	    return x;
	if (z == 0)
	    return x = (m == 0);
	x = 0;
	bool used[maxn];
	memset(used, 0, sizeof used);
	int dig = -1;
	for (int i = 0; i < n; ++i)
	    dig += (z >> i) & 1;
	for (int i = 0; i < n; ++i)
	    if (z & (1 << i) && !used[s[i] - '0'])
	    {
		ll t;
		used[t = s[i] - '0'] = true;
		t *= pow[dig];
		t %= d;
		x += ff(z ^ (1 << i), int(((m - t) + d) % d));
	    }
	return x;
    }
}

int main()
{
    initpow();
    int _;
    for (scanf("%d", &_); _--; )
    {
	scanf("%s%d", s, &d);
	n = strlen(s);
	memset(f, -1, sizeof f);
	std::cout << ff((1 << n) - 1, 0) << std::endl;
    }
}
