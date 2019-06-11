#include <cstdio>
#include <algorithm>

const int maxn(33);
const int INF((1u << 31) - 1);
int n;
double k, c;
int sum[maxn][maxn];
int ans[maxn][maxn];
int f[maxn];

int main()
{
	scanf("%d%lf%lf", &n, &k, &c);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &f[i]);
	}
	for (int l = 1; l <= n; ++l)
	{
#define b (a + l)
		for (int a = 1; b <= n + 1; ++a)
		{
			sum[a][b] = sum[a][b-1] + f[b-1];
			ans[a][b] = INF;
			for (int r = a; r < b; ++r)
				ans[a][b] = std::min(ans[a][b], ans[a][r] + sum[a][r] + f[r] + ans[r+1][b] + sum[r+1][b]);
		}
#undef b
	}
	printf("%.3f\n", ans[1][n+1] * k / sum[1][n+1] + c);
	return 0;
}
