#include <cstdio>
#include <algorithm>

const int maxn = 53;
const int maxt = 2503;
int n, m, t;
int f[maxt];
int g[maxn][maxn];

int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 1; i <= n; ++i)
	{
		char s[maxn];
		scanf("%s", s + 1);
		for (int j = 1; j <= m; ++j)
			for (int k = 1; k <= j; ++k)
			{
				//g[j][k] = g[j - 1][k];
				g[j][k] = 0;
				for (int l = j, one = 0; l >= 1; --l)
				{
					one += s[l] == '1';
					g[j][k] = std::max(g[j][k], g[l - 1][k - 1] + std::max(one, j - l + 1 - one));
				}
			}
		for (int j = t; j >= 1; --j)
			for (int k = 1; k <= std::min(j, m); ++k)
			{
				f[j] = std::max(f[j], f[j - k] + g[m][k]);
#ifdef DB
				fprintf(stderr, "g[m][%d] = %d\n", k, g[m][k]);
#endif
			}
	}
	printf("%d\n", f[t]);
}
