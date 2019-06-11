#include <cstdio>
#include <algorithm>

const int maxn(1003);
const int p(20100403);
int n, m;
int f[maxn][maxn];

int main()
{
	scanf("%d%d", &m, &n);
	f[1][1] = 1;
	for (int i = 1; i <= m + 1; ++i)
		for (int j = 1; j <= std::min(n, i) + 1; ++j)
		{
			f[i][j] += f[i][j - 1];
			f[i][j] %= p;
			if (i != j)
			{
				f[i][j] += f[i - 1][j];
				f[i][j] %= p;
			}
		}
	printf("%d\n", f[m + 1][n + 1]);
#ifdef DB
	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j <= n; ++j)
			fprintf(stderr, "%d ", f[i][j]);
		fprintf(stderr, "\n");
	}
#endif
	return 0;
}
