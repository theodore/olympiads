#include <cstdio>

typedef long long ll;
const int maxn = 100;
int n, m;
long long v[maxn];
bool map[maxn][maxn];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%lld", v + i);
	for (int i = 0, a, b; i < m; ++i)
	{
		scanf("%d%d", &a, &b);
		map[a - 1][b - 1] = true;
	}
	ll ans = 0;
	int ansp = 0;
	for (int _ = 0; _ < (1 << n); ++_)
	{
		long long now = 0;
		int cnt = 0;
		for (int i = 0; i < n; ++i)
			if (_ & (1 << i))
			{
				++cnt;
				now += v[i];
				for (int j = 0; j < n; ++j)
					if (map[i][j] && !(_ & (1 << j)))
						goto next;
			}
		if (now > ans || (now == ans && ansp < cnt))
		{
			ans = now;
			ansp = cnt;
		}
next:;
	}
	printf("%d %lld\n", ansp, ans);
}
