#include <cstdio>
#include <algorithm>

const int maxn = 73;
const int maxw = 2107;
const int inf = 1890000; // max answer possible

struct strct
{
    int h, w;
    bool operator<(const strct& x) const
	{ return h > x.h; }
};

int n;
int f[2][maxw][maxw];
strct b[maxn];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &b[i].h, &b[i].w);
    std::sort(b, b + n);
    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
	sum += b[i].w;
	for (int j = 0; j <= sum; ++j)
	    for (int k = 0; j + k <= sum; ++k)
	    {
		const int l = sum - j - k;
		int& x = f[i & 1][j][k] = inf;
		const int (&g)[maxw][maxw] = f[(i & 1) ^ 1];
		const int w = b[i].w, h = b[i].h;
#define up(a, b) a = std::min(a, b)
		if (j > w)
		    x = g[j - w][k];
		else if (j == w)
		    x = g[0][k] + h;
		if (k > w)
		    up(x, g[j][k - w]);
		else if (k == w)
		    up(x, g[j][0] + h);
		if (l > w)
		    up(x, g[j][k]);
		else if (l == w)
		    up(x, g[j][k] + h);
	    }
    }
    const int (&g)[maxw][maxw] = f[(n & 1) ^ 1];
    //int ans = inf;
    long long ans = ~0ull >> 1;
    for (int j = 1; j < sum; ++j)
	for (int k = 1; j + k < sum; ++k)
	    up(ans, ((long long)g[j][k]) * std::max(j, std::max(k, sum - j - k)));
    printf("%d\n", int(ans));
}
