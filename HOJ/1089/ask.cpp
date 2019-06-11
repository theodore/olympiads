#include <cstdio>
#include <cstdlib>
#include <cstring>
#define max(a, b) ((a) > (b) ? (a) : (b))

class Int
{
	public:
		Int();
		Int(int);
		Int(const Int&);
		~Int();
		Int operator+(const Int&) const;
		Int operator-(const Int&) const;
		Int operator*(const Int&) const;
		Int operator/(const Int&) const;
		Int& operator=(const Int&);
		/*
		Int& operator+=(const Int&);
		Int& operator-=(const Int&);
		*/
		Int& operator*=(const Int&);
		bool operator<(const Int&) const;
		bool operator<=(const Int&) const;
		void output() const;
	private:
		const static int MOD;
		int dig, num[100];
};

const int Int::MOD(10000);

Int::Int()
	: dig(1)
{
	memset(num, 0, sizeof(num));
}

Int::Int(int x)
{
	memset(num, 0, sizeof(num));
	for (dig = 0; x != 0; ++dig)
	{
		num[dig] = x % MOD;
		x /= MOD;
	}
	if (dig == 0)
		dig = 1;
}

Int::Int(const Int & p)
{
	dig = p.dig;
	memcpy(num, p.num, sizeof(num));
}

Int::~Int()
{
}

bool Int::operator<(const Int & p) const
{
	if (dig != p.dig)
		return dig < p.dig;
	for (int i = dig - 1; i >= 0; --i)
		if (num[i] != p.num[i])
			return num[i] < p.num[i];
	return false;
}

bool Int::operator<=(const Int & p) const
{
	if (dig != p.dig)
		return dig < p.dig;
	for (int i = dig - 1; i >= 0; --i)
		if (num[i] != p.num[i])
			return num[i] < p.num[i];
	return true;
}

Int Int::operator+(const Int & p) const
{
	Int ret;
	ret.dig = max(dig, p.dig);
	int c(0);
	for (int i = 0; i < ret.dig; ++i)
	{
		ret.num[i] = num[i] + p.num[i] + c;
		c = ret.num[i] / MOD;
		ret.num[i] %= MOD;
	}
	if (c)
		ret.num[ret.dig++] = c;
	return ret;
}

// Assumes *this >= p
Int Int::operator-(const Int & p) const
{
	Int ret;
	int c = 0;
	for (int i = 0; i < dig; ++i)
	{
		ret.num[i] = num[i] - p.num[i] - c;
		c = 0;
		if (ret.num[i] < 0)
		{
			ret.num[i] += MOD;
			c = 1;
		}
	}
	for (int i = 99; i >= 0; --i)
		if (ret.num[i])
		{
			ret.dig = i + 1;
			return ret;
		}
	ret.dig = 1;
	return ret;
}

Int Int::operator*(const Int & p) const
{
	Int ret;
	int & d = ret.dig = dig + p.dig - 1, c(0);
	for (int i = 0; i < dig; ++i)
		for (int j = 0; j < p.dig; ++j)
		{
			c = num[i] * p.num[j];
			for (int k = i + j; c != 0; ++k)
			{
				ret.num[k] += c;
				c = ret.num[k] / MOD;
				ret.num[k] %= MOD;
				d = max(d, k + 1);
			}
		}
	return ret;
}

int digof(int x)
{
	if (x < 10)
		return 1;
	if (x < 100)
		return 2;
	if (x < 1000)
		return 3;
	if (x < 10000)
		return 4;
	exit(1);
}

Int Int::operator/(const Int & p) const
{
	Int rem(*this), ret, c, s;
	while (!(rem < p))
	{
		c = 1;
		for (int i = 1; i < rem.dig - p.dig; ++i)
			c = c * MOD;
		int a = digof(rem.num[rem.dig-1]),
			b = digof(p.num[p.dig-1]);
		if (rem.dig == p.dig)
			for (int i = 1; i < a - b; ++i)
				c = c * 10;
		else
			for (int i = 1; i < a - b + 4; ++i)
				c = c * 10;
		s = c;
		while (((c + s) * p) <= rem)
			c = c + s;
		rem = rem - c * p;
		ret = ret + c;
	}
	return ret;
}

Int & Int::operator=(const Int & p)
{
	if (this == &p)
		return *this;
	dig = p.dig;
	memcpy(num, p.num, sizeof(num));
	return *this;
}

/*
Int & Int::operator+=(const Int & p)
{
	return *this = *this + p;
}

Int & Int::operator-=(const Int & p)
{
	return *this = *this - p;
}
*/

Int & Int::operator*=(const Int & p)
{
	return *this = *this * p;
}

void Int::output() const
{
	printf("%d", num[dig-1]);
	for (int i = dig - 2; i >= 0; --i)
		printf("%04d", num[i]);
}


int d, n;
Int fact[33], comb[33], ans[17], sum[17];

inline void calc_comb()
{
	fact[0] = 1;
	for (int i=1; i<=n; ++i)
		fact[i] = fact[i-1] * i;
	for (int i=0; i<=n; ++i)
		comb[i] = fact[n] / (fact[i] * fact[n-i]);
}

#ifdef DB
inline void debug()
{
	for (int i=0; i<=n; ++i)
	{
		printf("fact[%d] = ", i);
		fact[i].output();
		putchar('\n');
	}
	putchar('\n');
	for (int i=0; i<=n; ++i)
	{
		printf("comb[%d] = ", i);
		comb[i].output();
		putchar('\n');
	}
	exit(0);
}
#endif

inline void go()
{
	calc_comb();
#ifdef DB
	debug();
#endif
	ans[0] = 1;
	for (int i=1; i<d; ++i)
		sum[i] = 1;
	for (int i=1; i<=d; ++i)
	{
		for (int j=1; j<=n; ++j)
		{
			Int t(ans[i-1]), s(1);
			for (int k=1; k<j; ++k)
				//t = t * ans[i-1];
				t *= ans[i-1];
			for (int k=0; k<n-j; ++k)
				s = s * sum[i-1];
			ans[i] = ans[i] + comb[j] * t * s;
		}
		/*
		if (i < d - 1)
			sum[i+1] += ans[i];
		*/
		for (int j = i + 1; j < d; ++j)
			sum[j] = sum[j] + ans[i];
	}
}

// Notice: n == 0? d == 0?
int main()
{
#ifdef LOCAL
#ifndef GDB
	freopen("out", "w", stdout);
#endif
#endif
	scanf("%d%d", &n, &d);
	go();
	ans[d].output();
	putchar(10);
	return 0;
}

