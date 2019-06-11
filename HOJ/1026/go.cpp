#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>

typedef long long ll;
const int maxn = 15;
ll f[maxn][13];

void calc(const int n)
{
	for (int i = 0; i < 10; ++i)
		f[1][i] = 1;
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			for (int k = 0; k < j - 1; ++k)
				f[i][j] += f[i - 1][k];
			for (int k = j + 2; k < 10; ++k)
				f[i][j] += f[i - 1][k];
		}
		for (int k = 1; k <= 10; ++k)
			f[i][10] += f[i - 1][k];
	}
#ifdef DB
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j <= 10; ++j)
			fprintf(stderr, "%3lld", f[i][j]);
		fprintf(stderr, "\n");
	}
#endif
}

ll answer(int x)
{
	int c = 1;
	int bit[maxn];
	for (; x; x /= 10)
		bit[c++] = x % 10;
	bit[c] = 10;
	ll ans = 0;
	while (--c)
	{
		int t;
		if ((t = bit[c + 1]) == 10)
		{
			ans = f[c][10];
			for (int i = 1; i < bit[c]; ++i)
				ans += f[c][i];
		}
		else
		{
			for (int i = 0; i < std::min(t - 1, bit[c]); ++i)
				ans += f[c][i];
			for (int i = t + 2; i < std::min(10, bit[c]); ++i)
				ans += f[c][i];
			if (abs(bit[c] - bit[c + 1]) < 2)
				break;
		}
#ifdef DB
		fprintf(stderr, "c = %d, ans = %lld\n", c, ans);
#endif
	}
	return ans;
}

int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	++b;
	calc(int(log10(b)) + 1);
	std::cout << answer(b) - answer(a) << std::endl;
#ifdef DB
	fprintf(stderr, "%lld - %lld\n", answer(b), answer(a));
#endif
}
