#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef DB
# include <cstdlib>
#endif

const int MaxN = 10003;
const int MaxE = 20003;
int n, m;
int start[MaxN], to[MaxE], next[MaxE], leng[MaxE], edge;

void add(const int a, const int b, const int c)
{
	to[++edge] = b;
	leng[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

void input()
{
	edge = 0;
	memset(start, 0, sizeof start);
	for (int i = 1, a, b, c; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
}

int ans;

void dfs(const int x, const int fa, const int d)
{
	if (d <= m)
		++ans;
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa)
			dfs(to[e], x, d + leng[e]);
}

int answer()
{
	ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		--ans;
		dfs(i, 0, 0);
	}
	return ans / 2;
}

int main()
{
	while (scanf("%d%d", &n, &m), n | m)
	{
		input();
		printf("%d\n", answer());
	}
}
