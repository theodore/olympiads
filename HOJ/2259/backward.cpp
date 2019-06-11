#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 1000007;
int n;
int a[maxn];
int bit[maxn];
int minv[maxn];

int ask(int p)
{
    int r = ~0u >> 2;
    for (p = std::min(p, n + 1); p; p -= p & -p)
	r = std::min(r, bit[p]);
    return r;
}

void set(int p, const int v)
{
    while (p <= n + 1)
    {
	bit[p] = std::min(bit[p], v);
	p += p & -p;
    }
}

int main()
{
    scanf("%d", &n);
    memset(bit, 0x3f, sizeof bit[0] * (n + 1));
    for (int i = 1; i <= n; ++i)
	scanf("%d", a + i);
    minv[n + 1] = n + 1;
    minv[n + 2] = ~0u >> 2;
    bit[n + 1] = -n - 1;
    int ans;
    for (int i = n; i > 0; --i)
    {
	const int g = i + 1 + a[i];
	//ans = std::min(minv[std::min(n + 2, g)] - g, ask(g) + g);
	ans = ask(g) + g;
	if (g <= n + 1)
	    ans = std::min(ans, minv[g] - g);
	set(i, ans - i);
	minv[i] = std::min(minv[i + 1], ans + i);
#if DB >= 1
	fprintf(stderr, "%d %d\n", i, ans);
#endif
    }
    printf("%d\n", ans);
}
