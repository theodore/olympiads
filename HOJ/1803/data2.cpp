#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int maxn(100010);
int a[maxn];
int f[maxn];
int l[maxn], lc;
int size[maxn];
int start[maxn], to[maxn*2], next[maxn*2], edge;

int cmp(const void*, const void*)
{
	return rand() & 1;
}

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

int ff(int x)
{
	if (x != f[x])
		return f[x] = ff(f[x]);
	else
		return x;
}

void join(int a, int b)
{
	if (f[b] != b)
	{
		int t = f[b];
		f[b] = a;
		join(a, t);
	}
	else
	{
		f[b] = ff(a);
	}
}

bool vis[maxn];

void go(int x)
{
	vis[x] = true;
	size[x] = 1;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
		{
			go(to[e]);
			size[x] += size[to[e]];
		}
}

int main()
{
	freopen("in", "w", stdout);
	int n, r, m;
	scanf("%d%d%d", &r, &n, &m);
#ifdef DB
	srand(r * n * m);
#else
	srand(r * n * m * time(0));
#endif
	printf("%d\n", n);
	for (int i = 1; i <= n; ++i)
	{
		l[lc++] = i;
		f[i] = i;
		a[i] = i;
	}
	qsort(a + 1, n, 4, cmp);
	for (int i = 1; i <= n; ++i)
		printf("%d\n", a[i]);
	putchar(10);
	for (; lc != 1; --lc)
	{
		int a = rand() % lc, b = rand() % lc;
		if (a == b)
		{
			++b;
			if (b == lc)
				b = 0;
		}
		printf("%d %d\n", l[a], l[b]);
		add(l[a], l[b]);
		add(l[b], l[a]);
		if (a > b)
			std::swap(a, b);
		join(l[a], l[b]);
		for (int i = b; i < lc - 1; ++i)
			l[i] = l[i + 1];
	}
	go(1);
	for (printf("\n%d\n", m); m--; )
	{
		int x = rand() % n + 1;
		printf("%d %d\n", x, rand() % size[x] + 1);
	}
	return 0;
}
