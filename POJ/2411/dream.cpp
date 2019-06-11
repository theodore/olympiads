#include <cstdio>

#ifdef unix
# define lld "%lld"
#else
# define lld "%I64d"
#endif

//#define lowbit(x) ((x) & (-(x)))
int lowbit(int x)
{
	return x & -x;
}

const int maxn(13);
const int maxM((1 << 11) + 1);
int n, m, M;
long long ans[maxn][maxM];

bool nice(int x)
{
	int t, s;
	while (x)
	{
		t = lowbit(x);
		s = lowbit(x - t);
		if (s != t << 1)
			return false;
		else
			x -= s + t;
	}
	return true;
}

void dp()
{
	int t, s;
	ans[1][0] = 1;
	for (int j = 1; j <= M; ++j)
	{
		t = lowbit(j);
		s = lowbit(j - t);
		if (s == t << 1)
			ans[1][j] = ans[1][j - t - s];
		else
			ans[1][j] = 0;
	}
	for (int i = 2; i <= n; ++i)
	{
		ans[i][0] = ans[i-1][M];
		for (int j = 1; j <= M; ++j)
		{
			ans[i][j] = 0;
			for (int k = 0; k <= M; ++k)
				if ((j | k) == M && nice(j & k))
					ans[i][j] += ans[i-1][k];
		}
	}
}

int main()
{
	for (scanf("%d%d", &n, &m); n && m; scanf("%d%d", &n, &m))
	{
		if (n * m & 1)
			printf("0\n");
		else
		{
			M = (1 << m) - 1;
			dp();
			printf(lld"\n", ans[n][M]);
		}
	}
	return 0;
}
