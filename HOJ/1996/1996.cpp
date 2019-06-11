#include <cstdio>
#ifdef LOCAL
#include <cassert>
#endif
#define N 1010
#define MOD 19650827

namespace life_is_good {
	int n, g[N];
	int ans[N][N][2];
	
	inline void input();
	inline int there_we_go();
};

inline void life_is_good::input()
{
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		scanf("%d", g + i);
}

inline int life_is_good::there_we_go()
{
	for (int i=0; i<n; ++i)
		ans[i][i+1][0] = 1;
	for (int l=2; l<=n; ++l)
		for (int i=0; i+l<=n; ++i) {
#define j (i+l)
			ans[i][j][0] = 0;
			ans[i][j][1] = 0;
			if (g[i] < g[i+1])
				ans[i][j][0] += ans[i+1][j][0];
			if (g[i] < g[j-1])
				ans[i][j][0] += ans[i+1][j][1];
			if (g[j-1] > g[i])
				ans[i][j][1] += ans[i][j-1][0];
			if (g[j-1] > g[j-2])
				ans[i][j][1] += ans[i][j-1][1];
			ans[i][j][0] %= MOD;
			ans[i][j][1] %= MOD;
#undef j
		}
	return (ans[0][n][0] + ans[0][n][1]) % MOD;
}

int main()
{
	life_is_good::input();
	printf("%d\n", life_is_good::there_we_go());
	return 0;
}

