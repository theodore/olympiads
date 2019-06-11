#include <cstdio>

const int INF = -1u >> 1;
const int maxn = 10003;
int n, m;
int sf[maxn], st[maxn];
int f[maxn];

void input()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, a, b; i <= n; ++i)
	{
		scanf("%d%d", &a, &b);
		st[i] = st[i - 1] + a;
		sf[i] = sf[i - 1] + b;
	}
}

#define TimOrz(i, x) (f[x] + (m + st[i] - st[x]) * (sf[n] - sf[x]))

void dp()
{
	for (int i = 1; i <= n; ++i)
	{
		f[i] = INF;
		for (int j = i - 1, t; j >= 0; --j)
			if ((t = TimOrz(i, j)) < f[i])
				f[i] = t;
	}
}

int main()
{
	input();
	dp();
	printf("%d\n", f[n]);
}
