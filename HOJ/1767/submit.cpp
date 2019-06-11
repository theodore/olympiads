#include <cstdio>

const int MaxN = 100003;
const int MaxM = 200003;
int n;
int start[MaxN], to[MaxM], next[MaxM], len[MaxM], edge;

const int BS = 1 << 21;
char buf[BS], *p = buf + BS;

#define read() \
	do { \
		if (p == buf + BS) \
			fread(p = buf, 1, BS, stdin); \
	} while(0)

#define getint(x) \
	do { \
		read(); \
		while (*p < '0' || *p > '9') \
		{ \
			++p; \
			read(); \
		} \
		x = 0; \
		while (*p >= '0' && *p <= '9') \
		{ \
			x = x * 10 + *(p++) - '0'; \
			read(); \
		} \
	} while(0)

void putint(long long x)
{
	for (; x; x /= 10)
		*(--p) = x % 10 + '0';
	*(--p) = ' ';
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

struct
{
	bool first;
	int x, fa;
	int pos, val, realtop;
	int cure;
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
			for (l = 0, r = top + 1, m = (l + r) / 2; l + 1 < r; m = (l + r) / 2)
				(g(stack[m - 1], stack[m]) < g(stack[m], x) ? l : r) = m;
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
	go(1, 0);
	p = buf + BS - 1;
	*p = '\0';
	for (int i = n; i > 2; --i)
	{
		putint(f[i]);
	}
	putint(f[2]);
	puts(p + 1);
}
