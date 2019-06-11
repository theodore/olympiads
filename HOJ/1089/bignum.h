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
		Int& operator+=(const Int&);
		Int& operator-=(const Int&);
		Int& operator*=(const Int&);
		bool operator<(const Int&) const;
		bool operator<=(const Int&) const;
		void output() const;
	//private:
		const static int MOD;
		int dig, num[10000];
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
			c *= MOD;
		int a = digof(rem.num[rem.dig-1]),
			b = digof(p.num[p.dig-1]);
		if (rem.dig == p.dig)
			for (int i = 1; i < a - b; ++i)
				c *= 10;
		else
			for (int i = 1; i < a - b + 4; ++i)
				c *= 10;
		s = c;
		while (((c + s) * p) <= rem)
			c += s;
		rem -= c * p;
		ret += c;
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

Int & Int::operator+=(const Int & p)
{
	return *this = *this + p;
}

Int & Int::operator-=(const Int & p)
{
	return *this = *this - p;
}

Int & Int::operator*=(const Int & p)
{
	return *this = *this * p;
}

#ifndef DB
void Int::output() const
{
	printf("%d", num[dig-1]);
	for (int i = dig - 2; i >= 0; --i)
		printf("%04d", num[i]);
}
#else
void Int::output() const
{
	printf("dig = %d", dig);
	for (int i = 0; i < dig; ++i)
		printf("|%d", num[i]);
}
#endif
