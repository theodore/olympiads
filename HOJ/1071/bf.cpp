#include <cstdio>
#include <algorithm>

const int maxn = 5003;
int n;
long long A, B, C;
int h[maxn], v[maxn];

bool good(int a, int b, int c)
{
    if (h[c] < h[a] || v[c] < v[b])
	return false;
    return A * (h[c] - h[a]) + B * (v[c] - v[b]) <= C;
}

int main()
{
    scanf("%d%lld%lld%lld", &n, &A, &B, &C);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", h + i, v + i);
    int ans = 0;
    for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
	    if (good(i, j, i) && good(i, j, j))
	    {
		int cnt = 0;
		for (int k = 0; k < n; ++k)
		    cnt += good(i, j, k);
		ans = std::max(ans, cnt);
#ifdef DB
		fprintf(stderr, "%d %d %d\n", i, j, ans);
#endif
	    }
    printf("%d\n", ans);
}
