#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 100007;
const int maxv = 200007;
int n, num[maxn];
bool vis[maxv];

int calc(int a, int b)
{
    int z = 0;
    memset(vis, 0, sizeof vis);
    for (int j = a; j <= b; ++j)
    {
	if (!vis[num[j] + maxv / 2])
	    z += num[j];
	vis[num[j] + maxv / 2] = true;
    }
    return z;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
	scanf("%d", num + i);
    scanf("%d", &n);
    for (int i = 0, a, b; i < n; ++i)
    {
	scanf("%d%d", &a, &b);
	int z = 1 << 31;
	for (int x = a; x <= b; ++x)
	    for (int y = x; y <= b; ++y)
		z = std::max(z, calc(x, y));
	printf("%d\n", std::max(z, 0));
    }
}
