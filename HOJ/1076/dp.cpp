#include <cstdio>
#include <algorithm>

const int maxm = 103;
const int maxn = 17;
const int maxs = (1 << 15) + 7;
int n, m;
int prerequisite[maxn];
double f[maxm][maxs];
int v[maxn];

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 0, x; i < n; ++i)
	{
		scanf("%d", &v[i]);
		while (scanf("%d", &x), x)
			prerequisite[i] |= 1 << (x - 1);
	}
	for (int i = m - 1; i >= 0; --i)
		for (int j = 0; j < (1 << n); ++j)
		{
			for (int k = 0; k < n; ++k)
				if ((j & prerequisite[k]) == prerequisite[k] && f[i + 1][j | (1 << k)] + v[k] > f[i + 1][j])
					f[i][j] += f[i + 1][j | (1 << k)] + v[k];
				else
					f[i][j] += f[i + 1][j];
			f[i][j] /= n;
		}
	printf("%.6f\n", f[0][0]);
}
