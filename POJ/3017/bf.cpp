#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#ifdef LOCAL
# include <cassert>
# define Assert(x) assert(x)
#else
# define Assert(x) 0
#endif

typedef long long ll;
const int maxn = 100007;
const int maxN = 1 << 18;
const ll inf = ~0ull >> 1;
int n;
ll m;
int num[maxn];
ll sum[maxn], ans[maxn];
int pre[maxn];

ll calc(int x, int p)
{
    ll z = num[p];
    for (int i = x + 1; i < p; ++i)
	z = std::max<ll>(z, num[i]);
    return z + ans[x];
}

int main()
{
    stderr = stdout;
    std::cin >> n >> m;
    for (int i = 2; i <= n + 1; ++i)
    {
	scanf("%d", num + i);
	sum[i] = sum[i - 1] + num[i];
	if (num[i] > m)
	{
	    printf("-1\n");
	    return 0;
	}
    }
    for (int i = 2, j = 1; i <= n + 1; ++i)
    {
	while (sum[i] - sum[j] > m)
	    ++j;
	ans[i] = calc(j, i);
	for (int k = j + 1; k < i; ++k)
	    ans[i] = std::min<ll>(ans[i], calc(k, i));
#if DB >= 1
	fprintf(stderr, "%d %lld\n", i, ans[i]);
#endif
    }
    std::cout << ans[n + 1] << std::endl;
}
