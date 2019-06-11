// Using a segment tree
#include <cstdio>

#define lowbit(x) ((x) & (-(x)))

const int maxn(100003);
const int maxm(200003);
const int maxN((1<<18) + 3);
int n, m, N;
int start[maxn], to[maxm], next[maxm], edge;
int come[maxn], go[maxn], time;
int apple[maxN];

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

void change(int x)
{
	int d;
	if (apple[N + come[x]])
		d = -1;
	else
		d = 1;
	for (int i = N + come[x]; i; i >>= 1)
		apple[i] += d;
}

int query(int x)
{
	int ans(0);
	for (int l = N + come[x] - 1, r = N + go[x] + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
	{
		if (~l & 1)
			ans += apple[l^1];
		if (r & 1)
			ans += apple[r^1];
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (N = 4; N < n + 2; N <<= 1)
		;
	for (int i = N + 1; i <= N + n; ++i)
		apple[i] = 1;
	for (int i = N - 1; i; --i)
		apple[i] = apple[i<<1] + apple[(i<<1)+1];
	for (int i = 1, a, b; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
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
