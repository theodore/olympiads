#include <cstdio>

const int maxn(200003);
const int maxm(400003);
int n;
int f[maxn][23];
int start[maxn], to[maxm], next[maxm], edge;

void add(const int a, const int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void dfs(const int x, const int fa)
{
	int g[23];
	for (int i = 1; i <= 19; ++i)
		g[i] = i;
	for (int e = start[x]; e; e = next[e])
	{
		if (to[e] != fa)
		{
			dfs(to[e], x);
			for (int i = 1; i <= 19; ++i)
				g[i] += f[to[e]][i];
		}
	}
	f[x][1] = g[2];
	for (int i = 2; i <= 19; ++i)
		f[x][i] = g[i - 1];
	for (int i = 1; i <= 19; ++i)
		for (int j = 1; j <= 19; ++j)
			if (i != j && g[j] < f[x][i])
				f[x][i] = g[j];
}

int main()
{
#ifndef LOCAL
#endif
	scanf("%d", &n);
	for (int i = 1, a, b; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	if (f[1][2] < f[1][1])
		f[1][1] = f[1][2];
	printf("%d\n", f[1][1]);
	return 0;
}
