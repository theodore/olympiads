/*
PROB:vans
LANG:C++
*/
#include <cstdio>
#include <cstring>

class Int
{
 public:
	 Int();
	 ~Int();
	 Int(const Int&);
	Int operator+(Int);
	Int operator=(int);
	Int operator=(Int);
	void outputln();
 private:
	static const int MOD = 1000000000;
	int num[100], bit;
};

Int::Int()
	: bit(1)
{
	memset(num, 0, sizeof(num));
	num[0] = 0;
}

Int::Int(const Int& x)
	: bit(x.bit)
{
	memset(num, 0, sizeof(num));
	for (int i = 0; i < bit; ++i)
		num[i] = x.num[i];
}

Int::~Int()
{
}

Int Int::operator+(Int x)
{
	Int ret;
	int p(0);
	int max = bit;
	if (x.bit > max)
		max = x.bit;
	for (int i = 0; i < max || p; ++i)
	{
		ret.num[i] = num[i] + x.num[i] + p;
		p = ret.num[i] / MOD;
		ret.num[i] %= MOD;
		ret.bit = i + 1;
	}
	return ret;
}

Int Int::operator=(int x)
{
	bit = 1;
	num[0] = x;
	return *this;
}

Int Int::operator=(Int x)
{
	bit = x.bit;
	//memcpy(num, x.num, sizeof(num));
	for (int i = 0; i < bit; ++i)
		num[i] = x.num[i];
	return *this;
}

void Int::outputln()
{
	printf("%d", num[bit-1]);
	for (int i = bit - 2; i >= 0; --i)
		printf("%09d", num[i]);
		//printf("%d", num[i]);
	putchar('\n');
}

Int ans[1000][7];

int main()
{
	freopen("vans.in", "r", stdin);
#ifndef LOCAL
	freopen("vans.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	if (n == 1)
	{
		printf("0\n");
		return 0;
	}
#define fu 0
#define fd 1
#define fs 2
#define tu 3
#define td 4
#define ts 5
#define tm 6
	ans[0][tu] = 1;
	for (int i = 1; i < n; ++i)
	{
		ans[i][fu] = ans[i-1][fu] + ans[i-1][tu];
		ans[i][fd] = ans[i-1][fd] + ans[i-1][td];
		ans[i][fs] = ans[i-1][fs] + ans[i-1][ts];
		ans[i][tu] = ans[i-1][fs] + ans[i-1][ts];
		ans[i][td] = ans[i-1][fs] + ans[i-1][ts];
		ans[i][ts] = ans[i-1][fu] + ans[i-1][fd] + ans[i-1][tu] + ans[i-1][td] + ans[i-1][tm];
		ans[i][tm] = ans[i-1][ts];
#undef fu
#undef fd
#undef fs
#undef tu
#undef td
#undef ts
#undef tm
	}
	Int out;
	out = ans[n-1][2] + ans[n-1][5] + ans[n-1][2] + ans[n-1][5];
	out.outputln();
	return 0;
}
