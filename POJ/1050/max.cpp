#include <cstdio>

const int maxn(103);
int n;
int a[maxn][maxn];
int sum[maxn][maxn];

int main()
{
	scanf("%d", &n);
	int ans(-999999999), t;
	for (int i = 1, line = 0; i <= n; ++i, line = 0)
		for (int j = 1; j <= n; ++j)
		{
			scanf("%d", &a[i][j]);
			line += a[i][j];
			sum[i][j] = sum[i-1][j] + line;
			for (int x = 0; x < i; ++x)
				for (int y = 0; y < j; ++y)
					if ((t = (sum[i][j] + sum[x][y] - sum[i][y] - sum[x][j])) > ans)
						ans = t;
		}
	printf("%d\n", ans);
	return 0;
}
