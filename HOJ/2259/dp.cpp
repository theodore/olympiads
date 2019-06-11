#include <cstdio>
#include <cctype>
#include <algorithm>

const int maxn = 1000007;
struct H
{
    int v, g;
    bool operator<(const H& z) const
    {
	return v > z.v;
    }
};
H h[maxn];
int hs;

void getint(int& x)
{
    int c;
    while (!isdigit(c = getchar()))
	;
    x = c - '0';
    while (isdigit(c = getchar()))
	x = x * 10 + c - '0';
}

int main()
{
    int n;
    int ans = 0;
    getint(n);
    int z = ~0u >> 2;
#if DB >= 1
    fprintf(stderr, "f[0] = 0 ");
#endif
    for (int i = 1, x; i <= n; ++i)
    {
	getint(x);
	h[hs].v = ans - (h[hs].g = -i - x);
	std::push_heap(h, h + ++hs);
#if DB >= 1
	fprintf(stderr, "g[%d] = %d\n", i - 1, -i - x);
#endif
	while (hs > 0 && h[0].g >= -i)
	{
	    std::pop_heap(h, h + hs--);
	    z = std::min(z, h[hs].v + h[hs].g + h[hs].g);
	}
	ans = z + i;
	if (hs > 0)
	    ans = std::min(ans, h[0].v - i);
#if DB >= 1
	fprintf(stderr, "f[%d] = %d ", i, ans);
	if (i == n)
	    fprintf(stderr, "\n");
#endif
    }
    printf("%d\n", ans);
}
