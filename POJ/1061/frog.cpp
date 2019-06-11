#include <cstdio>
#include <cassert>

#ifdef unix
# define lld "%lld"
#else
# define lld "%I64d"
#endif

namespace bail
{
	void Ex_Euc_Algo(long long , long long  &, long long , long long  &, long long  &);
	bool equation(long long , long long  &, long long , long long  &, long long );
}

void bail::Ex_Euc_Algo(long long  a, long long  & x, long long  b, long long  & y, long long  & d)
{
	if (b == 0)
	{
		y = 0;
		x = 1;
		d = a;
	}
	else
	{
		Ex_Euc_Algo(b, y, a % b, x, d);
		y -= a / b * x;
	}
}

bool bail::equation(long long  a, long long  & x, long long  b, long long  & y, long long  c)
{
	long long  d;
	Ex_Euc_Algo(a, x, b, y, d);
	if (c % d == 0)
	{
		x *= c / d;
		y *= c / d;
#ifdef DB
		printf("a = "lld", x = "lld", b = "lld", y = "lld", c = "lld", d = "lld"\n", a, x, b, y, c, d);
		return true;
#endif
		b /= d;
		if (b < 0)
			b = -b;
		if (x > 0)
		{
			for (int k = 1 << 16; k >= 1; k = k >> 1)
			{
				while (x > 0)
					x -= k*b;
				x += k*b;
			}
		}
		else
		{
			for (int k = 1 << 16; k >= 1; k = k >> 1)
			{
				while (x < 0)
					x += k*b;
				x -= k*b;
			}
			x += b;
		}
		return true;
	}
	else
		return false;
}

int main()
{
#ifdef LOCAL
	freopen("frog.in", "r", stdin);
#endif
	long long  a, b, n, m, p;
	scanf(lld lld lld lld lld, &a, &b, &n, &m, &p);
	assert(p >= 0);
	// solve the equation, (n - m) * x + p * k == b - a
	long long  x, k;
	if (bail::equation(n - m, x, p, k, b - a))
		printf(""lld"\n", x);
	else
		printf("Impossible");
	return 0;
}

