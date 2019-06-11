#include <cstdio>

const int maxn = 503;
int n, m;
int a[maxn], b[maxn];
bool chs[maxn];

void input(int& x, int r[])
{
	scanf("%d", &x);
	for (int i = 1; i <= x; ++i)
		scanf("%d", &r[i]);
}

int ans;
int list[maxn], lc;

bool in()
{
	int i = 0;
	for (int j = 1; i < lc && j <= m; ++j)
		if (list[i] == b[j])
			++i;
	return i == lc;
}

void dfs(const int d)
{
	if (d == n + 1)
	{
		lc = 0;
		for (int i = 1; i <= n; ++i)
			if (chs[i])
			{
				if (lc && a[i] <= list[lc - 1])
					return;
				list[lc++] = a[i];
			}
		if (lc > ans && in())
		{
			ans = lc;
#ifdef DB
			fprintf(stderr, "up ans = %d\n", lc);
			for (int i = 0; i < lc; ++i)
				fprintf(stderr, "%d ", list[i]);
			fprintf(stderr, "\n");
#endif
		}
		return;
	}
	chs[d] = true;
	dfs(d + 1);
	chs[d] = false;
	dfs(d + 1);
}

int main()
{
	input(n, a);
	input(m, b);
	dfs(1);
	printf("%d\n", ans);
}
