#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn(2003);
const int maxm(2003);
int n, m, w;
int f[maxn][maxm];

int main()
{
	scanf("%d%d%d", &n, &m, &w);
	memset(f[0], 0xc0, sizeof f[0]);
	f[0][0] = 0;
	for (int i = 1, prc_b, prc_s, lim_b, lim_s; i <= n; ++i)
	{
		scanf("%d%d%d%d", &prc_b, &prc_s, &lim_b, &lim_s);
		for (int j = 0; j <= m; ++j)
		{
			f[i][j] = f[i - 1][j];
			for (int k = std::max(0, j - lim_b), t; k <= std::min(m, j + lim_s); ++k)
				if ((t = f[std::max(0, i - w - 1)][k] + (k - j) * (k > j ? prc_s : prc_b)) > f[i][j])
					f[i][j] = t;
		}
	}
	printf("%d\n", f[n][0]);
	return 0;
}
