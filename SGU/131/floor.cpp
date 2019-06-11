#include <cstdio>

#ifdef unix
# define lld "%lld"
#else
# define lld "%I64"
#endif

const int maxn(11);
const int maxM((1 << 9) + 3);
const int fill[][2] =
{ {0, 0}, {1, 1}, {0, 3}, {1, 3}, {2, 3}, {3, 1}, {3, 2} };
int n, m, M;
long long ans[maxn][maxM];
int cur;

void dfs(const int pos, const int pre, const int now)
{
	if (pos == m)
	{
		ans[cur][now] += ans[cur-1][~pre & M];
		return;
	}
	for (int i = 0; i < 7; ++i)
	{
		if ((pos + 1 < m || (fill[i][0] < 2 && fill[i][1] < 2))
				&& ((fill[i][0] & 3) & ((pre >> pos) & 3)) == 0
				&& ((fill[i][1] & 1) & ((now >> pos) & 1)) == 0)
		{
			dfs(pos + 1, pre | (fill[i][0] << pos), now | (fill[i][1] << pos));
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	/*
	if (n < m)
	{
		n ^= m;
		m ^= n;
		n ^= m;
	}
	*/
	M = (1 << m) - 1;
	/*
	ans[0][0] = 1;
	cur = 1;
	dfs(0, M, 0);
	*/
	ans[0][M] = 1;
	for (cur = 1; cur <= n; ++cur)
	{
		dfs(0, 0, 0);
	}
	printf(lld"\n", ans[n][M]);
	return 0;
}
