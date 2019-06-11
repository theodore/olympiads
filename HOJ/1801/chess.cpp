#include <cstdio>

typedef long long ll;
const int maxn = 103;
const int mod = 9999973;
int n, m;
ll f[maxn][maxn][maxn];

int main()
{
    scanf("%d%d", &n, &m);
    f[0][m][0] = 1;
    for (int i = 1; i <= n; ++i)
	for (int j = 0; j <= m; ++j)
	    for (int k = 0; j + k <= m; ++k)
	    {
		const ll (*const g)[maxn] = f[i - 1];
		ll& x = f[i][j][k] = g[j][k];
		if (k)
		    x = (x + g[j + 1][k - 1] * (j + 1)) % mod; // add to 0
		if (j + k < m)
		    x = (x + g[j][k + 1] * (k + 1)) % mod; // to 1
		if (k >= 2)
		    x = (x + g[j + 2][k - 2] * (j + 2) * (j + 1) / 2) % mod; // to 0, 0
		if (k && j + k < m)
		    x = (x + g[j + 1][k] * (j + 1) * k) % mod; // to 0, 1
		if (j + k < m - 1)
		    x = (x + g[j][k + 2] * (k + 2) * (k + 1) / 2) % mod; // to 1, 1
	    }
    ll ans = 0;
    for (int j = 0; j <= m; ++j)
	for (int k = 0; j + k <= m; ++k)
	    ans = (ans + f[n][j][k]) % mod;
    printf("%d\n", int(ans));
}
