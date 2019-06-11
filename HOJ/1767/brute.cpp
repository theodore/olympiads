#include <cstdio>

const int MaxN = 10003;
const int MaxM = 20003;
int n;
int start[MaxN], to[MaxM], next[MaxM], len[MaxM], edge;

void getint(int& x)
{
	static int ch;
	while ((ch = getchar()) < '0' || ch > '9')
		;
	x = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		x = x * 10 + ch - '0';
}

void add(const int a, const int b, const int c)
{
	to[++edge] = b;
	len[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

typedef long long ll;
ll f[MaxN];
int mak[MaxN], vel[MaxN];
int father[MaxN];
int dist[MaxN];

void dfs(const int x, const int fa)
{
	father[x] = fa;
	f[x] = f[fa] + mak[x] + ll(dist[x] - dist[fa]) * vel[x];
	long long t;
	for (int i = father[fa]; i; i = father[i])
		if ((t = f[i] + mak[x] + ll(dist[x] - dist[i]) * vel[x]) < f[x])
			f[x] = t;
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa)
		{
			dist[to[e]] = dist[x] + len[e];
			dfs(to[e], x);
		}
}

int main()
{
	getint(n);
	for (int i = 1, a, b, c; i < n; ++i)
	{
		getint(a);
		getint(b);
		getint(c);
		add(a, b, c);
		add(b, a, c);
	}
	for (int i = 2; i <= n; ++i)
	{
		getint(mak[i]);
		getint(vel[i]);
	}
	dfs(1, 0);
#warning You can optimize output
	for (int i = 2; i < n; ++i)
		printf("%lld ", f[i]);
	printf("%lld\n", f[n]);
}
