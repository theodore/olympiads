// 6:26 PM
#include <cstdio>

const int N(100010);
int c[N], ans[N];
int n, act[N];
int start[N], to[2*N], next[2*N], cnt;
bool vis[N];

void adde(int a, int b)
{
	to[++cnt] = b;
	next[cnt] = start[a];
	start[a] = cnt;
}

void add(int x, int d)
{
	for (int i = x; i <= n; i += i & -i)
		c[i] += d;
}

int sum(int x)
{
	int ret(0);
	for (int i = x; i; i -= i & -i)
		ret += c[i];
	return ret;
}

void dfs(const int x)
{
	vis[x] = true;
	const int & ax = act[x];
	ans[ax] = sum(ax);
	add(ax, 1);
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
			dfs(to[e]);
	add(ax, -1);
}

int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		static int a, b;
		scanf("%d%d", &a, &b);
		adde(a, b);
		adde(b, a);
	}
	for (int i = 1; i <= n; ++i)
	{
		static int t;
		scanf("%d", &t);
		act[t] = i;
	}
	dfs(1);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
