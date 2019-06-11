#include <cstdio>
#include <cstdlib>

#ifdef LOCAL
# define lld "%lld"
#else
# define lld "%I64d"
#endif

typedef long long ll;

const int maxb(2063);
ll base[maxb];
int bc;

void get_base(const ll x, const ll p)
{
	if (p + 6 <= x)
	{
		base[bc++] = p + 6;
		if (p + 8 <= x)
		{
			base[bc++] = p + 8;
			get_base(x, (p + 6) * 10);
			get_base(x, (p + 8) * 10);
		}
	}
}

ll gcd(ll a, ll b)
{
	ll t;
	while (b)
	{
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

ll lcm(ll a, ll b)
{
	return a / gcd(a, b) * b;
}

ll calc(const ll x)
{
	if (x == 0)
		return 0;
	int n = -1;
	for (int i = 0; i < bc; ++i)
		if (base[i] > x)
		{
			n = i;
			break;
		}
	if (n == -1)
		n = bc;
	ll ans(0);
	for (ll i = 1; i < (1ll << n); ++i)
	{
		ll now = 1;
		int cnt(0);
		for (int j = 0; j < n; ++j)
			if (i & (1ll << j))
			{
				++cnt;
				now = lcm(now, base[j]);
			}
		if (cnt & 1)
			ans += x / now;
		else
			ans -= x / now;
	}
	return ans;
}

int cmp(const void* a, const void* b)
{
	return (*(ll*)a - *(ll*)b > 0) ? 1 : -1;
}

int main()
{
	ll a, b;
	scanf(lld lld, &a, &b);
	get_base(b, 0);
#ifdef DB
	fprintf(stderr, "bc = %d\n", bc);
#endif
	qsort(base, bc, sizeof base[0], cmp);
	printf(lld"\n", calc(b) - calc(a));
	return 0;
}
