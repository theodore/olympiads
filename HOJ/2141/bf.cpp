#include <cstdio>
#include <algorithm>

const int maxn = 20007;
int n;
int kid[maxn];

int calc()
{
    int ans = 0;
    for (int i = 1; i <= n; ++i)
	for (int j = 1; j < i; ++j)
	    ans += kid[j] > kid[i];
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
	scanf("%d", kid + i);
    int ans = calc();
    printf("%d\n", ans);
    int m;
    scanf("%d", &m);
    for (int _ = 1, a, b; _ <= m; ++_)
    {
	scanf("%d%d", &a, &b);
	if (a > b)
	    std::swap(a, b);
	ans += (kid[b] > kid[a]) - (kid[b] < kid[a]);
	for (int i = a + 1; i < b; ++i)
	    ans += (kid[i] > kid[a]) + (kid[i] < kid[b]) - (kid[a] > kid[i]) - (kid[i] > kid[b]);
	std::swap(kid[a], kid[b]);
	printf("%d\n", ans);
#ifdef DB
	for (int i = 1; i < n; ++i)
	    fprintf(stderr, "%d ", kid[i]);
	fprintf(stderr, "%d\n", kid[n]);
#endif
    }
}
