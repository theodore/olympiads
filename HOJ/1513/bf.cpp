#include <cstdio>
#include <algorithm>

const int maxn = 1000;

int v[maxn][maxn];

int askmax(int x0, int y0, int x1, int y1)
{
    int a = 0;
    for (int i = x0; i <= x1; ++i)
    {
	int t = *std::max_element(v[i] + y0, v[i] + y1 + 1);
	a = std::max(a, t);
    }
    return a;
}

void set(int x0, int y0, int x1, int y1, int z)
{
    for (int i = x0; i <= x1; ++i)
	for (int j = y0; j <= y1; ++j)
	    v[i][j] = z;
}

int main()
{
    int n, m, _;
    scanf("%d%d%d", &n, &m, &_);
    for (int dx, dy, x, y, h; _--; )
    {
	scanf("%d%d%d%d%d", &dx, &dy, &h, &x, &y);
	set(x + 1, y + 1, x + dx, y + dy,
		askmax(x + 1, y + 1, x + dx, y + dy) + h);
    }
    printf("%d\n", askmax(1, 1, n, m));
}
