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

#if 0
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
#endif

struct
{
	bool first;
	int x, fa;
	int pos, val, realtop;
	int cure;
#ifdef DB
	void output()
	{
		fprintf(stderr, "first = %d, x = %d, fa = %d, pos = %d, val = %d, realtop = %d, cure = %d\n",
				first, x, fa, pos, val, realtop, cure);
	}
#endif
} S[MaxN];
int Stop;

void go(int x, int fa)
{
	S[Stop = 1].first = true;
	S[Stop].x = x;
	S[Stop].fa = fa;
	S[Stop].cure = start[x];
	int l, m, r;
	while (Stop)
	{
Again:
#ifdef DB
		fprintf(stderr, "Stop = %d\n", Stop);
		S[Stop].output();
		int abcdefg;
		scanf("%d", &abcdefg);
#endif
		x = S[Stop].x;
		fa = S[Stop].fa;
		if (S[Stop].first)
		{
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
			//int pos = l + 1, val = stack[pos], realtop = top;
			S[Stop].pos = l + 1;
			S[Stop].val = stack[l + 1];
			S[Stop].realtop = top;
			stack[top = l + 1] = x;
			S[Stop].first = false;
		}
		for (int e = S[Stop].cure; e; e = next[e])
			if (to[e] != fa)
			{
				dist[to[e]] = dist[x] + len[e];
				S[Stop].cure = next[e];
				S[++Stop].x = to[e];
				S[Stop].fa = x;
				S[Stop].first = true;
				S[Stop].cure = start[to[e]];
				goto Again;
			}
		// turn back
		stack[S[Stop].pos] = S[Stop].val;
		top = S[Stop].realtop;
		--Stop;
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
	//dfs(1, 0);
	go(1, 0);
	for (int i = 2; i < n; ++i)
	{
		putint(f[i]);
		putchar(' ');
	}
	putint(f[n]);
	putchar('\n');
}
