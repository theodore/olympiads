#include <cstdio>
#include <algorithm>

const int maxn = 1000003;
int n, m, p, q;
int next[maxn], color[maxn];

int get_next(const int x)
{
	int fa;
	for (fa = next[x]; next[fa] != fa; fa = next[fa])
		;
	for (int i = x; i ^ next[i]; i = next[i])
		next[i] = fa;
	return fa;
}

char ans[9 * maxn], *pt = ans + 9 * maxn;
void add(int x)
{
	*(--pt) = '\n';
	if (!x)
		*(--pt) = '0';
	for (; x; x /= 10)
		*(--pt) = '0' + x % 10;
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &p, &q);
	for (int i = 0; i <= n; ++i)
		next[i] = i;
	int lb = (m > n) * (m - n) + 1;
	for (int i = m; i >= lb; --i)
	{
		int l = (i * p + q) % n, r = (i * q + p) % n;
		if (l > r)
			std::swap(l, r);
		for (int j = get_next(l); j <= r; j = get_next(j))
		{
			color[j] = i, next[j] = get_next(j + 1);
		}
	}
	for (int i = n - 1; i >= 0; --i)
		//printf("%d\n", color[i]);
		add(color[i]);
	puts(pt);
}
