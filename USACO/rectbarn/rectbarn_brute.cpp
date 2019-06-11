#include <cstdio>

bool bad[100][100];

int max(int a, int b)
{
	return a > b ? a : b;
}

bool good(int a, int b, int c, int d)
{
	for (int i = a; i <= c; ++i)
		for (int j = b; j <= d; ++j)
			if (bad[i][j])
				return false;
	return true;
}

int main()
{
	freopen("rectbarn.in", "r", stdin);
	freopen("rectbarn.ans", "w", stdout);
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 0; i < p; ++i)
	{
		static int a, b;
		scanf("%d%d", &a, &b);
		bad[a][b] = true;
	}
	int ans(0);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = i; k <= n; ++k)
				for (int l = j; l <= m; ++l)
					if (good(i, j, k, l))
						ans = max(ans, (k - i + 1) * (l - j + 1));
	printf("%d\n", ans);
	return 0;
}
