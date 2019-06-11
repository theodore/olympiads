#include <cstdio>

const int maxn = 103;
int n;
int ans[maxn][maxn];
int son[maxn][2];

void input()
{
	scanf("%d", &n);
	for (int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		son[x % 100][x / 100] = i;
	}
}

int dfs(int x)
{
	static bool hash = false;
	if (!x && hash)
		return 0;
	hash = true;
	int a, b, as, bs;
	as = dfs(a = son[x][0]);
	bs = dfs(b = son[x][1]);
	int i = 0, j = 0, k = 0;
	if (as == bs || as > bs + 1)
	{
		while (as != bs + j)
			ans[x][i++] = ans[a][j++];
		ans[x][i] = x;
		while (j < as)
		{
			ans[x][++i] = ans[b][k++];
			ans[x][++i] = ans[a][j++];
		}
	}
	else
	{
		while (as + k != bs + 1)
			ans[x][i++] = ans[b][k++];
		ans[x][i] = x;
		while (k < bs)
		{
			ans[x][++i] = ans[a][j++];
			ans[x][++i] = ans[b][k++];
		}
		ans[x][++i] = ans[a][j];
	}
	return i + 1;
}

int main()
{
	input();
	dfs(0);
	for (int i = 0; i < n; ++i)
		printf("%d ", ans[0][i]);
	printf("%d\n", ans[0][n]);
}
