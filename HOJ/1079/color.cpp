#include <cstdio>

typedef long long ll;
const int maxn = 16;
const int maxc = 6;
const int mod = 1000000007;
int f[maxn][maxn][maxn][maxn][maxn][maxc];

int ff(int i[], int j)
{
#define F f[i[1]][i[2]][i[3]][i[4]][i[5]][j]
	if (F)
		return F;
	ll a = 0;
	int ii[maxc];
	for (int u = 1; u <= 5; ++u)
		ii[u] = i[u] - (u == j) + (u + 1 == j);
	for (int u = 1; u <= 5; ++u)
		if (ii[u])
			a = (a + ff(ii, u) * ll(ii[u] - (u + 1 == j))) % mod;
	return F = int(a);
#undef F
}

int main()
{
	int _, x, l[maxc] = {0};
	for (scanf("%d", &_); _--; )
	{
		scanf("%d", &x);
		++l[x];
	}
	f[1][0][0][0][0][1] = 1;
	ll ans = 0;
	for (int i = 1; i <= 5; ++i)
		if (l[i])
			ans = (ans + ff(l, i) * ll(l[i])) % mod;
	printf("%d\n", int(ans));
}
