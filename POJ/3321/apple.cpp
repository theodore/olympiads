// Using a BIT
#include <cstdio>

#define lowbit(x) ((x) & (-(x)))

const int maxn(100003);
const int maxm(200003);
int n, m;
int start[maxn], to[maxm], next[maxm], edge;
int bit[maxn];
int come[maxn], go[maxn], time;
int apple[maxn];

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void dfs(const int x, const int fa)
{
	come[x] = ++time;
	for (int e = start[x]; e; e = next[e])
		if (fa != to[e])
			dfs(to[e], x);
	go[x] = time;
}

void change(int p, int d)
{
	for (; p <= n; p += lowbit(p))
		bit[p] += d;
}

void change(int x)
{
	apple[x] ^= 1;
	if (apple[x])
		change(come[x], -1);
	else
		change(come[x], 1);
}

int sum(int p)
{
	int r(0);
	for (; p > 0; p -= lowbit(p))
		r += bit[p];
	return r;
}

int query(int x)
{
	return sum(go[x]) - sum(come[x]-1);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, a, b; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i)
	{
		bit[i] = lowbit(i);
	}
	for (scanf("%d", &m); m--; )
	{
		static char str[3];
		static int x;
		scanf("%s%d", str, &x);
		if (str[0] == 'C')
			change(x);
		else
			printf("%d\n", query(x));
	}
	return 0;
}
