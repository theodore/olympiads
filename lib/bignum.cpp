// Implementations for "bignum.h"
#define max(a, b) ((a) > (b) ? (a) : (b))

template <int count>
Int<count>::Int()
	: dig(1)
{
	memset(num, 0, sizeof num);
}

template <int count>
Int<count>::Int(int x)
{
	memset(num, 0, sizeof num);
	for (dig = 0; x != 0; ++dig)
	{
		num[dig] = x % N;
		x /= N;
	}
	if (dig == 0)
		dig = 1;
}

template <int count>
Int<count>::Int(const Int<count>& x)
	: dig(x.dig)
{
	memcpy(num, x.num, sizeof num);
}

template <int count>
inline void Int<count>::input()
{
	memset(num, 0, sizeof num);
	char str[count*4+10];
	scanf("%s", str);
	int t;
	dig = ((t=strlen(str))-1) / 4 + 1;
	for (int i=0; i<dig; ++i)
		for (int j=max(0, t-4*i-4); j<t-4*i; ++j)
			num[i] = num[i] * 10 + str[j] - '0';
}

template <int count>
inline void Int<count>::output() const
{
	printf("%d", num[dig-1]);
	for (int i=dig-2; i>=0; --i)
		printf("%04d", num[i]);
}

template <int count>
inline void Int<count>::outputln() const
{
	output();
	printf("\n");
}

template <int count>
inline const Int<count>& Int<count>::operator=(const Int<count>& x)
{
	dig = x.dig;
	memcpy(num, x.num, sizeof num);
	return *this;
}

template <int count>
inline const Int<count>& Int<count>::operator+(const Int<count>& x) const
{
	static Int ret;
	ret = 0;
	int p(0);
#define i ret.dig
	for (i=0; p || i<max(dig, x.dig); ++i)
	{
		ret.num[i] = num[i] + x.num[i] + p;
		if ((p = (ret.num[i] / N)) != 0)
		{
			ret.num[i] %= N;
		}
#undef i
	}
	return ret;
}

template <int count>
inline const Int<count>& Int<count>::operator-(const Int<count>& x) const
{
	static Int ret;
	ret = 0;
	int p(0);
#define i ret.dig
	for (i=0; p || i<max(dig, x.dig); ++i)
	{
		if ((ret.num[i] = num[i] - x.num[i] - p) < 0)
		{
			p = 1;
			ret.num[i] += N;
		}
		else
			p = 0;

	}
#undef i
	while (ret.dig > 0 && ret.num[ret.dig-1] == 0)
		--ret.dig;
	if (ret.dig == 0)
		ret.dig = 1;
	return ret;
}

template <int count>
inline const Int<count>& Int<count>::operator*(const Int<count>& x) const
{
	static Int ret;
	ret = 0;
	int p(0);
	for (int i=0; i<x.dig; ++i)
		for (int j=0; p!=0 || j<dig; ++j)
		{
			if (i+j >= ret.dig)
				ret.dig = i + j + 1;
			ret.num[i+j] += num[j] * x.num[i] + p;
			if ((p = (ret.num[i+j] / N)) != 0)
				ret.num[i+j] %= N;
		}
	return ret;
}

template <int count>
inline const Int<count>& Int<count>::operator/(Int<count> x) const
{
	static Int ret;
	ret = 0;
	if (*this < x)
		return ret;
	Int ori(*this);
	int j;
	if (dig == x.dig)
		j = 0;
	else
	{
		j = dig - x.dig - 1;
		for (int i=0; i<j; ++i)
			x *= N;
	}
	j *= 4;
	while (ori >= x*10)
	{
		++j;
		x *= 10;
	}
	for (; j>=0; --j)
	{
		int now;
		for (now=0; ori>=x; ++now)
			ori -= x;
		ret = ret * 10 + now;
		int p(0);
		// x /= 10
		for (int i=x.dig-1; i>=0; --i)
		{
			int q = x.num[i] % 10;
			x.num[i] = x.num[i]/10 + p*N/10;
			p = q;
			if (!x.num[i] && i == x.dig-1)
				--x.dig;
		}
	}
	return ret;
}

template <int count>
inline const Int<count>& Int<count>::operator%(const Int<count>& x) const
{
	return *this - *this/x*x;
}

	template <int count>
inline const Int<count>& Int<count>::operator+=(const Int<count>& x)
{
	return (*this = (*this + x));
}

	template <int count>
inline const Int<count>& Int<count>::operator-=(const Int<count>& x)
{
	return (*this = (*this - x));
}

	template <int count>
inline const Int<count>& Int<count>::operator*=(const Int<count>& x)
{
	return (*this = (*this * x));
}

	template <int count>
inline const Int<count>& Int<count>::operator/=(const Int<count>& x)
{
	return (*this = (*this / x));
}

	template <int count>
inline const Int<count>& Int<count>::operator%=(const Int<count>& x)
{
	return (*this = (*this % x));
}

template <int count>
inline bool Int<count>::operator<(const Int<count>& x) const
{
	if (dig < x.dig)
		return true;
	else if (dig > x.dig)
		return false;
	else
		for (int i=dig-1; i>=0; --i)
			if (num[i] < x.num[i])
				return true;
			else if (num[i] > x.num[i])
				return false;
	return false;
}

template <int count>
inline bool Int<count>::operator<=(const Int<count>& x) const
{
	return *this < x || *this == x;
}

template <int count>
inline bool Int<count>::operator>(const Int<count>& x) const
{
	if (dig > x.dig)
		return true;
	else if (dig < x.dig)
		return false;
	else
		for (int i=dig-1; i>=0; --i)
			if (num[i] > x.num[i])
				return true;
			else if (num[i] < x.num[i])
				return false;
	return false;
}

template <int count>
inline bool Int<count>::operator>=(const Int<count>& x) const
{
	return *this > x || *this == x;
}

template <int count>
inline bool Int<count>::operator==(const Int<count>& x) const
{
	if (dig != x.dig)
		return false;
	for (int i=0; i<dig; ++i)
		if (num[i] != x.num[i])
			return false;
	return true;
}

template <int count>
inline bool Int<count>::operator!=(const Int<count>& x) const
{
	return !(*this == x);
}

#undef max
