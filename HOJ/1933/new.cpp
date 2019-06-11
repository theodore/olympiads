#include <cstdio>
#include <cstring>
#include <algorithm>

#define up(a, b) a = std::min(a, b)

const int maxn = 73;
const int maxw = 2107;

struct strct
{
    int h, w;
    bool operator<(const strct& x) const
	{ return h > x.h; }
};

int n;
int f[2][maxw][maxw];
strct b[maxn];
int sum;

void input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &b[i].h, &b[i].w);
    std::sort(b, b + n);
}

void dp()
{
    const int inf = 0x3f3f3f3f;
    memset(f, 0x3f, sizeof f);
    f[1][0][0] = 0;
    for (int i = 0; i < n; ++i)
    {
	int (&g)[maxw][maxw] = f[(i & 1) ^ 1];
	int (&F)[maxw][maxw] = f[i & 1];
	const int w = b[i].w, h = b[i].h;
	int j, k;
	{
	    if (0 < sum && g[0][0] != inf)
	    {
		up(F[w][0], g[0][0] + h);
		up(F[0][w], g[0][0] + h);
		up(F[0][0], g[0][0]);
	    }
	    for (k = 1; 0 + k < sum; ++k)
		if (g[0][k] != inf)
		{
		    up(F[w][k], g[0][k] + h);
		    up(F[0][k + w], g[0][k]);
		    up(F[0][k], g[0][k]);
		    g[0][k] = inf;
		}
	    up(F[0][sum], g[0][sum] + h);
	    g[0][0] = inf;
	    g[0][sum] = inf;
	}
	for (j = 1; j <= sum; ++j)
	{
	    if (j < sum && g[j][0] != inf)
	    {
		up(F[j + w][0], g[j][0]);
		up(F[j][w], g[j][0] + h);
		up(F[j][0], g[j][0]);
	    }
	    for (k = 1; j + k < sum; ++k)
		if (g[j][k] != inf)
		{
		    up(F[j + w][k], g[j][k]);
		    up(F[j][k + w], g[j][k]);
		    up(F[j][k], g[j][k]);
		    g[j][k] = inf;
		}
	    up(F[j][sum - j], g[j][sum - j] + h);
	    g[j][0] = g[j][sum - j] = inf;
	}
	sum += w;
    }
}

void output()
{
    const int (&g)[maxw][maxw] = f[(n & 1) ^ 1];
    long long ans = ~0ull >> 1;
    for (int j = 1; j < sum; ++j)
	for (int k = 1; j + k < sum; ++k)
	    up(ans, ((long long)g[j][k]) * std::max(j, std::max(k, sum - j - k)));
    printf("%d\n", int(ans));
}

int main()
{
    input();
    dp();
    output();
}
