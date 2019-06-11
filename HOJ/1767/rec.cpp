#include <cstdio>

#define ever (; ; )

const int MaxN = 100003;
const int MaxM = 200003;
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

void putint(long long x)
{
	static int a[27], c;
	for (c = 1; x; x /= 10)
		a[c++] = int(x % 10);
	while (--c)
		putchar(a[c] + '0');
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
int dist[MaxN];
int stack[MaxN], top = -1;

double g(const int a, const int b)
{
	return double(f[a] - f[b]) / (dist[a] - dist[b]);
}

void dfs(const int x, const int fa)
{
	// find answer
	int l, m, r;
	if (x != 1)
	{
		for (l = 0, r = top + 1, m = (l + r) / 2; l + 1 < r; m = (l + r) / 2)
			(g(stack[m - 1], stack[m]) < vel[x] ? l : r) = m;
		int t = stack[l];
		f[x] = f[t] + mak[x] + ll(dist[x] - dist[t]) * vel[x];
	}
	// find where to go
	for (l = 0, r = top + 1, m = (l + r) / 2; l + 1 < r; m = (l + r) / 2)
		(g(stack[m - 1], stack[m]) < g(stack[m], x) ? l : r) = m;
	int pos = l + 1, val = stack[pos], realtop = top;
	stack[top = pos] = x;
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa)
		{
			dist[to[e]] = dist[x] + len[e];
			dfs(to[e], x);
		}
	// turn back
	stack[pos] = val;
	top = realtop;
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
	for (int i = 2; i < n; ++i)
	{
		putint(f[i]);
		putchar(' ');
	}
	putint(f[n]);
	putchar('\n');
}
