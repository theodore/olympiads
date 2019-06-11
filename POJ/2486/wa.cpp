#include <cstdio>
#include <cstring>

const int maxn(103);
const int maxm(203);
int n, k;
int amount[maxn];
int start[maxn], to[maxm], next[maxm], edge;
int f[maxn];
int ans;

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void input()
{
	for (int i = 1; i <= n; ++i)
		scanf("%d", &amount[i]);
	edge = 0;
	memset(start, 0, sizeof start);
	for (int i = 1, a, b; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
}

void search(int x, int fa, int d)
{
	if (d > k)
		return;
	f[x] = f[fa] + amount[x];
	if (f[x] > ans)
		ans = f[x];
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa)
			search(to[e], x, d + 1);
}

int main()
{
	while (scanf("%d%d", &n, &k) != EOF)
	{
		input();
		ans = 0;
		search(1, 0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
